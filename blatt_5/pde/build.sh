#!/bin/sh
CC=${CC:-gcc}
OPTFLAGS=${OPTFLAGS:--Ofast -march=native -flto}
PGO=${PGO:-true}
STRIP=${STRIP:-true}
test -f partdiff && rm partdiff
test -f partdiff.o && rm partdiff.o
if test $PGO = "true"; then
	test -f ./*.gcda && rm ./*.gcda
	$CC -std=c11 -Wall -Wextra -Wpedantic $OPTFLAGS -fprofile-generate=./ -c -o partdiff.o partdiff.c
	$CC -std=c11 -Wall -Wextra -Wpedantic $OPTFLAGS -fprofile-generate=./ partdiff.o -lm -o partdiff
	./partdiff 1 2 64 1 2 10240 > /dev/zero
	./partdiff 1 2 64 2 2 5120 > /dev/zero
	test -f partdiff && rm partdiff
	test -f partdiff.o && rm partdiff.o
	$CC -std=c11 -Wall -Wextra -Wpedantic $OPTFLAGS -fprofile-use=./ -c -o partdiff.o partdiff.c
	$CC -std=c11 -Wall -Wextra -Wpedantic $OPTFLAGS -fprofile-use=./ partdiff.o -lm -o partdiff
	test -f ./*.gcda && rm ./*.gcda
else
	$CC -std=c11 -Wall -Wextra -Wpedantic $OPTFLAGS -c -o partdiff.o partdiff.c
	$CC -std=c11 -Wall -Wextra -Wpedantic $OPTFLAGS partdiff.o -lm -o partdiff
fi
if test $STRIP = "true"; then
	strip partdiff
fi
