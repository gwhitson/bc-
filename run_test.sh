#!/bin/bash

make  clean
make

if [ $# -ne 1 ]; then
    ./compiler source/test.py listing/test.lst object/test.obj
    cat listing/test.lst
else
    ./compiler source/$1.py listing/$1.lst object/$1.obj
    cat listing/$1.lst
fi
