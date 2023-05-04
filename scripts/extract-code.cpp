// extract-code.cpp : Scan a Markdown file for C++ programs

#include <string>
#include <sstream>
#include <regex>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

int main(const int argc, const char **argv) {
    vector<string_view> args{ argv + 1, argv + argc };
    for (const auto& filename : args) {
        cout << "- " << filename << ":\n";
        string input_file, line;
        ifstream infile{ filename.data() };
        if (!infile) {
            cerr << "Error opening file: " << filename << '\n';
            return 1;
        }
        for (;;) {
            getline(infile, line);
            if (infile.eof()) {
                break;
            }
            input_file += line + '\n';
        }
        infile.close();
        istringstream iss{ input_file };
        while (!iss.eof()) {
            getline(iss, line);
            if ((line != "```cpp") && (line != "```")) {
                continue;
            }
            bool no_cpp = line == "```";
            getline(iss, line);
            regex is_cpp { R"(^// ([[:alnum:]_-]+\.cpp) :)" };
            smatch matches;
            if (regex_search(line, matches, is_cpp)) {
                cerr << "Filename: " << matches[1] << (no_cpp ? " (no type)" : "") << '\n';
            }
            string output_file = matches[1];
            ofstream header{ "headers\\"s + output_file, ios_base::binary },
                module{ "modules\\"s + output_file, ios_base::binary };
            while (line != "```") {
                header << line << '\n';
                if (line == "using namespace std;") {
                    module << "import std;\n";
                }
                if (line.substr(0, 8) != "#include") {
                    module << line << '\n';
                }
                getline(iss, line);
            }
        }
    }
}