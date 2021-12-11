#define _DEFAULT_SOURCE
#define _MPI_BUFFER_SIZE 256

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <mpi.h>

int main() {
    MPI_Init(NULL, NULL);

    int rank;
    int size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

	//Message buffer
	char str[_MPI_BUFFER_SIZE];
	
    if(rank != 0) {
		//Rank 1 to n
        char h_string[64];
        
        struct timeval t_value;
        time_t t_seconds;
        int t_micros;
        struct tm *t_formatting;
        char t_string[64];
        
        gethostname(h_string, sizeof(h_string));
        
        gettimeofday(&t_value, NULL);
        t_seconds = t_value.tv_sec;
        t_micros = t_value.tv_usec;
        
        t_formatting = localtime(&t_seconds);
        strftime(t_string, sizeof(t_string), "%Y-%m-%d %H:%M:%S.", t_formatting);

        //Send following string to rank 0
        snprintf(str, _MPI_BUFFER_SIZE, "%s: %s%d\n", h_string, t_string, t_micros);
		MPI_Send(&str, _MPI_BUFFER_SIZE, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    } else {
        //Rank is zero
		
        //Receive strings and print
		for(int i = 1; i < size; i++) {
			MPI_Recv(&str, _MPI_BUFFER_SIZE, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf(str);
		}
    }
	
	MPI_Barrier(MPI_COMM_WORLD);
	printf("Rang %d beendet jetzt!\n", rank);

    MPI_Finalize();

    return 0;
}
