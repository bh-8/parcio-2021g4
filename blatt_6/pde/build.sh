#!/bin/sh
CC=${CC:-gcc}
OPTFLAGS=${OPTFLAGS:--Ofast -march=native -flto}
test -f $1 && rm $1
test -f $1.o && rm $1.o
$CC -std=c11 -Wall -Wextra -Wpedantic $OPTFLAGS -c -o $1.o $1.c
$CC -std=c11 -Wall -Wextra -Wpedantic $OPTFLAGS $1.o -lm -o $1
