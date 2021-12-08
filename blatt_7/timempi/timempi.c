#define _DEFAULT_SOURCE

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
    printf("Rank: %d\n", rank);

    if(rank == 0) {
        //Rank is zero

        //TODO: Receive strings and print minimum micro seconds
    } else {
        //Rank 1 to n
        char h_string[256];
        
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

        //TODO: Send following string to rank 0
        printf("%s: %s%d\n", h_string, t_string, t_micros);
    }

    MPI_Finalize();

    return 0;
}
