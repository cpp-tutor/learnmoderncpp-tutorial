#!/bin/bash

# Note: in order to be recognized as code blocks, they must start with: ```python

for f in ../01*.md ../02*.md ../03*.md ../04*.md ../05*.md ../06*.md ../07*.md ../08*.md ../09*.md ../10*.md ; do
  out=../jupyter-notebooks/$(basename $f)
  cat $f | sed 's/```cpp/```python/' | jupytext --from md --to notebook -o ${out%%.md}.ipynb
done
