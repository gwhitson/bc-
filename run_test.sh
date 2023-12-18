#!/bin/bash

make clean
make

#ls | grep -q 'compiler'
#if [ $? -eq 1 ] ; then
#    make
#fi

if [ $# -ne 1 ]; then
    ./compiler tst/01.py lst/01.lst
    cat tst/01.py
    cat lst/01.lst
else
    ./compiler tst/$1.py lst/$1.lst
    cat tst/$1.py
    cat lst/$1.lst
fi
