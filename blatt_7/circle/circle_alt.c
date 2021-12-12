#define _MPI_BUFFER_SIZE 256

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int*
init(int N, int maxsize, int rank)
{
	int* buf = malloc(sizeof(int) * maxsize);

	srand(time(NULL) ^ (long)rank);

	for (int i = 0; i < N; i++)
		buf[i] = rand() % 25;

	for (int i = N; i < maxsize; ++i)
		buf[i] = -1;

	return buf;
}

int
circle(int* buf, int rank, int size, int N)
{
	int follower = (rank + 1) % size;
	int previous = (rank - 1) < 0 ? size - 1 : rank - 1;
	int last = -1;
	int terminate = 0;

	if (rank == 0)
		MPI_Send(buf, 1, MPI_INT, size - 1, 1, MPI_COMM_WORLD);
	else if (rank == size - 1)
		MPI_Recv(&last, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	while (1)
	{
		if (rank != 0)
		{
			int other_N = -1;
			MPI_Send(&N, 1, MPI_INT, follower, 0, MPI_COMM_WORLD);
			MPI_Recv(&other_N, 1, MPI_INT, previous, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Send(buf, N, MPI_INT, follower, 0, MPI_COMM_WORLD);
			MPI_Recv(buf, other_N, MPI_INT, previous, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			N = other_N;
			if (last != -1 && buf[0] == last)
				terminate = 1;
			MPI_Allreduce(&terminate, &terminate, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
			if (terminate)
				break;
		}
		else
		{
			int other_N = -1;
			MPI_Recv(&other_N, 1, MPI_INT, previous, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Send(&N, 1, MPI_INT, follower, 0, MPI_COMM_WORLD);
			int *temp = malloc(sizeof(int) * N);
			for (int i = 0; i < N; ++i)
				temp[i] = buf[i];
			MPI_Recv(buf, other_N, MPI_INT, previous, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Send(temp, N, MPI_INT, follower, 0, MPI_COMM_WORLD);
			N = other_N;
			free(temp);
			MPI_Allreduce(&terminate, &terminate, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD);
			if (terminate)
				break;
		}
	}

	// Return the last used N
	return N;
}

void
print_arr(int *buf, int rank, int size, int N, int before)
{
	char str[_MPI_BUFFER_SIZE];

	if (rank == 0)
	{
		if (before == 0)
			printf("\nAFTER\n");
		else
			printf("\nBEFORE\n");

		for (int i = 0; i < N; i++)
		{
			printf("rank %d: %d\n", rank, buf[i]);
		}
		for (int i = 1; i < size; ++i)
		{
			int other_N;
			MPI_Recv(&other_N, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			for (int j = 0; j < other_N; ++j)
			{
				MPI_Recv(&str, _MPI_BUFFER_SIZE, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				printf(str);
			}
		}
	}
	else
	{
		MPI_Send(&N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		for (int i = 0; i < N; ++i)
		{
			snprintf(str, _MPI_BUFFER_SIZE, "rank %d: %d\n", rank, buf[i]);
			MPI_Send(&str, _MPI_BUFFER_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
		}
	}
}

int
main(int argc, char** argv)
{
	MPI_Init(&argc, &argv);
	
	int  N;
	int  rank;
	int  size;
	int* buf;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (argc < 2)
	{
		if (rank == 0)
			printf("Arguments error!\nPlease specify a buffer size.\n");
		return EXIT_FAILURE;
	}

	// Array length
	// TODO: Proper input validation, maybe
	// TODO: How to divide the array when there are more processes than its len
	N   = atoi(argv[1]);
	int count = N / size;
	int remainder = N % size;
	N = count;
	int maxsize = remainder == 0 ? N : N + 1;

	N += rank < remainder ? 1 : 0;
	
	buf = init(N, maxsize, rank);

	print_arr(buf, rank, size, N, 1);

	N = circle(buf, rank, size, N);

	MPI_Barrier(MPI_COMM_WORLD);

	print_arr(buf, rank, size, N, 0);

	MPI_Finalize();

	return EXIT_SUCCESS;
}
