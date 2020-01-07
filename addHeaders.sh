#!/usr/bin/env sh

files=$(find src -type f)
for file in $files; do
    echo $file
    filename=$(basename $file)

    cat  $csv > tmpfile2; mv tmpfile2 $csv;
    echo "/**
 * @file $filename
 *
 * @author Adam Jędrzejowski <adam@jedrzejowski.pl>
 *
 */" | cat - yourfile > /tmp/tmpZprCraft && mv /tmp/tmpZprCraft "$file"
done


