#define _DEFAULT_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

int main() {
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
	
    printf("%s: %s%d\n", h_string, t_string, t_micros);
    return 0;
}
