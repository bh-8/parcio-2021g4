CFLAGSGCC = -std=c11 -Wall -Wextra -Wpedantic -Ofast -fopenmp
CFLAGSMPICC = -std=c11 -Wall -Wextra -Wpedantic -O3 -g
GCC = gcc
MPICC = mpicc

all: mpi threaded

threaded:
	$(GCC) $(CFLAGSGCC) -c -o partdiff_blatt3_threaded.o partdiff_blatt3_threaded.c
	$(GCC) $(CFLAGSGCC) partdiff_blatt3_threaded.o -lm -o partdiff_blatt3_threaded

mpi:
	$(MPICC) $(CFLAGSMPICC) -c -o partdiff_blatt8_mpi.o partdiff_blatt8_mpi.c
	$(MPICC) $(CFLAGSMPICC) partdiff_blatt8_mpi.o -lm -o partdiff_blatt8_mpi

clean:
	$(RM) partdiff_blatt3_threaded.o partdiff_blatt3_threaded partdiff_blatt8_mpi.o partdiff_blatt8_mpi
