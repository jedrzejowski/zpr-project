#!/usr/bin/sh

doxygen Doxyfile

mkdir -p "docs/res"

cp "res/preview1.png" "docs/res/preview1.png"
cp "res/preview2.png" "docs/res/preview2.png"
