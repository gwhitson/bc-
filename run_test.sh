#!/bin/bash

make clean
make

#ls | grep -q 'compiler'
#if [ $? -eq 1 ] ; then
#    make
#fi

if [ $# -ne 1 ]; then
    ./compiler tst/test.py lst/test.lst
    cat tst/test.py
    cat lst/test.lst
else
    ./compiler tst/$1.py lst/$1.lst
    cat tst/$1.py
    cat lst/$1.lst
fi
