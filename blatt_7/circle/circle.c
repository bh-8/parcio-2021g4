#define _MPI_BUFFER_SIZE 256

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int* init(int N, int R, bool zeroLast) {
	//N: requested array length
	//R: process rank
	
	//Allocate memory
	int* buf = malloc(sizeof(int) * N);
	
	//Initialize randomizer
	srand(time(NULL) ^ (long)R);
	
	//Fill array with random values
	for (int i = 0; i < N; i++) {
		buf[i] = rand() % 25;
	}
	
	if(zeroLast) {
		buf[N - 1] = 0;
	}
	
	return buf;
}

int* circle(int* buf, int bufSize, int R, int S) {
	//buf: process data
	//bufSize: data size
	//R: process rank
	//S: amount of mpi processes (size)
	
	//Next rank
	int nextRank = (R + 1) % S;
	
	//Previous rank (if smaller zero, use last)
	int prevRank = (R - 1) < 0 ? S - 1 : R - 1;
	
	//Send & receive...
	MPI_Send(buf, bufSize, MPI_INT, nextRank, 0, MPI_COMM_WORLD);
	MPI_Recv(buf, bufSize, MPI_INT, prevRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	
	return buf;
}

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);
	
	int N;
	int rank;
	int size;
	int* buf;
	
	//Init process rank
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	//Amount of processes
    MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	//Check argument
	if (argc < 2 && rank == 0) {
		printf("Arguments error!\nPlease specify a buffer size.\n");
		return EXIT_FAILURE;
	}

	// Array length
	N = atoi(argv[1]);
	
	//Check argument
	if(N < size && rank == 0) {
		printf("Arguments error!\nArray length is lower than process number.\n");
		return EXIT_FAILURE;
	}
	
	//Elements per process
	int elements = N / size;
	int elementsRemainder = N % size;
	
	if(elementsRemainder != 0) {
		//Increase element count per thread
		elements++;
	}
	
	//Wait for all processes to check arguments
	MPI_Barrier(MPI_COMM_WORLD);
	
	//Allocate memory for elements per process
	if(elementsRemainder != 0) {
		if(rank < elementsRemainder) {
			buf = init(elements, rank, false);
		} else {
			buf = init(elements, rank, true);
		}
	} else {
		buf = init(elements, rank, false);
	}
	
	//Print prior circle
	printf("BEFORE\n");
	for (int i = 0; i < elements; i++) {
		printf("rank %d: %d\n", rank, buf[i]);
	}
	
	//Send first element of first process to last process
	int cond = buf[0];
	if(rank == size - 1) {
		MPI_Recv(&cond, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	if(rank == 0) {
		MPI_Send(&cond, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD);
	}
	
	//Wait for broadcast of first element
	MPI_Barrier(MPI_COMM_WORLD);
	
	//Perform circle
	bool isLastProc = rank == size - 1 ? true : false;
	bool bufferMetCondition = isLastProc ? (buf[0] == cond) : false;
	while(!bufferMetCondition) {
		circle(buf, elements, rank, size);
		
		if(isLastProc == 1) {
			//Last process contains target value?
			bufferMetCondition = buf[0] == cond;
			
			//Broadcast condition
			for(int i = 0; i < size - 1; i++) {
				MPI_Send(&bufferMetCondition, 1, MPI_C_BOOL, i, 0, MPI_COMM_WORLD);
			}
		} else {
			MPI_Recv(&bufferMetCondition, 1, MPI_C_BOOL, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	}
	
	//Wait for cycle to complete
	MPI_Barrier(MPI_COMM_WORLD);
	
	//Print after circle
	printf("AFTER\n");
	for (int j = 0; j < elements; j++) {
		printf("rank %d: %d\n", rank, buf[j]);
	}
	
	//Free memory & finalize
	free(buf);
	MPI_Finalize();
	
	return EXIT_SUCCESS;
}
