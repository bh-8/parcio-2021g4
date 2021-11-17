CFLAGS  = -std=c11 -Wall -Wextra -Wpedantic -Ofast -fopenmp

all: row

row:
	$(CC) $(CFLAGS) -D ROW -c -o partdiff_row.o partdiff.c
	$(CC) $(CFLAGS) -D ROW partdiff_row.o -lm -o partdiff_row

column:
	$(CC) $(CFLAGS) -D COLUMN -c -o partdiff_column.o partdiff.c
	$(CC) $(CFLAGS) -D COLUMN partdiff_column.o -lm -o partdiff_column

element:
	$(CC) $(CFLAGS) -D ELEMENT -c -o partdiff_element.o partdiff.c
	$(CC) $(CFLAGS) -D ELEMENT partdiff_element.o -lm -o partdiff_element

clean:
	$(RM) partdiff.o partdiff partdiff_row.o partdiff_row partdiff_column.o partdiff_column partdiff_element.o partdiff_element
