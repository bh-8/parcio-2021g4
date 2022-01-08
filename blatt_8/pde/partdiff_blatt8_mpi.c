/*
 * partdiff - PDE solver for Gauß-Seidel and Jacobi methods
 * Copyright (C) 1997 Thomas Ludwig
 * Copyright (C) 1997 Thomas A. Zochler
 * Copyright (C) 1997 Andreas C. Schmidt
 * Copyright (C) 2007-2010 Julian M. Kunkel
 * Copyright (C) 2010-2021 Michael Kuhn
 * Copyright (C) 2021 Bernhard Birnbaum
 * Copyright (C) 2021 Philipp David
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* ************************************************************************ */
/* Include standard header file.                                            */
/* ************************************************************************ */
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <sys/time.h>
#include <mpi.h>

/* ************* */
/* Some defines. */
/* ************* */

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define MAX_INTERLINES    10240
#define MAX_ITERATION     200000
#define MAX_THREADS       1024
#define METH_GAUSS_SEIDEL 1
#define METH_JACOBI       2
#define FUNC_F0           1
#define FUNC_FPISIN       2
#define TERM_PREC         1
#define TERM_ITER         2

struct calculation_arguments
{
	uint64_t N;            /* number of spaces between lines (lines=N+1) */
	uint64_t num_matrices; /* number of matrices */
	double   h;            /* length of a space between two lines */
	double*  M;            /* two matrices with real values */
	
	int R; //store mpi rank
	int S; //store mpi size
	
	uint64_t matrixSize; //stores mpi process matrix size
	uint64_t matrixFrom; //stores the global index of the first line
	uint64_t matrixTo; //stores the global index of the last line

	size_t lineWidth;
	size_t procLines;
};

struct calculation_results
{
	uint64_t m;
	uint64_t stat_iteration; /* number of current iteration */
	double   stat_precision; /* actual precision of all slaves in iteration */
};

struct options
{
	uint64_t number;         /* Number of threads */
	uint64_t method;         /* Gauss Seidel or Jacobi method of iteration */
	uint64_t interlines;     /* matrix size = interlines*8+9 */
	uint64_t inf_func;       /* inference function */
	uint64_t termination;    /* termination condition */
	uint64_t term_iteration; /* terminate if iteration number reached */
	double   term_precision; /* terminate if precision reached */
};

struct vector
{
	size_t** buf;
	size_t size;
	size_t max_size;
};

static void push(void*);
static void* pop();

/* ************************************************************************ */
/* Global variables                                                         */
/* ************************************************************************ */

/* time measurement variables */
struct timeval start_time; /* time when program started */
struct timeval comp_time;  /* time when calculation completed */
struct vector allocated_memory;

static void
usage(char* name)
{
	printf("Usage: %s [num] [method] [lines] [func] [term] [prec/iter]\n", name);
	printf("\n");
	printf("  - num:       number of threads (1 .. %d)\n", MAX_THREADS);
	printf("  - method:    calculation method (1 .. 2)\n");
	printf("                 %1d: Gauß-Seidel\n", METH_GAUSS_SEIDEL);
	printf("                 %1d: Jacobi\n", METH_JACOBI);
	printf("  - lines:     number of interlines (0 .. %d)\n", MAX_INTERLINES);
	printf("                 matrixsize = (interlines * 8) + 9\n");
	printf("  - func:      interference function (1 .. 2)\n");
	printf("                 %1d: f(x,y) = 0\n", FUNC_F0);
	printf("                 %1d: f(x,y) = 2 * pi^2 * sin(pi * x) * sin(pi * y)\n", FUNC_FPISIN);
	printf("  - term:      termination condition ( 1.. 2)\n");
	printf("                 %1d: sufficient precision\n", TERM_PREC);
	printf("                 %1d: number of iterations\n", TERM_ITER);
	printf("  - prec/iter: depending on term:\n");
	printf("                 precision:  1e-4 .. 1e-20\n");
	printf("                 iterations:    1 .. %d\n", MAX_ITERATION);
	printf("\n");
	printf("Example: %s 1 2 100 1 2 100 \n", name);
}

static void
askParams(struct options* options, int argc, char** argv)
{
	int ret;

	if (argc < 7 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-?") == 0)
	{
		usage(argv[0]);
		exit(0);
	}

	ret = sscanf(argv[1], "%" SCNu64, &(options->number));

	if (ret != 1 || !(options->number >= 1 && options->number <= MAX_THREADS))
	{
		usage(argv[0]);
		exit(1);
	}

	ret = sscanf(argv[2], "%" SCNu64, &(options->method));

	if (ret != 1 || !(options->method == METH_GAUSS_SEIDEL || options->method == METH_JACOBI))
	{
		usage(argv[0]);
		exit(1);
	}

	ret = sscanf(argv[3], "%" SCNu64, &(options->interlines));

	if (ret != 1 || !(options->interlines <= MAX_INTERLINES))
	{
		usage(argv[0]);
		exit(1);
	}

	ret = sscanf(argv[4], "%" SCNu64, &(options->inf_func));

	if (ret != 1 || !(options->inf_func == FUNC_F0 || options->inf_func == FUNC_FPISIN))
	{
		usage(argv[0]);
		exit(1);
	}

	ret = sscanf(argv[5], "%" SCNu64, &(options->termination));

	if (ret != 1 || !(options->termination == TERM_PREC || options->termination == TERM_ITER))
	{
		usage(argv[0]);
		exit(1);
	}

	if (options->termination == TERM_PREC)
	{
		ret = sscanf(argv[6], "%lf", &(options->term_precision));

		options->term_iteration = MAX_ITERATION;

		if (ret != 1 || !(options->term_precision >= 1e-20 && options->term_precision <= 1e-4))
		{
			usage(argv[0]);
			exit(1);
		}
	}
	else
	{
		ret = sscanf(argv[6], "%" SCNu64, &(options->term_iteration));

		options->term_precision = 0;

		if (ret != 1 || !(options->term_iteration >= 1 && options->term_iteration <= MAX_ITERATION))
		{
			usage(argv[0]);
			exit(1);
		}
	}
}

/* ************************************************************************ */
/* initVariables: Initializes some global variables                         */
/* ************************************************************************ */
static void
initVariables(struct calculation_arguments* arguments, struct calculation_results* results, struct options const* options, int R, int S)
{
	arguments->R            = R; //store mpi rank
	arguments->S            = S; //store mpi size

	arguments->N            = (options->interlines * 8) + 9 - 1;
	arguments->num_matrices = (options->method == METH_JACOBI) ? 2 : 1;
	arguments->h            = 1.0 / arguments->N;
	
	arguments->lineWidth    = arguments->N + 1; //size of one matrix dimension
	arguments->procLines    = arguments->lineWidth / S; //split global matrix to mpi processes
	int const procLinesRem  = arguments->lineWidth % S;
	if (R < procLinesRem)
		arguments->procLines++;
	arguments->matrixFrom   = arguments->procLines * R;
	if (procLinesRem && R < procLinesRem)
		arguments->matrixFrom += R;
	else if (procLinesRem && R >= procLinesRem)
		arguments->matrixFrom += procLinesRem;
	arguments->matrixTo     = arguments->matrixFrom + arguments->procLines;
	
	results->m              = 0;
	results->stat_iteration = 0;
	results->stat_precision = 0;
}

/* ************************************************************************ */
/* cleanup: frees all allocated memory                                      */
/* ************************************************************************ */
static inline void
cleanup() {
	for (void* p = pop(); p != NULL; p = pop())
		free(p);
	free(allocated_memory.buf);
}

/* ************************************************************************ */
/* allocateMemory ()                                                        */
/* allocates memory and quits if there was a memory allocation problem      */
/* ************************************************************************ */
static void*
allocateMemory(size_t size)
{
	void* p;

	if ((p = malloc(size)) == NULL)
	{
		printf("Speicherprobleme! (%" PRIu64 " Bytes angefordert)\n", size);
		cleanup();
		exit(1);
	}

	push(p);

	return p;
}

/* ************************************************************************ */
/* push: push a pointer into the vector                                     */
/* ************************************************************************ */
static void
push(void* data)
{
	if (allocated_memory.max_size == 0)
	{
		if ((allocated_memory.buf = malloc(sizeof(size_t*) << 3)) ==
				NULL)
		{
			cleanup();
			exit(1);
		}
		allocated_memory.max_size = 8;
	}
	else if (allocated_memory.max_size == allocated_memory.size)
	{
		size_t** newbuf = malloc(sizeof(size_t*) *
				((allocated_memory.size) +
				 (allocated_memory.size >> 1)));
		if (newbuf == NULL)
		{
			cleanup();
			exit(1);
		}
		memcpy(newbuf, allocated_memory.buf, allocated_memory.size);
		free(allocated_memory.buf);
		allocated_memory.buf = newbuf;
		allocated_memory.max_size = (allocated_memory.size) +
			(allocated_memory.size >> 1);
	}
	allocated_memory.buf[allocated_memory.size++] = (size_t*) data;

}

/* ************************************************************************ */
/* pop: pop a pointer from the vector, return NULL if empty                 */
/* ************************************************************************ */
static void*
pop()
{
	if (allocated_memory.size == 0)
		return NULL;
	void* p = allocated_memory.buf[--(allocated_memory.size)];
	allocated_memory.buf[allocated_memory.size] = NULL;
	return p;
}

/* ************************************************************************ */
/* allocateMatrices: allocates memory for matrices                          */
/* ************************************************************************ */
static void
allocateMatrices(struct calculation_arguments* arguments)
{
	arguments->M = allocateMemory(arguments->num_matrices * (arguments->procLines + 2) * arguments->lineWidth * sizeof(double));
}

/* ************************************************************************ */
/* initMatrices: Initialize matrix/matrices and some global variables       */
/* ************************************************************************ */
static void
initMatrices(struct calculation_arguments* arguments, struct options const* options)
{
	uint64_t const N = arguments->N;
	double const   h = arguments->h;
	uint64_t const matrixSize = arguments->lineWidth * arguments->procLines;

	typedef double(*matrix)[arguments->procLines + 2][arguments->lineWidth];

	matrix Matrix = (matrix)arguments->M;

	/* initialize matrix/matrices with zeros */
	for (size_t g = 0; g < arguments->num_matrices; g++)
		for (size_t i = 0; i < arguments->lineWidth; i++)
			for (size_t j = 0; j <= arguments->procLines + 1; j++)
				Matrix[g][i][j] = 0.0;

	/* initialize borders, depending on function (function 2: nothing to do) */
	uint64_t g, y, x, i; /* local variables for loops */
	if (options->inf_func == FUNC_F0) {
		for (g = 0; g < arguments->num_matrices; g++) {
			for(y = 0; y < arguments->procLines; y++) {
				for(x = 0; x < arguments->lineWidth; x++) {
					i = arguments->matrixFrom + y * arguments->lineWidth + x; //i depends on current mpi rank
					if(x == 0) { //one time per line
						Matrix[g][y][x] = 1.0 - (h * i); //left...
						Matrix[g][y][arguments->lineWidth - 1] = h * i; //right...
					}
					if(arguments->R == 0) { //only first matrix
						if(y == 0) { //only first line
							Matrix[g][y][x] = 1.0 - (h * i); //top...
							if(x == arguments->lineWidth - 1) { //one time per line
								Matrix[g][y][x] = 0.0; //top right...
							}
						}
					}
					if(arguments->R == arguments->S - 1) { //only last matrix
						if(y == arguments->procLines - 1) { //only last line
							Matrix[g][y][x] = h * i; //bottom...
							if(x == 0) {
								Matrix[g][y][x] = 0.0; //bottom left...
							}
						}
					}
				}
			}
		}
	}
}

/* ************************************************************************ */
/* calculate_func: calculates the interference function                     */
/* ************************************************************************ */
static inline double
calculate_func(struct calculation_arguments const* arguments, struct options const* options, int i, int j)
{
	double const h = arguments->h;

	if (options->inf_func == FUNC_FPISIN)
	{
		return ((2 * M_PI * M_PI) * h * h * sin(M_PI * h * (double)i) * sin(M_PI * h * (double)j)) / 4;
	}
	else
	{
		return 0.0;
	}
}

/* ************************************************************************ */
/* calculate: solves the equation                                           */
/* ************************************************************************ */
static void
calculate(struct calculation_arguments const* arguments, struct calculation_results* results, struct options const* options)
{
	typedef double(*matrix)[arguments->procLines + 2][arguments->lineWidth];
	matrix Matrix = (matrix)arguments->M;

	int i, j;			      /* local variables for loops */
	int m1, m2;			      /* used as indices for old and new matrices */
	double star;		      /* four times center value minus 4 neigh.b values */
	double residuum;	      /* residuum of current iteration */
	double maxresiduum = 0.0; /* maximum residuum value of a slave in iteration */

	uint64_t stat_iteration = 0;
	uint64_t term_iteration = options->term_iteration;

	/* initialize m1 and m2 depending on algorithm */
	if (options->method == METH_JACOBI)
	{
		m1 = 0;
		m2 = 1;
	}
	else
	{
		m1 = 0;
		m2 = 0;
	}

	while (term_iteration > 0)
	{
		/* First rank */
		if (0 == arguments->R)
		{
			MPI_Send(&Matrix[m2][arguments->procLines -1][0], arguments->lineWidth, MPI_DOUBLE, 1, 0xFF, MPI_COMM_WORLD);
			MPI_Recv(&Matrix[m2][arguments->procLines][0], arguments->lineWidth, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}

		/* Last rank */
		else if (arguments->S - 1 == arguments->R)
		{
			/* Odd last rank */
			if (arguments->R & 1)
			{
				MPI_Recv(&Matrix[m2][0][0], arguments->lineWidth, MPI_DOUBLE, arguments->R - 1, 0xFF, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				MPI_Send(&Matrix[m2][1][0], arguments->lineWidth, MPI_DOUBLE, arguments->R -1, 0, MPI_COMM_WORLD);
			}

			/* Even last rank */
			else
			{
				MPI_Send(&Matrix[m2][1][0], arguments->lineWidth, MPI_DOUBLE, arguments->R -1, 0, MPI_COMM_WORLD);
				MPI_Recv(&Matrix[m2][0][0], arguments->lineWidth, MPI_DOUBLE, arguments->R - 1, 0xFF, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}
		}

		/* All other ranks */
		else
		{
			/* Odd rank */
			if (arguments->R & 1)
			{
				MPI_Recv(&Matrix[m2][0][0], arguments->lineWidth, MPI_DOUBLE, arguments->R - 1, 0xFF, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				MPI_Send(&Matrix[m2][1][0], arguments->lineWidth, MPI_DOUBLE, arguments->R -1, 0, MPI_COMM_WORLD);
				MPI_Recv(&Matrix[m2][arguments->procLines][0], arguments->lineWidth, MPI_DOUBLE, arguments->R +1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				MPI_Send(&Matrix[m2][arguments->procLines -1][0], arguments->lineWidth, MPI_DOUBLE, arguments->R + 1, 0xFF, MPI_COMM_WORLD);
			}

			/* Even rank */
			else
			{
				MPI_Send(&Matrix[m2][1][0], 1, MPI_DOUBLE, arguments->R -1, 0, MPI_COMM_WORLD);
				MPI_Recv(&Matrix[m2][0][0], 1, MPI_DOUBLE, arguments->R - 1, 0xFF, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				MPI_Send(&Matrix[m2][arguments->procLines -1][0], arguments->lineWidth, MPI_DOUBLE, arguments->R +1, 0xFF, MPI_COMM_WORLD);
				MPI_Recv(&Matrix[m2][arguments->procLines][0], arguments->lineWidth, MPI_DOUBLE, arguments->R + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}
		}

		maxresiduum = 0.0;

		/* over all rows */
		for (i = 1; i < arguments->procLines; i++)
		{
			/* over all columns */
			for (j = 1; j < arguments->lineWidth - 1; j++)
			{
				star = (Matrix[m2][i - 1][j] + Matrix[m2][i][j - 1] + Matrix[m2][i][j + 1] + Matrix[m2][i + 1][j]) / 4;

				star += calculate_func(arguments, options, i, j);

				residuum = Matrix[m2][i][j] - star;
				residuum = fabs(residuum);
				maxresiduum = (residuum < maxresiduum) ? maxresiduum : residuum;

				Matrix[m1][i][j] = star;
			}
		}
		MPI_Barrier(MPI_COMM_WORLD);
		if (options->termination == TERM_PREC || term_iteration == 1)
			MPI_Allreduce(&maxresiduum, &maxresiduum, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);

		/* exchange m1 and m2 */
		i = m1;
		m1 = m2;
		m2 = i;
		stat_iteration++;
		/* check for stopping calculation depending on termination method */
		if (options->termination == TERM_PREC)
		{
			MPI_Barrier(MPI_COMM_WORLD);
			if (maxresiduum < options->term_precision)
				term_iteration = 0;
		}
		else if (options->termination == TERM_ITER)
			term_iteration--;
	}
	results->m = m2;
	results->stat_iteration = stat_iteration;
	results->stat_precision = maxresiduum;
}

/* ************************************************************************ */
/*  displayStatistics: displays some statistics about the calculation       */
/* ************************************************************************ */
static void
displayStatistics(struct calculation_arguments const* arguments, struct calculation_results const* results, struct options const* options)
{
	int    N    = arguments->N;
	double time = (comp_time.tv_sec - start_time.tv_sec) + (comp_time.tv_usec - start_time.tv_usec) * 1e-6;

	printf("Berechnungszeit:    %f s\n", time);
	printf("Speicherbedarf:     %f MiB\n", arguments->procLines * arguments->lineWidth * sizeof(double) * arguments->num_matrices / 1024.0 / 1024.0);
	printf("Berechnungsmethode: ");

	if (options->method == METH_GAUSS_SEIDEL)
	{
		printf("Gauß-Seidel");
	}
	else if (options->method == METH_JACOBI)
	{
		printf("Jacobi");
	}

	printf("\n");
	printf("Interlines:         %" PRIu64 "\n", options->interlines);
	printf("Stoerfunktion:      ");

	if (options->inf_func == FUNC_F0)
	{
		printf("f(x,y) = 0");
	}
	else if (options->inf_func == FUNC_FPISIN)
	{
		printf("f(x,y) = 2 * pi^2 * sin(pi * x) * sin(pi * y)");
	}

	printf("\n");
	printf("Terminierung:       ");

	if (options->termination == TERM_PREC)
	{
		printf("Hinreichende Genaugkeit");
	}
	else if (options->termination == TERM_ITER)
	{
		printf("Anzahl der Iterationen");
	}

	printf("\n");
	printf("Anzahl Iterationen: %" PRIu64 "\n", results->stat_iteration);
	printf("Norm des Fehlers:   %e\n", results->stat_precision);
	printf("\n");
}

/****************************************************************************/
/** Beschreibung der Funktion displayMatrix:                               **/
/**                                                                        **/
/** Die Funktion displayMatrix gibt eine Matrix                            **/
/** in einer "ubersichtlichen Art und Weise auf die Standardausgabe aus.   **/
/**                                                                        **/
/** Die "Ubersichtlichkeit wird erreicht, indem nur ein Teil der Matrix    **/
/** ausgegeben wird. Aus der Matrix werden die Randzeilen/-spalten sowie   **/
/** sieben Zwischenzeilen ausgegeben.                                      **/
/****************************************************************************/
static void displayMatrixMpi(struct calculation_arguments* arguments, struct calculation_results* results, struct options* options) {
	int const elements = 8 * options->interlines + 9;

	int x, y;

	typedef double(*matrix)[arguments->matrixTo - arguments->matrixFrom + 3][arguments->lineWidth];
	matrix Matrix = (matrix)arguments->M;
	int m = results->m;

	MPI_Status status;

	// Die erste Zeile gehört zu Rang 0
	if (arguments->R == 0) {
		arguments->matrixFrom--;
	}

	// Die letzte Zeile gehört zu Rang (size - 1)
	if (arguments->R == arguments->S - 1) {
		arguments->matrixTo++;
	}

	if (arguments->R == 0) {
		printf("Matrix:\n");
	}

	for (y = 0; y < 9; y++) {
		int line = y * (options->interlines + 1);

		if (arguments->R == 0) {
			// Prüfen, ob die Zeile zu Rang 0 gehört
			if (line < arguments->matrixFrom || line > arguments->matrixTo) {
				// Der Tag wird genutzt, um Zeilen in der richtigen Reihenfolge zu empfangen
				// Matrix[m][0] wird überschrieben, da die Werte nicht mehr benötigt werden
				MPI_Recv(Matrix[m][0], elements, MPI_DOUBLE, MPI_ANY_SOURCE, 42 + y, MPI_COMM_WORLD, &status);
			}
		} else {
			if (line >= arguments->matrixFrom && line <= arguments->matrixTo) {
				// Zeile an Rang 0 senden, wenn sie dem aktuellen Prozess gehört
				// (line - from + 1) wird genutzt, um die lokale Zeile zu berechnen
				MPI_Send(Matrix[m][line - arguments->matrixFrom + 1], elements, MPI_DOUBLE, 0, 42 + y, MPI_COMM_WORLD);
			}
		}

		if (arguments->R == 0) {
			for (x = 0; x < 9; x++) {
				int col = x * (options->interlines + 1);

				if (line >= arguments->matrixFrom && line <= arguments->matrixTo) {
					// Diese Zeile gehört zu Rang 0
					printf("%7.4f", Matrix[m][line][col]);
				} else {
					// Diese Zeile gehört zu einem anderen Rang und wurde weiter oben empfangen
					printf("%7.4f", Matrix[m][0][col]);
				}
			}

			printf("\n");
		}
	}

	fflush(stdout);
}

/* ************************************************************************ */
/*  main                                                                    */
/* ************************************************************************ */
int
main(int argc, char** argv)
{
	//MPI Init
	MPI_Init(&argc, &argv);
	
	int R; //store mpi rank
	int S; //store mpi size
	MPI_Comm_rank(MPI_COMM_WORLD, &R);
    MPI_Comm_size(MPI_COMM_WORLD, &S);
	
	struct options               options;
	struct calculation_arguments arguments;
	struct calculation_results   results;

	askParams(&options, argc, argv);

	if (options.method == METH_GAUSS_SEIDEL)
	{
		printf("This version only works with Jacobi\n");
		return 1;
	}
	
	initVariables(&arguments, &results, &options, R, S);

	if (options.number > arguments.N)
		options.number = 1;
	
	allocateMatrices(&arguments);
	initMatrices(&arguments, &options);

	gettimeofday(&start_time, NULL);
	calculate(&arguments, &results, &options);
	gettimeofday(&comp_time, NULL);

	if (R == 0)
		displayStatistics(&arguments, &results, &options);
	displayMatrixMpi(&arguments, &results, &options);

	cleanup();
	MPI_Finalize();

	return 0;
}
