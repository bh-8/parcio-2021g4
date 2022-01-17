CFLAGSGCC = -std=c11 -Wall -Wextra -Wpedantic -Ofast
CFLAGSMPICC = -std=c11 -Wall -Wextra -Wpedantic -O3 -g
GCC = gcc
MPICC = mpicc

all: mpi blatt3

blatt3:
	$(GCC) $(CFLAGSGCC) -c -o partdiff_blatt3.o partdiff_blatt3.c
	$(GCC) $(CFLAGSGCC) partdiff_blatt3.o -lm -o partdiff_blatt3

mpi:
	$(MPICC) $(CFLAGSMPICC) -c -o partdiff_blatt9_mpi.o partdiff_blatt9_mpi.c
	$(MPICC) $(CFLAGSMPICC) partdiff_blatt9_mpi.o -lm -o partdiff_blatt9_mpi

clean:
	$(RM) partdiff_blatt3.o partdiff_blatt3 partdiff_blatt9_mpi.o partdiff_blatt9_mpi