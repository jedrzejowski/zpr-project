#!/usr/bin/env sh

files=$(find src -type f)
for file in $files; do
    echo $file
    filename=$(basename $file)

    echo "/**
 * @file $filename
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 */
" | cat - "$file" > /tmp/tmpZprCraft && mv /tmp/tmpZprCraft "$file"
done


