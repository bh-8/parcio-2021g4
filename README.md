# Parallele Programmierung 2021
- [Arbeitsverzeichnis aktuelles Blatt](https://github.com/birne420/parcio-2021g4/tree/main/blatt_8)
- Website der Vorlesung: https://parcio.ovgu.de/Teaching/Winter+2021_2022/Parallele+Programmierung.html
---
### Blatt 9 - Parallelisierung mit MPI (Gauß-Seidel)
- Übungsblatt: ausstehend
- Abgabe: ausstehend
- Bewertung: ausstehend
### Blatt 8 - Parallelisierung mit MPI (Jacobi)
- Übungsblatt: [PP_2021_Uebung_08_MPI_Jacobi-p-306.pdf](https://parcio.ovgu.de/parcio_media/Teaching/Winter+2021_2022/Parallele+Programmierung/PP_2021_Uebung_08_MPI_Jacobi-p-306.pdf)
  1. **Parallelisierung mit MPI (300 Punkte)**
    - Jacobi-Verfahren mit Abbruch nach fester Iterationszahl
    - Jacobi-Verfahren mit Abbruch nach Genauigkeit
    - das Programm darf nicht langsamer als die serielle Variante sein
    - zu keinem Zeitpunkt darf ein Prozess die gesamte Matrix im Speicher halten
    - das Programm muss weiterhin mit einem Prozess funktionieren
    - das Programm muss mit beliebigen Prozesszahlen funktionieren
    - erstellen Sie eine eigene Funktion für die MPI-Parallelisierung des Jacobi-Verfahrens
    - Hinweis: Sie können die in den Materialien bereitgestellte `displayMatrixMpi`-Funktion als Grundlage für die parallele Ausgabe der Matrix benutzen
  2. **Leistungsanalyse (120 Punkte)**
    - ermitteln Sie die Leistungsdaten Ihres Programms und visualisieren Sie die Laufzeiten in einem Diagramm
    - vergleichen Sie außerdem ihr Programm mit der ursprünglichen seriellen Variante
    - visualisieren Sie alle Ergebnisse in hinreichend beschrifteten Diagrammen; schreiben Sie ca. eine viertel Seite Interpretation zu diesen Ergebnissen
  3. **Hybride Parallelisierung (90 Bonuspunkte)**
    - ermitteln Sie die Leistungsdaten Ihres Hybrid-Programms und vergleichen Sie die Laufzeiten in einem Diagramm
    - wiederholen Sie dabei jede Messung mindestens drei Mal, um aussagekräftige Mittelwerte bilden zu können
    - schreiben Sie eine halbe Seite Interpretation zu diesen Ergebnissen
- Abgabe: ausstehend (08.01.2022, 23:59)
- Bewertung: ausstehend
### Blatt 7 - MPI-Einführung
- Übungsblatt: [PP_2021_Uebung_07_MPI_Einfuehrung-p-298.pdf](https://parcio.ovgu.de/parcio_media/Teaching/Winter+2021_2022/Parallele+Programmierung/PP_2021_Uebung_07_MPI_Einfuehrung-p-298.pdf)
- Abgabe: [GoepfertWelzerDavidBirnbaum.tar.gz](https://github.com/birne420/parcio-2021g4/blob/main/blatt_7/_abgabe/GoepfertWelzerDavidBirnbaum.tar.gz?raw=true)
- Bewertung: [bewertung.pdf](https://github.com/birne420/parcio-2021g4/blob/main/blatt_7/_abgabe/bewertung.pdf?raw=true) (305/300)
### Blatt 6 - Parallelisierung mit POSIX Threads
- Übungsblatt: [PP_2021_Uebung_06_POSIX_Threads-p-286.pdf](https://parcio.ovgu.de/parcio_media/Teaching/Winter+2021_2022/Parallele+Programmierung/PP_2021_Uebung_06_POSIX_Threads-p-286.pdf)
- Abgabe: [GoepfertWelzerDavidBirnbaum.tar.gz](https://github.com/birne420/parcio-2021g4/blob/main/blatt_6/_abgabe/GoepfertWelzerDavidBirnbaum.tar.gz?raw=true)
- Bewertung: [bewertung.pdf](https://github.com/birne420/parcio-2021g4/blob/main/blatt_6/_abgabe/bewertung.pdf?raw=true) (435/420)
### Blatt 5 - Parallelisierung mit OpenMP
- Übungsblatt: [PP_2021_Uebung_05_OpenMP-p-274.pdf](https://parcio.ovgu.de/parcio_media/Teaching/Winter+2021_2022/Parallele+Programmierung/PP_2021_Uebung_05_OpenMP-p-274.pdf)
- Abgabe: [GoepfertWelzerDavidBirnbaum.tar.gz](https://github.com/birne420/parcio-2021g4/blob/main/blatt_5/_abgabe/GoepfertWelzerDavidBirnbaum.tar.gz?raw=true)
- Bewertung: [bewertung.pdf](https://github.com/birne420/parcio-2021g4/blob/main/blatt_5/_abgabe/bewertung.pdf?raw=true) (450/420)
### Blatt 4 - Parallelisierungsschema
- Übungsblatt: [PP_2021_Uebung_04_Parallelisierungsschema-p-266.pdf](https://parcio.ovgu.de/parcio_media/Teaching/Winter+2021_2022/Parallele+Programmierung/PP_2021_Uebung_04_Parallelisierungsschema-p-266.pdf)
- Abgabe: [GoepfertWelzerDavidBirnbaum.tar.gz](https://github.com/birne420/parcio-2021g4/blob/main/blatt_4/_abgabe/GoepfertWelzerDavidBirnbaum.tar.gz?raw=true)
- Bewertung: [bewertung.pdf](https://github.com/birne420/parcio-2021g4/blob/main/blatt_4/_abgabe/bewertung.pdf?raw=true) (285/300)
### Blatt 3 - Leistungsoptimierung einer seriellen Anwendung
- Übungsblatt: [PP_2021_Uebung_03_Leistungsoptimierung-p-260.pdf](https://parcio.ovgu.de/parcio_media/Teaching/Winter+2021_2022/Parallele+Programmierung/PP_2021_Uebung_03_Leistungsoptimierung-p-260.pdf)
- Abgabe: [GoepfertWelzerDavidBirnbaum.tar.gz](https://github.com/birne420/parcio-2021g4/blob/main/blatt_3/_abgabe/GoepfertWelzerDavidBirnbaum.tar.gz?raw=true)
- Bewertung: [bewertung.pdf](https://github.com/birne420/parcio-2021g4/blob/main/blatt_3/_abgabe/bewertung.pdf?raw=true) (385/340)
### Blatt 2 - Debugging
- Übungsblatt: [PP_2021_Uebung_02_Debugging-p-248.pdf](https://parcio.ovgu.de/parcio_media/Teaching/Winter+2021_2022/Parallele+Programmierung/PP_2021_Uebung_02_Debugging-p-248.pdf)
- Abgabe: [GoepfertWelzerDavidBirnbaum.tar.gz](https://github.com/birne420/parcio-2021g4/blob/main/blatt_2/_abgabe/GoepfertWelzerDavidBirnbaum.tar.gz?raw=true)
- Bewertung: [bewertung.pdf](https://github.com/birne420/parcio-2021g4/blob/main/blatt_2/_abgabe/bewertung.pdf?raw=true) (282/330)
### Blatt 1 - Einführung
- Übungsblatt: [PP_2021_Uebung_01_Einfuehrung-p-240.pdf](https://parcio.ovgu.de/parcio_media/Teaching/Winter+2021_2022/Parallele+Programmierung/PP_2021_Uebung_01_Einfuehrung-p-240.pdf)
- Abgabe: [GoepfertWelzerDavidBirnbaum.tar.gz](https://github.com/birne420/parcio-2021g4/blob/main/blatt_1/_abgabe/GoepfertWelzerDavidBirnbaum.tar.gz?raw=true)
- Bewertung: [bewertung.pdf](https://github.com/birne420/parcio-2021g4/blob/main/blatt_1/_abgabe/bewertung.pdf?raw=true) (235/210)
