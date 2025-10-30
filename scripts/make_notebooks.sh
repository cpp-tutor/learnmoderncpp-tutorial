#!/bin/bash

# Note: in order to be recognized as code blocks, must start with: ```python

srcdir=$(dirname $(readlink -f "$0"))/..
destdir=$srcdir/jupyter-notebooks
for f in $srcdir/{01,02,03,04,05,06,07,08,09,10}-*.md ; do
  out=$destdir/$(basename $f)
  cat $f | sed 's/```cpp/```python/' | jupytext --from md --to notebook -k cpp23 -o ${out%%.md}.ipynb
done
