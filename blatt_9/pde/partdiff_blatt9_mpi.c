/*
 * partdiff - PDE solver for Gauß-Seidel and Jacobi methods
 * Copyright (C) 1997 Thomas Ludwig
 * Copyright (C) 1997 Thomas A. Zochler
 * Copyright (C) 1997 Andreas C. Schmidt
 * Copyright (C) 2007-2010 Julian M. Kunkel
 * Copyright (C) 2010-2021 Michael Kuhn
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
	uint64_t local_to;     /* local ending line of this process */
	double   h;            /* length of a space between two lines */
	double*  M;            /* two matrices with real values */
	int      from;         /* global starting line of this process */
	int      to;           /* global ending line of this process */
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
	int      rank;           /* mpi rank */
	int      size;           /* mpi size */
};

/* ************************************************************************ */
/* Global variables                                                         */
/* ************************************************************************ */

/* time measurement variables */
struct timeval start_time; /* time when program started */
struct timeval comp_time;  /* time when calculation completed */

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

static inline void
exit_success()
{
	MPI_Finalize();
	exit(EXIT_SUCCESS);
}

static inline void
exit_failure()
{
	MPI_Finalize();
	exit(EXIT_FAILURE);
}

static void
askParams(struct options* options, int argc, char** argv)
{
	int ret;

	if (argc < 7 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-?") == 0)
	{
		usage(argv[0]);
		exit_success();
	}

	ret = sscanf(argv[1], "%" SCNu64, &(options->number));

	if (ret != 1 || !(options->number >= 1 && options->number <= MAX_THREADS))
	{
		usage(argv[0]);
		exit_failure();
	}

	ret = sscanf(argv[2], "%" SCNu64, &(options->method));

	if (ret != 1 || !(options->method == METH_GAUSS_SEIDEL || options->method == METH_JACOBI))
	{
		usage(argv[0]);
		exit_failure();
	}

	ret = sscanf(argv[3], "%" SCNu64, &(options->interlines));

	if (ret != 1 || !(options->interlines <= MAX_INTERLINES))
	{
		usage(argv[0]);
		exit_failure();
	}

	ret = sscanf(argv[4], "%" SCNu64, &(options->inf_func));

	if (ret != 1 || !(options->inf_func == FUNC_F0 || options->inf_func == FUNC_FPISIN))
	{
		usage(argv[0]);
		exit_failure();
	}

	ret = sscanf(argv[5], "%" SCNu64, &(options->termination));

	if (ret != 1 || !(options->termination == TERM_PREC || options->termination == TERM_ITER))
	{
		usage(argv[0]);
		exit_failure();
	}

	if (options->termination == TERM_PREC)
	{
		ret = sscanf(argv[6], "%lf", &(options->term_precision));

		options->term_iteration = MAX_ITERATION;

		if (ret != 1 || !(options->term_precision >= 1e-20 && options->term_precision <= 1e-4))
		{
			usage(argv[0]);
			exit_failure();
		}
	}
	else
	{
		ret = sscanf(argv[6], "%" SCNu64, &(options->term_iteration));

		options->term_precision = 0;

		if (ret != 1 || !(options->term_iteration >= 1 && options->term_iteration <= MAX_ITERATION))
		{
			usage(argv[0]);
			exit_failure();
		}
	}
}

/* ************************************************************************ */
/* initVariables: Initializes some global variables                         */
/* ************************************************************************ */
static void
initVariables(struct calculation_arguments* arguments, struct calculation_results* results, struct options const* options)
{
	arguments->N            = (options->interlines * 8) + 9 - 1;
	arguments->num_matrices = (options->method == METH_JACOBI) ? 2 : 1;
	arguments->h            = 1.0 / arguments->N;

	uint64_t rank           = options->rank;
	uint64_t size           = options->size;
	uint64_t local_to       = arguments->N / size;
	uint64_t remainder      = arguments->N % size;
	uint64_t from           = rank * local_to;
	uint64_t to             = from + local_to;

	if (rank == 0)
	{
		from++;
	}
	if (size - rank == 1)
	{
		to--;
	}

	arguments->local_to     = rank < remainder ? local_to + 1 : local_to;
	arguments->from         = rank < remainder ? from + rank : from + remainder;
	arguments->to           = rank < remainder ? to + rank + 1 : to + remainder;

	results->m              = 0;
	results->stat_iteration = 0;
	results->stat_precision = 0;
}

/* ************************************************************************ */
/* freeMatrices: frees memory for matrices                                  */
/* ************************************************************************ */
static void
freeMatrices(struct calculation_arguments* arguments)
{
	free(arguments->M);
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
		exit_failure();
	}

	return p;
}

/* ************************************************************************ */
/* allocateMatrices: allocates memory for matrices                          */
/* ************************************************************************ */
static void
allocateMatrices(struct calculation_arguments* arguments)
{
	uint64_t const N = arguments->N;
	uint64_t const local_to = arguments->local_to;

	arguments->M = allocateMemory(arguments->num_matrices * (local_to + 2) * (N + 1) * sizeof(double));
}

/* ************************************************************************ */
/* initMatrices: Initialize matrix/matrices and some global variables       */
/* ************************************************************************ */
static void
initMatrices(struct calculation_arguments* arguments, struct options const* options)
{
	uint64_t g, i, j; /* local variables for loops */

	uint64_t const  N = arguments->N;
	double const    h = arguments->h;
	uint64_t local_to = arguments->local_to;
	uint64_t from     = arguments->from;

	typedef double(*matrix)[local_to + 2][N + 1];

	matrix Matrix = (matrix)arguments->M;

	/* initialize matrix/matrices with zeros */
	for (g = 0; g < arguments->num_matrices; g++)
	{
		for (i = 0; i <= local_to + 1; i++)
		{
			for (j = 0; j <= N; j++)
			{
				Matrix[g][i][j] = 0.0;
			}
		}
	}

	uint64_t global_i = from;

	/* initialize borders, depending on function (function 2: nothing to do) */
	if (options->inf_func == FUNC_F0)
	{
		if (options->rank == 0)
		{
			for (g = 0; g < arguments->num_matrices; g++)
			{
				for (i = 0, global_i = from; i <= local_to; i++, global_i++)
				{
					for (j = 0; j <= N; j++)
					{
						Matrix[g][0][j] = 1.0 - (h * global_i);
					}
				}
			}
		}

		if (options->size - options->rank == 1)
		{
			for (g = 0; g < arguments->num_matrices; g++)
			{
				for (i = 0, global_i = from; i <= local_to; i++, global_i++)
				{
					for (j = 0; j <= N; j++)
					{
						Matrix[g][local_to][j] = h * global_i;
					}
				}
			}
		}

		for (g = 0; g < arguments->num_matrices; g++)
		{
			for (i = 0, global_i = from; i <= local_to; i++, global_i++)
			{
				Matrix[g][i][0] = 1.0 - (h * global_i);
				Matrix[g][i][N] = h * global_i;
			}

			Matrix[g][local_to][0] = 0.0;
			Matrix[g][0][N] = 0.0;
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
	/* THIS BREAKS JACOBI, FIX LATER */
	uint64_t 	i, j;        /* local variables for loops */
	int 		direction;   /* direction for diagonal traversal */
	double 		star;        /* four times center value minus 4 neigh.b values */
	double 		residuum;    /* residuum of current iteration */
	double 		maxresiduum; /* maximum residuum value of a slave in iteration */

	uint64_t stat_iteration = 0;
	uint64_t term_iteration = options->term_iteration;
	uint64_t N              = arguments->N;
	uint64_t local_to       = arguments->local_to;
	uint64_t from           = arguments->from - 1;
	const int rank          = options->rank;
	const int size          = options->size;

	if (size - rank != 1)
	{
		++local_to;
	}

	typedef double(*matrix)[local_to + 1][N + 1];
	matrix Matrix = (matrix)arguments->M;

	while (term_iteration > 0)
	{
		maxresiduum = 0.0;

		for (i = 1, j = 1, direction = 0; i < local_to && j < N;)
		{
			/* TODO: Receive from previous process */

			star = (Matrix[0][i - 1][j] + Matrix[0][i][j - 1] + Matrix[0][i][j + 1] + Matrix[0][i + 1][j]) / 4;

			star += calculate_func(arguments, options, i + from, j);

			residuum    = Matrix[0][i][j] - star;
			residuum    = fabs(residuum);
			maxresiduum = (residuum < maxresiduum) ? maxresiduum : residuum;

			Matrix[0][i][j] = star;

			/* TODO: Send to next process */

			/* upward diagonal direction */
			if (direction == 0)
			{
				if (j == N - 1)
				{
					++i;
					direction = 255;
				}
				else if (i == 1)
				{
					++j;
					direction = 255;
				}
				else
				{
					--i, ++j;
				}
			}

			/* downward diagonal direction */
			else
			{
				if (i == local_to)
				{
					++j;
					direction = 0;
				}
				else if (j == 1)
				{
					++i;
					direction = 0;
				}
				else
				{
					++i, --j;
				}
			}
		}

		if (options->termination == TERM_PREC || term_iteration == 1)
		{
			MPI_Allreduce(&maxresiduum, &maxresiduum, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
		}

		stat_iteration++;
		/* check for stopping calculation depending on termination method */
		if (options->termination == TERM_PREC)
		{
			if (maxresiduum < options->term_precision)
			{
				term_iteration = 0;
			}
		}
		else if (options->termination == TERM_ITER)
		{
			term_iteration--;
		}
	}

	results->m = 0;
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
	printf("Speicherbedarf:     %f MiB\n", (N + 1) * (N + 1) * sizeof(double) * arguments->num_matrices / 1024.0 / 1024.0);
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
static void
displayMatrix(struct calculation_arguments* arguments, struct calculation_results* results, struct options* options)
{
	int x, y;

	int const interlines = options->interlines;
	int const N          = arguments->N;

	typedef double(*matrix)[N + 1][N + 1];

	matrix Matrix = (matrix)arguments->M;

	printf("Matrix:\n");

	for (y = 0; y < 9; y++)
	{
		for (x = 0; x < 9; x++)
		{
			printf("%7.4f", Matrix[results->m][y * (interlines + 1)][x * (interlines + 1)]);
		}

		printf("\n");
	}

	fflush(stdout);
}

static void
displayMatrixMpi(struct calculation_arguments* arguments, struct calculation_results* results, struct options* options, int rank, int size, int from, int to)
{
	int const elements = 8 * options->interlines + 9;

	int x, y;

	typedef double(*matrix)[to - from + 3][arguments->N + 1];
	matrix Matrix = (matrix)arguments->M;
	int m = results->m;

	MPI_Status status;

	// Die erste Zeile gehört zu Rang 0
	if (rank == 0) {
		from--;
	}

	// Die letzte Zeile gehört zu Rang (size - 1)
	if (rank == size - 1) {
		to++;
	}

	if (rank == 0) {
		printf("Matrix:\n");
	}

	for (y = 0; y < 9; y++)
	{
		int line = y * (options->interlines + 1);

		if (rank == 0)
		{
			// Prüfen, ob die Zeile zu Rang 0 gehört
			if (line < from || line > to)
			{
				// Der Tag wird genutzt, um Zeilen in der richtigen Reihenfolge zu empfangen
				// Matrix[m][0] wird überschrieben, da die Werte nicht mehr benötigt werden
				MPI_Recv(Matrix[m][0], elements, MPI_DOUBLE, MPI_ANY_SOURCE, 42 + y, MPI_COMM_WORLD, &status);
			}
		}
		else
		{
			if (line >= from && line <= to)
			{
				// Zeile an Rang 0 senden, wenn sie dem aktuellen Prozess gehört
				// (line - from + 1) wird genutzt, um die lokale Zeile zu berechnen
				MPI_Send(Matrix[m][line - from + 1], elements, MPI_DOUBLE, 0, 42 + y, MPI_COMM_WORLD);
			}
		}

		if (rank == 0)
		{
			for (x = 0; x < 9; x++)
			{
				int col = x * (options->interlines + 1);

				if (line >= from && line <= to)
				{
					// Diese Zeile gehört zu Rang 0
					printf("%7.4f", Matrix[m][line][col]);
				}
				else
				{
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
	MPI_Init(&argc, &argv);

	struct options               options;
	struct calculation_arguments arguments;
	struct calculation_results   results;

	MPI_Comm_rank(MPI_COMM_WORLD, &options.rank);
	MPI_Comm_size(MPI_COMM_WORLD, &options.size);

	askParams(&options, argc, argv);

	initVariables(&arguments, &results, &options);

	allocateMatrices(&arguments);
	initMatrices(&arguments, &options);

	if (options.rank == 0)
	{
		gettimeofday(&start_time, NULL);
	}

	calculate(&arguments, &results, &options);
	if (options.rank == 0)
	{
		gettimeofday(&comp_time, NULL);
	}

	if (options.rank == 0)
	{
		displayStatistics(&arguments, &results, &options);
	}

	if (options.size == 1)
	{
		displayMatrix(&arguments, &results, &options);
	}
	else
	{
		displayMatrixMpi(&arguments, &results, &options, options.rank, options.size, arguments.from, arguments.to);
	}

	freeMatrices(&arguments);

	exit_success();
}
