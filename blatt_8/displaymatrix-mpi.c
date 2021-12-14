/*
 * rank und size sind der MPI-Rang und die Größe des Kommunikators
 * from und to stehen für den globalen(!) Bereich von Zeilen für die dieser Prozess zuständig ist
 *
 * Beispiel mit 9 Matrixzeilen und 4 Prozessen:
 * - Rang 0 is verantwortlich für Zeilen 1-2, Rang 1 für 3-4, Rang 2 für 5-6 und Rang 3 für 7
 * - Zeilen 0 und 8 sind nicht inkludiert, weil sie nicht berechnet werden
 * - Jeder Prozess speichert zwei Randzeilen in seiner Matrix
 * - Zum Beispiel: Rang 2 hat vier Zeilen 0-3 aber berechnet nur 1-2 weil 0 und 3 beide Randzeilen für andere Prozesse sind;
 *	 Rang 2 ist daher verantwortlich für die globalen Zeilen 5-6
*/
static void displayMatrixMpi(struct calculation_arguments* arguments, struct calculation_results* results, struct options* options, int rank, int size, int from, int to) {
	int const elements = 8 * options->interlines + 9;

	int x, y;

	typedef double(*matrix)[to - from + 3][arguments->N + 1];
	matrix Matrix = (matrix)arguments->M;
	int m = results->m;

	MPI_Status status;

	// Die erste Zeile gehört zu Rang 0
	if (rank == 0) {
		from--;
	}

	// Die letzte Zeile gehört zu Rang (size - 1)
	if (rank == size - 1) {
		to++;
	}

	if (rank == 0) {
		printf("Matrix:\n");
	}

	for (y = 0; y < 9; y++) {
		int line = y * (options->interlines + 1);

		if (rank == 0) {
			// Prüfen, ob die Zeile zu Rang 0 gehört
			if (line < from || line > to) {
				// Der Tag wird genutzt, um Zeilen in der richtigen Reihenfolge zu empfangen
				// Matrix[m][0] wird überschrieben, da die Werte nicht mehr benötigt werden
				MPI_Recv(Matrix[m][0], elements, MPI_DOUBLE, MPI_ANY_SOURCE, 42 + y, MPI_COMM_WORLD, &status);
			}
		} else {
			if (line >= from && line <= to) {
				// Zeile an Rang 0 senden, wenn sie dem aktuellen Prozess gehört
				// (line - from + 1) wird genutzt, um die lokale Zeile zu berechnen
				MPI_Send(Matrix[m][line - from + 1], elements, MPI_DOUBLE, 0, 42 + y, MPI_COMM_WORLD);
			}
		}

		if (rank == 0) {
			for (x = 0; x < 9; x++) {
				int col = x * (options->interlines + 1);

				if (line >= from && line <= to) {
					// Diese Zeile gehört zu Rang 0
					printf("%7.4f", Matrix[m][line][col]);
				} else {
					// Diese Zeile gehört zu einem anderen Rang und wurde weiter oben empfangen
					printf("%7.4f", Matrix[m][0][col]);
				}
			}

			printf("\n");
		}
	}

	fflush(stdout);
}
