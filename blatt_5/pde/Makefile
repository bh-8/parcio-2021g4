CFLAGS  = -std=c11 -Wall -Wextra -Wpedantic -Ofast -fopenmp -D ROW
LDFLAGS = $(CFLAGS)
LDLIBS  = -lm

all: partdiff

partdiff: partdiff.o

clean:
	$(RM) partdiff.o partdiff
