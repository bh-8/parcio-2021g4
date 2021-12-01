CFLAGS  = -std=c11 -Wall -Wextra -Wpedantic -Ofast -pthread
LDFLAGS = $(CFLAGS)
LDLIBS  = -lm

all: partdiff

partdiff: partdiff.o

clean:
	$(RM) partdiff.o partdiff