#!/usr/bin/sh

doxygen Doxyfile

mkdir -p "doxygen/html/res"

cp "res/preview1.png" "doxygen/html/res/preview1.png"
cp "res/preview2.png" "doxygen/html/res/preview2.png"
