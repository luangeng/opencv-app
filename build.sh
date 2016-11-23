#!/bin/sh

if [ $# -gt 0 ] ; then
    base=`basename $1 .cpp`
    echo "compiling $base.cpp"
    g++ -ggdb `pkg-config --cflags opencv` -o `basename $base .cpp` $base.cpp `pkg-config --libs opencv`;
    echo "---------------------------------------------------"
    ./$base
    echo "---------------------------------------------------"
else
    for i in *.c; do
        echo "compiling $i"
        gcc -ggdb `pkg-config --cflags opencv` -o `basename $i .c` $i `pkg-config --libs opencv`;
    done
    for i in *.cpp; do
        echo "compiling $i"
        g++ -ggdb `pkg-config --cflags opencv` -o `basename $i .cpp` $i `pkg-config --libs opencv`;
    done
fi


