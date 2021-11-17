CFLAGS  = -std=c11 -Wall -Wextra -Wpedantic -Ofast -fopenmp

all: row

row:
	$(CC) $(CFLAGS) -D ROW -c -o partdiff_row.o partdiff.c
	$(CC) $(CFLAGS) -D ROW partdiff_row.o -lm -o partdiff-zeile

column:
	$(CC) $(CFLAGS) -D COLUMN -c -o partdiff_column.o partdiff.c
	$(CC) $(CFLAGS) -D COLUMN partdiff_column.o -lm -o partdiff-spalte

element:
	$(CC) $(CFLAGS) -D ELEMENT -c -o partdiff_element.o partdiff.c
	$(CC) $(CFLAGS) -D ELEMENT partdiff_element.o -lm -o partdiff-element

clean:
	$(RM) partdiff.o partdiff partdiff_row.o partdiff-zeile partdiff_column.o partdiff-spalte partdiff_element.o partdiff-element
