## Jupyter Notebooks

The complete Tutorial is available as a set of Jupyter Notebooks listed above. Please note that they are intended for use with JupyterLab&mdash;it is possible to preview them on GitHub but the interactive features will not be present.

Installation of JupyterLab under Debian Linux is as follows:

```bash
sudo apt update
sudo apt install jupyter jupyterlab       # Note: many large dependencies
sudo pip install --break-system-packages jupyter-cpp-kernel
sudo apt install build-essential g++      # Note: minimum to compile C++
cd /path/to/notebooks
jupyter lab                               # Note: copy weblink token from console and open in browser
```
