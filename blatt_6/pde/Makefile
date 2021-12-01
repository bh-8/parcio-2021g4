CFLAGS  = -std=c11 -Wall -Wextra -Wpedantic -Ofast -march=native -pthread
LDFLAGS = $(CFLAGS)
LDLIBS  = -lm

all: partdiff

partdiff: partdiff.o

clean:
	$(RM) partdiff.o partdiff
