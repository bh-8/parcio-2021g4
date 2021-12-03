CFLAGS  = -std=c11 -Wall -Wextra -Wpedantic -Ofast -fopenmp
LDFLAGS = $(CFLAGS)
LDLIBS  = -lm

all: partdiff

partdiff: partdiff.o

clean:
	$(RM) partdiff.o partdiff