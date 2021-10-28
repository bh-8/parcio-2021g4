/*
 * Simple error demonstration to demonstrate power of Valgrind.
 * Julian M. Kunkel - 17.04.2008
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int*
mistake1(void)
{
	int buf[] = { 1, 1, 2, 3, 4, 5 };

	return memcpy(malloc(sizeof(int) * 6), buf, sizeof(buf));
}

int*
mistake2(void)
{
	int* buf = malloc(sizeof(int) * 2);

	buf[1] = 2;

	return buf;
}

int*
mistake3(void)
{
	/* In dieser Funktion darf kein Speicher direkt allokiert werden. */
	int* buf = mistake2();

	buf[0] = 3;

	return buf;
}

int*
mistake4(void)
{
	int* buf = malloc(sizeof(int));

	buf[0] = 4;

	return buf;
}

int
main(void)
{
	/* Modifizieren Sie die folgende Zeile nicht. */
	int* p[4] = { &mistake1()[1], &mistake2()[1], mistake3(), mistake4() };

	printf("1: %d\n", *p[0]);
	printf("2: %d\n", *p[1]);
	printf("3: %d\n", *p[2]);
	printf("4: %d\n", *p[3]);

	/* Fügen sie hier die korrekten aufrufe von free() ein. */
	free(p[0] - 1);
	free(p[1] - 1);
	free(p[2]);
	free(p[3]);

	return 0;
}
