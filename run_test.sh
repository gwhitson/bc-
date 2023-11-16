#!/bin/bash

make clean
make

#ls | grep -q 'compiler'
#if [ $? -eq 1 ] ; then
#    make
#fi

if [ $# -ne 1 ]; then
    ./compiler testfiles/test.py testlist/test.lst
    cat testlist/test.lst
else
    ./compiler testfiles/$1.py testlist/$1.lst
    cat testlist/$1.lst
fi
