
[//]: # (Diese Datei ist Markdown)

# Ausgangszustand:
Wir führen partdiff ohne Änderungen aus:
```
% time ./partdiff 1 2 64 1 2 10240
Berechnungszeit:    40.949971 s
Speicherbedarf:     4.141861 MiB
Berechnungsmethode: Jacobi
Interlines:         64
Stoerfunktion:      f(x,y) = 0
Terminierung:       Anzahl der Iterationen
Anzahl Iterationen: 10240
Norm des Fehlers:   2.753424e-05

Matrix:
 1.0000 0.8750 0.7500 0.6250 0.5000 0.3750 0.2500 0.1250 0.0000
 0.8750 0.5042 0.3082 0.2306 0.1820 0.1372 0.0996 0.0909 0.1250
 0.7500 0.3082 0.0991 0.0477 0.0349 0.0276 0.0346 0.0996 0.2500
 0.6250 0.2306 0.0477 0.0080 0.0035 0.0048 0.0276 0.1372 0.3750
 0.5000 0.1820 0.0349 0.0035 0.0006 0.0035 0.0349 0.1820 0.5000
 0.3750 0.1372 0.0276 0.0048 0.0035 0.0080 0.0477 0.2306 0.6250
 0.2500 0.0996 0.0346 0.0276 0.0349 0.0477 0.0991 0.3082 0.7500
 0.1250 0.0909 0.0996 0.1372 0.1820 0.2306 0.3082 0.5042 0.8750
 0.0000 0.1250 0.2500 0.3750 0.5000 0.6250 0.7500 0.8750 1.0000
./partdiff 1 2 64 1 2 10240  40.89s user 0.00s system 99% cpu 40.956 total
```

```
% time ./partdiff 1 2 64 2 2 5120 
Berechnungszeit:    49.717030 s
Speicherbedarf:     4.141861 MiB
Berechnungsmethode: Jacobi
Interlines:         64
Stoerfunktion:      f(x,y) = 2 * pi^2 * sin(pi * x) * sin(pi * y)
Terminierung:       Anzahl der Iterationen
Anzahl Iterationen: 5120
Norm des Fehlers:   1.662227e-05

Matrix:
 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000
 0.0000 0.0131 0.0241 0.0315 0.0341 0.0315 0.0241 0.0131 0.0000
 0.0000 0.0241 0.0446 0.0583 0.0631 0.0583 0.0446 0.0241 0.0000
 0.0000 0.0315 0.0583 0.0761 0.0824 0.0761 0.0583 0.0315 0.0000
 0.0000 0.0341 0.0631 0.0824 0.0892 0.0824 0.0631 0.0341 0.0000
 0.0000 0.0315 0.0583 0.0761 0.0824 0.0761 0.0583 0.0315 0.0000
 0.0000 0.0241 0.0446 0.0583 0.0631 0.0583 0.0446 0.0241 0.0000
 0.0000 0.0131 0.0241 0.0315 0.0341 0.0315 0.0241 0.0131 0.0000
 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000
./partdiff 1 2 64 2 2 5120  49.65s user 0.00s system 99% cpu 49.721 total
```

# Compiler Flags
Im nachfolgenden haben wir zunächst alle erdenklichen Compiler-Flags verwendet,
um das Programm ohne Veränderung des Quellcodes zu beschleunigen.  Die
verwendeten Kommandos zum kompilieren sind angegeben und werden im
`pde`-Verzeichnis des aktuellen Übungsblattes ausgeführt.

## -O2

```% cc -std=c11 -Wall -Wextra -Wpedantic -O2 -o partdiff -lm partdiff.c```
```
% time ./partdiff 1 2 64 1 2 10240
Berechnungszeit:    12.074859 s
Speicherbedarf:     4.141861 MiB
Berechnungsmethode: Jacobi
Interlines:         64
Stoerfunktion:      f(x,y) = 0
Terminierung:       Anzahl der Iterationen
Anzahl Iterationen: 10240
Norm des Fehlers:   2.753424e-05

Matrix:
 1.0000 0.8750 0.7500 0.6250 0.5000 0.3750 0.2500 0.1250 0.0000
 0.8750 0.5042 0.3082 0.2306 0.1820 0.1372 0.0996 0.0909 0.1250
 0.7500 0.3082 0.0991 0.0477 0.0349 0.0276 0.0346 0.0996 0.2500
 0.6250 0.2306 0.0477 0.0080 0.0035 0.0048 0.0276 0.1372 0.3750
 0.5000 0.1820 0.0349 0.0035 0.0006 0.0035 0.0349 0.1820 0.5000
 0.3750 0.1372 0.0276 0.0048 0.0035 0.0080 0.0477 0.2306 0.6250
 0.2500 0.0996 0.0346 0.0276 0.0349 0.0477 0.0991 0.3082 0.7500
 0.1250 0.0909 0.0996 0.1372 0.1820 0.2306 0.3082 0.5042 0.8750
 0.0000 0.1250 0.2500 0.3750 0.5000 0.6250 0.7500 0.8750 1.0000
./partdiff 1 2 64 1 2 10240  12.06s user 0.00s system 99% cpu 12.078 total
```

```
% time ./partdiff 1 2 64 2 2 5120 
Berechnungszeit:    27.572394 s
Speicherbedarf:     4.141861 MiB
Berechnungsmethode: Jacobi
Interlines:         64
Stoerfunktion:      f(x,y) = 2 * pi^2 * sin(pi * x) * sin(pi * y)
Terminierung:       Anzahl der Iterationen
Anzahl Iterationen: 5120
Norm des Fehlers:   1.662227e-05

Matrix:
 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000
 0.0000 0.0131 0.0241 0.0315 0.0341 0.0315 0.0241 0.0131 0.0000
 0.0000 0.0241 0.0446 0.0583 0.0631 0.0583 0.0446 0.0241 0.0000
 0.0000 0.0315 0.0583 0.0761 0.0824 0.0761 0.0583 0.0315 0.0000
 0.0000 0.0341 0.0631 0.0824 0.0892 0.0824 0.0631 0.0341 0.0000
 0.0000 0.0315 0.0583 0.0761 0.0824 0.0761 0.0583 0.0315 0.0000
 0.0000 0.0241 0.0446 0.0583 0.0631 0.0583 0.0446 0.0241 0.0000
 0.0000 0.0131 0.0241 0.0315 0.0341 0.0315 0.0241 0.0131 0.0000
 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000
./partdiff 1 2 64 2 2 5120  27.53s user 0.00s system 99% cpu 27.575 total
```

## -O3
```% cc -std=c11 -Wall -Wextra -Wpedantic -O3 -o partdiff -lm partdiff.c```
```
% time ./partdiff 1 2 64 1 2 10240
Berechnungszeit:    12.144606 s
Speicherbedarf:     4.141861 MiB
Berechnungsmethode: Jacobi
Interlines:         64
Stoerfunktion:      f(x,y) = 0
Terminierung:       Anzahl der Iterationen
Anzahl Iterationen: 10240
Norm des Fehlers:   2.753424e-05

Matrix:
 1.0000 0.8750 0.7500 0.6250 0.5000 0.3750 0.2500 0.1250 0.0000
 0.8750 0.5042 0.3082 0.2306 0.1820 0.1372 0.0996 0.0909 0.1250
 0.7500 0.3082 0.0991 0.0477 0.0349 0.0276 0.0346 0.0996 0.2500
 0.6250 0.2306 0.0477 0.0080 0.0035 0.0048 0.0276 0.1372 0.3750
 0.5000 0.1820 0.0349 0.0035 0.0006 0.0035 0.0349 0.1820 0.5000
 0.3750 0.1372 0.0276 0.0048 0.0035 0.0080 0.0477 0.2306 0.6250
 0.2500 0.0996 0.0346 0.0276 0.0349 0.0477 0.0991 0.3082 0.7500
 0.1250 0.0909 0.0996 0.1372 0.1820 0.2306 0.3082 0.5042 0.8750
 0.0000 0.1250 0.2500 0.3750 0.5000 0.6250 0.7500 0.8750 1.0000
./partdiff 1 2 64 1 2 10240  12.11s user 0.00s system 99% cpu 12.147 total
```

```
% time ./partdiff 1 2 64 2 2 5120 
Berechnungszeit:    17.013855 s
Speicherbedarf:     4.141861 MiB
Berechnungsmethode: Jacobi
Interlines:         64
Stoerfunktion:      f(x,y) = 2 * pi^2 * sin(pi * x) * sin(pi * y)
Terminierung:       Anzahl der Iterationen
Anzahl Iterationen: 5120
Norm des Fehlers:   1.662227e-05

Matrix:
 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000
 0.0000 0.0131 0.0241 0.0315 0.0341 0.0315 0.0241 0.0131 0.0000
 0.0000 0.0241 0.0446 0.0583 0.0631 0.0583 0.0446 0.0241 0.0000
 0.0000 0.0315 0.0583 0.0761 0.0824 0.0761 0.0583 0.0315 0.0000
 0.0000 0.0341 0.0631 0.0824 0.0892 0.0824 0.0631 0.0341 0.0000
 0.0000 0.0315 0.0583 0.0761 0.0824 0.0761 0.0583 0.0315 0.0000
 0.0000 0.0241 0.0446 0.0583 0.0631 0.0583 0.0446 0.0241 0.0000
 0.0000 0.0131 0.0241 0.0315 0.0341 0.0315 0.0241 0.0131 0.0000
 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000
./partdiff 1 2 64 2 2 5120  16.99s user 0.00s system 99% cpu 17.017 total
```

## -O3 -march=native (haswell)

```% cc -std=c11 -Wall -Wextra -Wpedantic -O3 -march=native -o partdiff -lm partdiff.c```
```
% time ./partdiff 1 2 64 1 2 10240
Berechnungszeit:    11.898758 s
Speicherbedarf:     4.141861 MiB
Berechnungsmethode: Jacobi
Interlines:         64
Stoerfunktion:      f(x,y) = 0
Terminierung:       Anzahl der Iterationen
Anzahl Iterationen: 10240
Norm des Fehlers:   2.753424e-05

Matrix:
 1.0000 0.8750 0.7500 0.6250 0.5000 0.3750 0.2500 0.1250 0.0000
 0.8750 0.5042 0.3082 0.2306 0.1820 0.1372 0.0996 0.0909 0.1250
 0.7500 0.3082 0.0991 0.0477 0.0349 0.0276 0.0346 0.0996 0.2500
 0.6250 0.2306 0.0477 0.0080 0.0035 0.0048 0.0276 0.1372 0.3750
 0.5000 0.1820 0.0349 0.0035 0.0006 0.0035 0.0349 0.1820 0.5000
 0.3750 0.1372 0.0276 0.0048 0.0035 0.0080 0.0477 0.2306 0.6250
 0.2500 0.0996 0.0346 0.0276 0.0349 0.0477 0.0991 0.3082 0.7500
 0.1250 0.0909 0.0996 0.1372 0.1820 0.2306 0.3082 0.5042 0.8750
 0.0000 0.1250 0.2500 0.3750 0.5000 0.6250 0.7500 0.8750 1.0000
./partdiff 1 2 64 1 2 10240  11.87s user 0.00s system 99% cpu 11.901 total
```

```
% time ./partdiff 1 2 64 2 2 5120
Berechnungszeit:    16.659710 s
Speicherbedarf:     4.141861 MiB
Berechnungsmethode: Jacobi
Interlines:         64
Stoerfunktion:      f(x,y) = 2 * pi^2 * sin(pi * x) * sin(pi * y)
Terminierung:       Anzahl der Iterationen
Anzahl Iterationen: 5120
Norm des Fehlers:   1.662227e-05

Matrix:
 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000
 0.0000 0.0131 0.0241 0.0315 0.0341 0.0315 0.0241 0.0131 0.0000
 0.0000 0.0241 0.0446 0.0583 0.0631 0.0583 0.0446 0.0241 0.0000
 0.0000 0.0315 0.0583 0.0761 0.0824 0.0761 0.0583 0.0315 0.0000
 0.0000 0.0341 0.0631 0.0824 0.0892 0.0824 0.0631 0.0341 0.0000
 0.0000 0.0315 0.0583 0.0761 0.0824 0.0761 0.0583 0.0315 0.0000
 0.0000 0.0241 0.0446 0.0583 0.0631 0.0583 0.0446 0.0241 0.0000
 0.0000 0.0131 0.0241 0.0315 0.0341 0.0315 0.0241 0.0131 0.0000
 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000
./partdiff 1 2 64 2 2 5120  16.63s user 0.00s system 99% cpu 16.662 total
```

## -Ofast -march=native

```
% cc -std=c11 -Wall -Wextra -Wpedantic -Ofast -march=native -c -o partdiff.o partdiff.c
% cc -std=c11 -Wall -Wextra -Wpedantic -Ofast -march=native partdiff.o -lm -o partdiff
```
```
% time ./partdiff 1 2 64 1 2 10240
Berechnungszeit:    11.764466 s
Speicherbedarf:     4.141861 MiB
Berechnungsmethode: Jacobi
Interlines:         64
Stoerfunktion:      f(x,y) = 0
Terminierung:       Anzahl der Iterationen
Anzahl Iterationen: 10240
Norm des Fehlers:   2.753424e-05

Matrix:
 1.0000 0.8750 0.7500 0.6250 0.5000 0.3750 0.2500 0.1250 0.0000
 0.8750 0.5042 0.3082 0.2306 0.1820 0.1372 0.0996 0.0909 0.1250
 0.7500 0.3082 0.0991 0.0477 0.0349 0.0276 0.0346 0.0996 0.2500
 0.6250 0.2306 0.0477 0.0080 0.0035 0.0048 0.0276 0.1372 0.3750
 0.5000 0.1820 0.0349 0.0035 0.0006 0.0035 0.0349 0.1820 0.5000
 0.3750 0.1372 0.0276 0.0048 0.0035 0.0080 0.0477 0.2306 0.6250
 0.2500 0.0996 0.0346 0.0276 0.0349 0.0477 0.0991 0.3082 0.7500
 0.1250 0.0909 0.0996 0.1372 0.1820 0.2306 0.3082 0.5042 0.8750
 0.0000 0.1250 0.2500 0.3750 0.5000 0.6250 0.7500 0.8750 1.0000
./partdiff 1 2 64 1 2 10240  11.74s user 0.00s system 99% cpu 11.768 total
```

```
% time ./partdiff 1 2 64 2 2 5120 
Berechnungszeit:    7.473932 s
Speicherbedarf:     4.141861 MiB
Berechnungsmethode: Jacobi
Interlines:         64
Stoerfunktion:      f(x,y) = 2 * pi^2 * sin(pi * x) * sin(pi * y)
Terminierung:       Anzahl der Iterationen
Anzahl Iterationen: 5120
Norm des Fehlers:   1.662227e-05

Matrix:
 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000
 0.0000 0.0131 0.0241 0.0315 0.0341 0.0315 0.0241 0.0131 0.0000
 0.0000 0.0241 0.0446 0.0583 0.0631 0.0583 0.0446 0.0241 0.0000
 0.0000 0.0315 0.0583 0.0761 0.0824 0.0761 0.0583 0.0315 0.0000
 0.0000 0.0341 0.0631 0.0824 0.0892 0.0824 0.0631 0.0341 0.0000
 0.0000 0.0315 0.0583 0.0761 0.0824 0.0761 0.0583 0.0315 0.0000
 0.0000 0.0241 0.0446 0.0583 0.0631 0.0583 0.0446 0.0241 0.0000
 0.0000 0.0131 0.0241 0.0315 0.0341 0.0315 0.0241 0.0131 0.0000
 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000
./partdiff 1 2 64 2 2 5120  7.46s user 0.00s system 99% cpu 7.477 total
```

## -Ofast -march=native -flto

```
% cc -std=c11 -Wall -Wextra -Wpedantic -Ofast -march=native -flto -c -o partdiff.o partdiff.c
% cc -std=c11 -Wall -Wextra -Wpedantic -Ofast -march=native -flto partdiff.o -lm -o partdiff
```
```
% time ./partdiff 1 2 64 1 2 10240
Berechnungszeit:    12.136541 s
Speicherbedarf:     4.141861 MiB
Berechnungsmethode: Jacobi
Interlines:         64
Stoerfunktion:      f(x,y) = 0
Terminierung:       Anzahl der Iterationen
Anzahl Iterationen: 10240
Norm des Fehlers:   2.753424e-05

Matrix:
 1.0000 0.8750 0.7500 0.6250 0.5000 0.3750 0.2500 0.1250 0.0000
 0.8750 0.5042 0.3082 0.2306 0.1820 0.1372 0.0996 0.0909 0.1250
 0.7500 0.3082 0.0991 0.0477 0.0349 0.0276 0.0346 0.0996 0.2500
 0.6250 0.2306 0.0477 0.0080 0.0035 0.0048 0.0276 0.1372 0.3750
 0.5000 0.1820 0.0349 0.0035 0.0006 0.0035 0.0349 0.1820 0.5000
 0.3750 0.1372 0.0276 0.0048 0.0035 0.0080 0.0477 0.2306 0.6250
 0.2500 0.0996 0.0346 0.0276 0.0349 0.0477 0.0991 0.3082 0.7500
 0.1250 0.0909 0.0996 0.1372 0.1820 0.2306 0.3082 0.5042 0.8750
 0.0000 0.1250 0.2500 0.3750 0.5000 0.6250 0.7500 0.8750 1.0000
./partdiff 1 2 64 1 2 10240  12.12s user 0.00s system 99% cpu 12.144 total
```

```
% time ./partdiff 1 2 64 2 2 5120 
Berechnungszeit:    7.102181 s
Speicherbedarf:     4.141861 MiB
Berechnungsmethode: Jacobi
Interlines:         64
Stoerfunktion:      f(x,y) = 2 * pi^2 * sin(pi * x) * sin(pi * y)
Terminierung:       Anzahl der Iterationen
Anzahl Iterationen: 5120
Norm des Fehlers:   1.662227e-05

Matrix:
 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000
 0.0000 0.0131 0.0241 0.0315 0.0341 0.0315 0.0241 0.0131 0.0000
 0.0000 0.0241 0.0446 0.0583 0.0631 0.0583 0.0446 0.0241 0.0000
 0.0000 0.0315 0.0583 0.0761 0.0824 0.0761 0.0583 0.0315 0.0000
 0.0000 0.0341 0.0631 0.0824 0.0892 0.0824 0.0631 0.0341 0.0000
 0.0000 0.0315 0.0583 0.0761 0.0824 0.0761 0.0583 0.0315 0.0000
 0.0000 0.0241 0.0446 0.0583 0.0631 0.0583 0.0446 0.0241 0.0000
 0.0000 0.0131 0.0241 0.0315 0.0341 0.0315 0.0241 0.0131 0.0000
 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000
./partdiff 1 2 64 2 2 5120  7.09s user 0.00s system 99% cpu 7.105 total
```

## -Ofast -march=native -flto + PGO

```
% cc -std=c11 -Wall -Wextra -Wpedantic -Ofast -march=native -flto -fprofile-generate=./ -c -o partdiff.o partdiff.c
% cc -std=c11 -Wall -Wextra -Wpedantic -Ofast -march=native -flto -fprofile-generate=./ partdiff.o -lm -o partdiff
% ./partdiff 1 2 64 1 2 10240 > /dev/zero
% ./partdiff 1 2 64 2 2 5120 > /dev/zero
% make clean > /dev/zero
% cc -std=c11 -Wall -Wextra -Wpedantic -Ofast -march=native -flto -fprofile-use=./ -c -o partdiff.o partdiff.c
% cc -std=c11 -Wall -Wextra -Wpedantic -Ofast -march=native -flto -fprofile-use=./ partdiff.o -lm -o partdiff
```

```
% time ./partdiff 1 2 64 1 2 10240
Berechnungszeit:    11.608513 s
Speicherbedarf:     4.141861 MiB
Berechnungsmethode: Jacobi
Interlines:         64
Stoerfunktion:      f(x,y) = 0
Terminierung:       Anzahl der Iterationen
Anzahl Iterationen: 10240
Norm des Fehlers:   2.753424e-05

Matrix:
 1.0000 0.8750 0.7500 0.6250 0.5000 0.3750 0.2500 0.1250 0.0000
 0.8750 0.5042 0.3082 0.2306 0.1820 0.1372 0.0996 0.0909 0.1250
 0.7500 0.3082 0.0991 0.0477 0.0349 0.0276 0.0346 0.0996 0.2500
 0.6250 0.2306 0.0477 0.0080 0.0035 0.0048 0.0276 0.1372 0.3750
 0.5000 0.1820 0.0349 0.0035 0.0006 0.0035 0.0349 0.1820 0.5000
 0.3750 0.1372 0.0276 0.0048 0.0035 0.0080 0.0477 0.2306 0.6250
 0.2500 0.0996 0.0346 0.0276 0.0349 0.0477 0.0991 0.3082 0.7500
 0.1250 0.0909 0.0996 0.1372 0.1820 0.2306 0.3082 0.5042 0.8750
 0.0000 0.1250 0.2500 0.3750 0.5000 0.6250 0.7500 0.8750 1.0000
./partdiff 1 2 64 1 2 10240  11.58s user 0.00s system 99% cpu 11.611 total
```

```
% time ./partdiff 1 2 64 2 2 5120 
Berechnungszeit:    7.229841 s
Speicherbedarf:     4.141861 MiB
Berechnungsmethode: Jacobi
Interlines:         64
Stoerfunktion:      f(x,y) = 2 * pi^2 * sin(pi * x) * sin(pi * y)
Terminierung:       Anzahl der Iterationen
Anzahl Iterationen: 5120
Norm des Fehlers:   1.662227e-05

Matrix:
 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000
 0.0000 0.0131 0.0241 0.0315 0.0341 0.0315 0.0241 0.0131 0.0000
 0.0000 0.0241 0.0446 0.0583 0.0631 0.0583 0.0446 0.0241 0.0000
 0.0000 0.0315 0.0583 0.0761 0.0824 0.0761 0.0583 0.0315 0.0000
 0.0000 0.0341 0.0631 0.0824 0.0892 0.0824 0.0631 0.0341 0.0000
 0.0000 0.0315 0.0583 0.0761 0.0824 0.0761 0.0583 0.0315 0.0000
 0.0000 0.0241 0.0446 0.0583 0.0631 0.0583 0.0446 0.0241 0.0000
 0.0000 0.0131 0.0241 0.0315 0.0341 0.0315 0.0241 0.0131 0.0000
 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000
./partdiff 1 2 64 2 2 5120  7.22s user 0.00s system 99% cpu 7.233 total
```

# Auswertung Compiler-Flags
Zur Hilfenahme einiger Compilerflags haben wir bei `./partdiff 1 2 64 1 2
10240` einen Speedup von ~3,5 und bei `./partdiff 1 2 64 2 2 5120 ` einen von
~6,9 erreicht. Das sieht schon mal gar nicht schlecht aus, aber da geht noch
mehr.

# Profiling
Mit dem Programm `gprof` kann man sich ein Profil der Ausführzeiten eines
Programmes, z.B. innerhalb von Funktionen, anzeigen lassen. Dafür haben wir das
Makefile um die Option `-pg` ergänzt, um das Profiling zu aktivieren, und die
Option `-O0` mit `-Og` ersetzt, um schneller Ergebnisse zu erzielen.

```
% make      
cc -std=c11 -Wall -Wextra -Wpedantic -Og -g -pg   -c -o partdiff.o partdiff.c
cc -std=c11 -Wall -Wextra -Wpedantic -Og -g -pg  partdiff.o  -lm -o partdiff
% ./partdiff 1 2 64 1 2 10240
Berechnungszeit:    43.397918 s
Speicherbedarf:     4.141861 MiB
Berechnungsmethode: Jacobi
Interlines:         64
Stoerfunktion:      f(x,y) = 0
Terminierung:       Anzahl der Iterationen
Anzahl Iterationen: 10240
Norm des Fehlers:   2.753424e-05

Matrix:
 1.0000 0.8750 0.7500 0.6250 0.5000 0.3750 0.2500 0.1250 0.0000
 0.8750 0.5042 0.3082 0.2306 0.1820 0.1372 0.0996 0.0909 0.1250
 0.7500 0.3082 0.0991 0.0477 0.0349 0.0276 0.0346 0.0996 0.2500
 0.6250 0.2306 0.0477 0.0080 0.0035 0.0048 0.0276 0.1372 0.3750
 0.5000 0.1820 0.0349 0.0035 0.0006 0.0035 0.0349 0.1820 0.5000
 0.3750 0.1372 0.0276 0.0048 0.0035 0.0080 0.0477 0.2306 0.6250
 0.2500 0.0996 0.0346 0.0276 0.0349 0.0477 0.0991 0.3082 0.7500
 0.1250 0.0909 0.0996 0.1372 0.1820 0.2306 0.3082 0.5042 0.8750
 0.0000 0.1250 0.2500 0.3750 0.5000 0.6250 0.7500 0.8750 1.0000
% gprof ./partdiff   
Flat profile:

Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls   s/call   s/call  name    
 81.83     10.89    10.89        1    10.89    12.99  calculate
 15.76     12.99     2.10 2758256640     0.00     0.00  calculate_func
  2.52     13.32     0.34        1     0.34     0.34  freeMatrices
  0.00     13.32     0.00        1     0.00     0.00  allocateMatrices
  0.00     13.32     0.00        1     0.00     0.00  allocateMemory
  0.00     13.32     0.00        1     0.00     0.00  askParams
  0.00     13.32     0.00        1     0.00     0.00  displayMatrix
  0.00     13.32     0.00        1     0.00     0.00  displayStatistics
  0.00     13.32     0.00        1     0.00     0.00  initMatrices
  0.00     13.32     0.00        1     0.00     0.00  initVariables

 %         the percentage of the total running time of the
time       program used by this function.

cumulative a running sum of the number of seconds accounted
 seconds   for by this function and those listed above it.

 self      the number of seconds accounted for by this
seconds    function alone.  This is the major sort for this
           listing.

calls      the number of times this function was invoked, if
           this function is profiled, else blank.

 self      the average number of milliseconds spent in this
ms/call    function per call, if this function is profiled,
	   else blank.

 total     the average number of milliseconds spent in this
ms/call    function and its descendents per call, if this
	   function is profiled, else blank.

name       the name of the function.  This is the minor sort
           for this listing. The index shows the location of
	   the function in the gprof listing. If the index is
	   in parenthesis it shows where it would appear in
	   the gprof listing if it were to be printed.


Copyright (C) 2012-2020 Free Software Foundation, Inc.

Copying and distribution of this file, with or without modification,
are permitted in any medium without royalty provided the copyright
notice and this notice are preserved.


		     Call graph (explanation follows)


granularity: each sample hit covers 2 byte(s) for 0.08% of 13.32 seconds

index % time    self  children    called     name
                                                 <spontaneous>
[1]    100.0    0.00   13.32                 main [1]
               10.89    2.10       1/1           calculate [2]
                0.34    0.00       1/1           freeMatrices [4]
                0.00    0.00       1/1           askParams [7]
                0.00    0.00       1/1           initVariables [11]
                0.00    0.00       1/1           initMatrices [10]
                0.00    0.00       1/1           allocateMatrices [5]
                0.00    0.00       1/1           displayStatistics [9]
                0.00    0.00       1/1           displayMatrix [8]
-----------------------------------------------
               10.89    2.10       1/1           main [1]
[2]     97.5   10.89    2.10       1         calculate [2]
                2.10    0.00 2758256640/2758256640     calculate_func [3]
-----------------------------------------------
                2.10    0.00 2758256640/2758256640     calculate [2]
[3]     15.7    2.10    0.00 2758256640         calculate_func [3]
-----------------------------------------------
                0.34    0.00       1/1           main [1]
[4]      2.5    0.34    0.00       1         freeMatrices [4]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[5]      0.0    0.00    0.00       1         allocateMatrices [5]
                0.00    0.00       1/1           allocateMemory [6]
-----------------------------------------------
                0.00    0.00       1/1           allocateMatrices [5]
[6]      0.0    0.00    0.00       1         allocateMemory [6]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[7]      0.0    0.00    0.00       1         askParams [7]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[8]      0.0    0.00    0.00       1         displayMatrix [8]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[9]      0.0    0.00    0.00       1         displayStatistics [9]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[10]     0.0    0.00    0.00       1         initMatrices [10]
-----------------------------------------------
                0.00    0.00       1/1           main [1]
[11]     0.0    0.00    0.00       1         initVariables [11]
-----------------------------------------------

 This table describes the call tree of the program, and was sorted by
 the total amount of time spent in each function and its children.

 Each entry in this table consists of several lines.  The line with the
 index number at the left hand margin lists the current function.
 The lines above it list the functions that called this function,
 and the lines below it list the functions this one called.
 This line lists:
     index	A unique number given to each element of the table.
		Index numbers are sorted numerically.
		The index number is printed next to every function name so
		it is easier to look up where the function is in the table.

     % time	This is the percentage of the `total' time that was spent
		in this function and its children.  Note that due to
		different viewpoints, functions excluded by options, etc,
		these numbers will NOT add up to 100%.

     self	This is the total amount of time spent in this function.

     children	This is the total amount of time propagated into this
		function by its children.

     called	This is the number of times the function was called.
		If the function called itself recursively, the number
		only includes non-recursive calls, and is followed by
		a `+' and the number of recursive calls.

     name	The name of the current function.  The index number is
		printed after it.  If the function is a member of a
		cycle, the cycle number is printed between the
		function's name and the index number.


 For the function's parents, the fields have the following meanings:

     self	This is the amount of time that was propagated directly
		from the function into this parent.

     children	This is the amount of time that was propagated from
		the function's children into this parent.

     called	This is the number of times this parent called the
		function `/' the total number of times the function
		was called.  Recursive calls to the function are not
		included in the number after the `/'.

     name	This is the name of the parent.  The parent's index
		number is printed after it.  If the parent is a
		member of a cycle, the cycle number is printed between
		the name and the index number.

 If the parents of the function cannot be determined, the word
 `<spontaneous>' is printed in the `name' field, and all the other
 fields are blank.

 For the function's children, the fields have the following meanings:

     self	This is the amount of time that was propagated directly
		from the child into the function.

     children	This is the amount of time that was propagated from the
		child's children to the function.

     called	This is the number of times the function called
		this child `/' the total number of times the child
		was called.  Recursive calls by the child are not
		listed in the number after the `/'.

     name	This is the name of the child.  The child's index
		number is printed after it.  If the child is a
		member of a cycle, the cycle number is printed
		between the name and the index number.

 If there are any cycles (circles) in the call graph, there is an
 entry for the cycle-as-a-whole.  This entry shows who called the
 cycle (as parents) and the members of the cycle (as children.)
 The `+' recursive calls entry shows the number of function calls that
 were internal to the cycle, and the calls entry for each member shows,
 for that member, how many times it was called from other members of
 the cycle.


Copyright (C) 2012-2020 Free Software Foundation, Inc.

Copying and distribution of this file, with or without modification,
are permitted in any medium without royalty provided the copyright
notice and this notice are preserved.


Index by function name

   [5] allocateMatrices (partdiff.c) [3] calculate_func   [10] initMatrices (partdiff.c)
   [6] allocateMemory (partdiff.c) [8] displayMatrix (partdiff.c) [11] initVariables (partdiff.c)
   [7] askParams (partdiff.c)  [9] displayStatistics (partdiff.c)
   [2] calculate (partdiff.c)  [4] freeMatrices (partdiff.c)
```

In der Ausgabe von `gprof` sieht man, dass ein Großteil der Zeit in der
`calculate`-Funktion verbracht wird. Des Weiteren wird die
`calculate_func`-Funktion sehr oft aufgerufen. Auf den höheren
Optimierungsstufen wird `calculate_func` höchstwahrscheinlich automatisch
geinlined, allerdings ist die Funktion relative kurz und hat nur einen Branch,
also sagen wir dem Compiler, dass er die Funktion doch bitte inlinen soll mit
`static inline`.

Das ergibt dann folgenden diff:
```
--- a/partdiff.c
+++ b/partdiff.c
@@ -289,7 +289,7 @@ initMatrices(struct calculation_arguments* arguments, struct options const* opti
 /* ************************************************************************ */
 /* calculate_func: calculates the interference function                     */
 /* ************************************************************************ */
-double
+static inline double
 calculate_func(struct calculation_arguments const* arguments, struct options const* options, int i, int j)
 {
        double const h = arguments->h;
```

Jetzt profilen wir das Programm erneut:
```
% make clean
rm -f partdiff.o partdiff
% make      
cc -std=c11 -Wall -Wextra -Wpedantic -Og -g -pg   -c -o partdiff.o partdiff.c
cc -std=c11 -Wall -Wextra -Wpedantic -Og -g -pg  partdiff.o  -lm -o partdiff
% ./partdiff 1 2 64 1 2 10240
Berechnungszeit:    14.816419 s
...
% gprof ./partdiff
Flat profile:

Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls   s/call   s/call  name    
100.11     14.80    14.80        1    14.80    14.80  calculate
  0.00     14.80     0.00        1     0.00     0.00  allocateMatrices
  0.00     14.80     0.00        1     0.00     0.00  allocateMemory
  0.00     14.80     0.00        1     0.00     0.00  askParams
  0.00     14.80     0.00        1     0.00     0.00  displayMatrix
  0.00     14.80     0.00        1     0.00     0.00  displayStatistics
  0.00     14.80     0.00        1     0.00     0.00  freeMatrices
  0.00     14.80     0.00        1     0.00     0.00  initMatrices
  0.00     14.80     0.00        1     0.00     0.00  initVariables
```

Das hat uns, wie erwartet, etwas näher an die höheren Compiler-Flags
herangebracht. Wir wissen jetzt auch, dass das Problem definitiv in `calculate`
ist, allerdings nicht wo genau. Vielleich kann uns ja `perf` helfen?

```
% perf stat ./partdiff 1 2 64 1 2 10240
Berechnungszeit:    15.185243 s
Speicherbedarf:     4.141861 MiB
Berechnungsmethode: Jacobi
Interlines:         64
Stoerfunktion:      f(x,y) = 0
Terminierung:       Anzahl der Iterationen
Anzahl Iterationen: 10240
Norm des Fehlers:   2.753424e-05

Matrix:
 1.0000 0.8750 0.7500 0.6250 0.5000 0.3750 0.2500 0.1250 0.0000
 0.8750 0.5042 0.3082 0.2306 0.1820 0.1372 0.0996 0.0909 0.1250
 0.7500 0.3082 0.0991 0.0477 0.0349 0.0276 0.0346 0.0996 0.2500
 0.6250 0.2306 0.0477 0.0080 0.0035 0.0048 0.0276 0.1372 0.3750
 0.5000 0.1820 0.0349 0.0035 0.0006 0.0035 0.0349 0.1820 0.5000
 0.3750 0.1372 0.0276 0.0048 0.0035 0.0080 0.0477 0.2306 0.6250
 0.2500 0.0996 0.0346 0.0276 0.0349 0.0477 0.0991 0.3082 0.7500
 0.1250 0.0909 0.0996 0.1372 0.1820 0.2306 0.3082 0.5042 0.8750
 0.0000 0.1250 0.2500 0.3750 0.5000 0.6250 0.7500 0.8750 1.0000

 Performance counter stats for './partdiff 1 2 64 1 2 10240':

         15,187.31 msec task-clock:u              #    1.000 CPUs utilized          
                 0      context-switches:u        #    0.000 K/sec                  
                 0      cpu-migrations:u          #    0.000 K/sec                  
             1,126      page-faults:u             #    0.074 K/sec                  
    69,390,489,462      cycles:u                  #    4.569 GHz                    
   160,040,212,630      instructions:u            #    2.31  insn per cycle         
     8,300,125,555      branches:u                #  546.517 M/sec                  
         6,468,835      branch-misses:u           #    0.08% of all branches        

      15.187886356 seconds time elapsed

      15.145942000 seconds user
       0.001993000 seconds sys


perf stat ./partdiff 1 2 64 1 2 10240  15.16s user 0.01s system 99% cpu 15.224 total
```

Hier sehen wir sofort, dass das Programm nur einen Prozessorkern auslastet:
`15,187.31 msec task-clock:u # 1.000 CPUs`. Das ist jetzt aber nicht so einfach
zu beheben, also schauen wir weiter. Wir haben keine context-switches oder
migrations, daran kann es also nicht liegen. Die branch-misses sind auch in
einem akzeptablen Rahmen.

Auf dem Aufgabenblatt wird erwähnt dass es wahrscheinlich
Speicherzugriffsprobleme gibt, und ein Blick in `calculate` zeigt, dass durch
die Matrix M in column-major order iteriert wird:
```
/* over all columns */
                for (j = 1; j < N; j++)
                {
                        /* over all rows */
                        for (i = 1; i < N; i++)
                        {
```
In C wird eine Matrix in row-major order im Arbeitsspeicher hinterlegt. Über so
eine Matrix in column-major order zu iterieren, bedeutet dass die
Speicherzugriffe nicht strikt inkrementell, sondern mit großen Sprüngen und
Lücken erfolgen. Das führt dann zu zahlreichen cache-misses. Beheben wir also
das Problem:

```
--- a/partdiff.c
+++ b/partdiff.c
@@ -340,11 +340,11 @@ calculate(struct calculation_arguments const* arguments, struct calculation_resu
        {
                maxresiduum = 0;
 
-               /* over all columns */
-               for (j = 1; j < N; j++)
+               /* over all rows */
+               for (i = 1; i < N; i++)
                {
-                       /* over all rows */
-                       for (i = 1; i < N; i++)
+                       /* over all columns */
+                       for (j = 1; j < N; j++)
                        {
                                star = (Matrix[m2][i - 1][j] + Matrix[m2][i][j - 1] + Matrix[m2][i][j + 1] + Matrix[m2][i + 1][j]) / 4;
```

Jetzt kompilieren wir `partdiff` erneut wie in -O3 -march=native -flto + PGO:
```
% cc -std=c11 -Wall -Wextra -Wpedantic -Ofast -march=native -flto -fprofile-generate=./ -c -o partdiff.o partdiff.c
% cc -std=c11 -Wall -Wextra -Wpedantic -Ofast -march=native -flto -fprofile-generate=./ partdiff.o -lm -o partdiff
% ./partdiff 1 2 64 1 2 10240 > /dev/zero
% ./partdiff 1 2 64 2 2 5120 > /dev/zero
% make clean > /dev/zero
% cc -std=c11 -Wall -Wextra -Wpedantic -Ofast -march=native -flto -fprofile-use=./ -c -o partdiff.o partdiff.c
% cc -std=c11 -Wall -Wextra -Wpedantic -Ofast -march=native -flto -fprofile-use=./ partdiff.o -lm -o partdiff
```

```
% time ./partdiff 1 2 64 1 2 10240
Berechnungszeit:    1.366247 s
Speicherbedarf:     4.141861 MiB
Berechnungsmethode: Jacobi
Interlines:         64
Stoerfunktion:      f(x,y) = 0
Terminierung:       Anzahl der Iterationen
Anzahl Iterationen: 10240
Norm des Fehlers:   2.753424e-05

Matrix:
 1.0000 0.8750 0.7500 0.6250 0.5000 0.3750 0.2500 0.1250 0.0000
 0.8750 0.5042 0.3082 0.2306 0.1820 0.1372 0.0996 0.0909 0.1250
 0.7500 0.3082 0.0991 0.0477 0.0349 0.0276 0.0346 0.0996 0.2500
 0.6250 0.2306 0.0477 0.0080 0.0035 0.0048 0.0276 0.1372 0.3750
 0.5000 0.1820 0.0349 0.0035 0.0006 0.0035 0.0349 0.1820 0.5000
 0.3750 0.1372 0.0276 0.0048 0.0035 0.0080 0.0477 0.2306 0.6250
 0.2500 0.0996 0.0346 0.0276 0.0349 0.0477 0.0991 0.3082 0.7500
 0.1250 0.0909 0.0996 0.1372 0.1820 0.2306 0.3082 0.5042 0.8750
 0.0000 0.1250 0.2500 0.3750 0.5000 0.6250 0.7500 0.8750 1.0000
./partdiff 1 2 64 1 2 10240  1.36s user 0.00s system 99% cpu 1.369 total
```

```
% time ./partdiff 1 2 64 2 2 5120 
Berechnungszeit:    3.048801 s
Speicherbedarf:     4.141861 MiB
Berechnungsmethode: Jacobi
Interlines:         64
Stoerfunktion:      f(x,y) = 2 * pi^2 * sin(pi * x) * sin(pi * y)
Terminierung:       Anzahl der Iterationen
Anzahl Iterationen: 5120
Norm des Fehlers:   1.662227e-05

Matrix:
 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000
 0.0000 0.0131 0.0241 0.0315 0.0341 0.0315 0.0241 0.0131 0.0000
 0.0000 0.0241 0.0446 0.0583 0.0631 0.0583 0.0446 0.0241 0.0000
 0.0000 0.0315 0.0583 0.0761 0.0824 0.0761 0.0583 0.0315 0.0000
 0.0000 0.0341 0.0631 0.0824 0.0892 0.0824 0.0631 0.0341 0.0000
 0.0000 0.0315 0.0583 0.0761 0.0824 0.0761 0.0583 0.0315 0.0000
 0.0000 0.0241 0.0446 0.0583 0.0631 0.0583 0.0446 0.0241 0.0000
 0.0000 0.0131 0.0241 0.0315 0.0341 0.0315 0.0241 0.0131 0.0000
 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000 0.0000
./partdiff 1 2 64 2 2 5120  3.04s user 0.00s system 99% cpu 3.052 total
```

Wir erreichen einen Speedup von ~30 für die erste Variante und ~16,3 für die
zweite.

# Mehr Benchmarks (auf dem Cluster)

Mit Hilfe von `hyperfine` kann man Benchmarks durchführen. Mit folgendem
Kommando haben wir auf einer Node des Clusters den Ausgangszustand und die
optimierte Variante verglichen:
```
% srun hyperfine -w=1 --export-markdown='run1.md' -n 'Ausgangszustand' -p "make clean && make" "./partdiff 1 2 64 1 2 10240" -n 'Optimiert' -p "./build.sh" "./partdiff_new 1 2 64 1 2 10240"
```
Folgende Vergleichstabelle wurde von `hyperfine` erzeugt:

| Command | Mean [s] | Min [s] | Max [s] | Relative |
|:---|---:|---:|---:|---:|
| `Ausgangszustand` | 40.195 ± 0.065 | 40.043 | 40.251 | 43.62 ± 0.58 |
| `Optimiert` | 0.922 ± 0.012 | 0.900 | 0.935 | 1.00 |

Und für Variante 2:
```
% srun hyperfine -w=1 --export-markdown='run1.md' -n 'Ausgangszustand' -p "make clean && make" "./partdiff 1 2 64 2 2 5120" -n 'Optimiert' -p "./build.sh" "./partdiff_new 1 2 64 2 2 5120"
```

| Command | Mean [s] | Min [s] | Max [s] | Relative |
|:---|---:|---:|---:|---:|
| `Ausgangszustand` | 49.013 ± 0.026 | 48.984 | 49.069 | 21.10 ± 0.26 |
| `Optimiert` | 2.323 ± 0.029 | 2.307 | 2.403 | 1.00 |


Es wurde das Makefile im Ausgangszustand verwendet.
`build.sh` ist in der Abgabe enthalten, allerdings in einer Version ohne den
Suffix '_new'.

# Mehr Änderungen?
Wir haben versucht, den Code noch weiter abzuändern, z.B. 2*Pi^2 als Konstante
zu definieren oder /4 in *0.25 umzuwandeln, allerdings haben diese Änderungen
keinen offensichtlichen Unterschied bei dem höchsten Optimierungslevel gemacht.
Die Änderungen sind als Patch in `pde/patches` enthalten.

# Noch mehr Benchmarks?
Mit `benchmark.sh` wird eine große Menge Kombination von Compiler-Flags
ausprobiert. Hier die Ergebnisse für die erste Variante:

| Command | Mean [s] | Min [s] | Max [s] | Relative |
|:---|---:|---:|---:|---:|
| `-O0` | 39.767 ± 0.052 | 39.728 | 39.910 | 42.97 ± 0.36 |
| `-O1` | 7.801 ± 0.017 | 7.779 | 7.831 | 8.43 ± 0.07 |
| `-O2` | 2.826 ± 0.027 | 2.791 | 2.857 | 3.05 ± 0.04 |
| `-O3` | 2.480 ± 0.014 | 2.459 | 2.495 | 2.68 ± 0.03 |
| `-Og` | 8.860 ± 0.006 | 8.850 | 8.869 | 9.57 ± 0.08 |
| `-Os` | 7.866 ± 0.015 | 7.843 | 7.882 | 8.50 ± 0.07 |
| `-O2 -march=native` | 2.839 ± 0.017 | 2.801 | 2.854 | 3.07 ± 0.03 |
| `-O3 -march=native` | 2.504 ± 0.010 | 2.477 | 2.511 | 2.71 ± 0.02 |
| `-Ofast -march=native` | 0.929 ± 0.005 | 0.916 | 0.934 | 1.00 ± 0.01 |
| `-Os -march=native` | 7.623 ± 0.012 | 7.608 | 7.649 | 8.24 ± 0.07 |
| `-O2 -march=native -flto` | 2.833 ± 0.021 | 2.798 | 2.851 | 3.06 ± 0.03 |
| `-O3 -march=native -flto` | 2.499 ± 0.007 | 2.486 | 2.506 | 2.70 ± 0.02 |
| `-Ofast -march=native -flto` | 0.925 ± 0.008 | 0.906 | 0.932 | 1.00 |
| `-Os -march=native -flto` | 7.629 ± 0.014 | 7.603 | 7.646 | 8.24 ± 0.07 |
| `-O0 + strip` | 39.746 ± 0.009 | 39.733 | 39.764 | 42.95 ± 0.35 |
| `-O1 + strip` | 7.802 ± 0.018 | 7.775 | 7.822 | 8.43 ± 0.07 |
| `-O2 + strip` | 2.834 ± 0.021 | 2.791 | 2.851 | 3.06 ± 0.03 |
| `-O3 + strip` | 2.471 ± 0.015 | 2.448 | 2.486 | 2.67 ± 0.03 |
| `-Og + strip` | 8.858 ± 0.009 | 8.848 | 8.874 | 9.57 ± 0.08 |
| `-Os + strip` | 7.861 ± 0.012 | 7.844 | 7.879 | 8.49 ± 0.07 |
| `-O2 -march=native + strip` | 2.826 ± 0.019 | 2.797 | 2.848 | 3.05 ± 0.03 |
| `-O3 -march=native + strip` | 2.497 ± 0.015 | 2.461 | 2.507 | 2.70 ± 0.03 |
| `-Ofast -march=native + strip` | 0.929 ± 0.003 | 0.925 | 0.935 | 1.00 ± 0.01 |
| `-Os -march=native + strip` | 7.624 ± 0.012 | 7.604 | 7.641 | 8.24 ± 0.07 |
| `-O2 -march=native -flto + strip` | 2.830 ± 0.020 | 2.787 | 2.851 | 3.06 ± 0.03 |
| `-O3 -march=native -flto + strip` | 2.502 ± 0.007 | 2.492 | 2.510 | 2.70 ± 0.02 |
| `-Ofast -march=native -flto + strip` | 0.926 ± 0.007 | 0.909 | 0.933 | 1.00 ± 0.01 |
| `-Os -march=native -flto + strip` | 7.637 ± 0.015 | 7.606 | 7.663 | 8.25 ± 0.07 |
| `-O2 -march=native -flto + PGO` | 2.608 ± 0.010 | 2.599 | 2.625 | 2.82 ± 0.03 |
| `-O3 -march=native -flto + PGO` | 2.613 ± 0.020 | 2.578 | 2.641 | 2.82 ± 0.03 |
| `-Ofast -march=native -flto + PGO` | 0.929 ± 0.010 | 0.903 | 0.938 | 1.00 ± 0.01 |
| `-Os -march=native -flto + PGO` | 7.629 ± 0.017 | 7.607 | 7.649 | 8.24 ± 0.07 |
| `-O2 -march=native -flto + PGO + strip` | 2.606 ± 0.014 | 2.578 | 2.623 | 2.82 ± 0.03 |
| `-O3 -march=native -flto + PGO + strip` | 2.617 ± 0.010 | 2.604 | 2.638 | 2.83 ± 0.03 |
| `-Ofast -march=native -flto + PGO + strip` | 0.928 ± 0.007 | 0.912 | 0.936 | 1.00 ± 0.01 |
| `-Os -march=native -flto + PGO + strip` | 7.633 ± 0.014 | 7.604 | 7.651 | 8.25 ± 0.07 |

Und die Ergebnisse für die zweite:
| Command | Mean [s] | Min [s] | Max [s] | Relative |
|:---|---:|---:|---:|---:|
| `-O0` | 48.927 ± 0.010 | 48.915 | 48.945 | 21.19 ± 0.23 |
| `-O1` | 24.359 ± 0.020 | 24.343 | 24.411 | 10.55 ± 0.11 |
| `-O2` | 24.385 ± 0.044 | 24.354 | 24.477 | 10.56 ± 0.11 |
| `-O3` | 12.587 ± 0.008 | 12.578 | 12.602 | 5.45 ± 0.06 |
| `-Og` | 26.513 ± 0.009 | 26.504 | 26.533 | 11.48 ± 0.12 |
| `-Os` | 28.112 ± 0.010 | 28.092 | 28.125 | 12.18 ± 0.13 |
| `-O2 -march=native` | 24.277 ± 0.014 | 24.270 | 24.316 | 10.52 ± 0.11 |
| `-O3 -march=native` | 12.688 ± 0.044 | 12.668 | 12.812 | 5.50 ± 0.06 |
| `-Ofast -march=native` | 2.381 ± 0.119 | 2.326 | 2.713 | 1.03 ± 0.05 |
| `-Os -march=native` | 28.204 ± 0.190 | 28.111 | 28.740 | 12.22 ± 0.15 |
| `-O2 -march=native -flto` | 24.280 ± 0.019 | 24.265 | 24.316 | 10.52 ± 0.11 |
| `-O3 -march=native -flto` | 12.694 ± 0.079 | 12.659 | 12.916 | 5.50 ± 0.07 |
| `-Ofast -march=native -flto` | 2.334 ± 0.026 | 2.292 | 2.399 | 1.01 ± 0.02 |
| `-Os -march=native -flto` | 28.205 ± 0.214 | 28.054 | 28.806 | 12.22 ± 0.16 |
| `-O0 + strip` | 48.923 ± 0.006 | 48.910 | 48.930 | 21.19 ± 0.23 |
| `-O1 + strip` | 24.372 ± 0.063 | 24.333 | 24.543 | 10.56 ± 0.12 |
| `-O2 + strip` | 24.384 ± 0.037 | 24.353 | 24.459 | 10.56 ± 0.11 |
| `-O3 + strip` | 12.628 ± 0.063 | 12.572 | 12.734 | 5.47 ± 0.06 |
| `-Og + strip` | 26.556 ± 0.125 | 26.494 | 26.871 | 11.50 ± 0.13 |
| `-Os + strip` | 28.155 ± 0.063 | 28.081 | 28.303 | 12.19 ± 0.13 |
| `-O2 -march=native + strip` | 24.276 ± 0.014 | 24.263 | 24.310 | 10.51 ± 0.11 |
| `-O3 -march=native + strip` | 12.667 ± 0.009 | 12.658 | 12.682 | 5.49 ± 0.06 |
| `-Ofast -march=native + strip` | 2.373 ± 0.109 | 2.325 | 2.679 | 1.03 ± 0.05 |
| `-Os -march=native + strip` | 28.261 ± 0.241 | 28.119 | 28.716 | 12.24 ± 0.17 |
| `-O2 -march=native -flto + strip` | 24.270 ± 0.014 | 24.248 | 24.304 | 10.51 ± 0.11 |
| `-O3 -march=native -flto + strip` | 12.675 ± 0.017 | 12.660 | 12.717 | 5.49 ± 0.06 |
| `-Ofast -march=native -flto + strip` | 2.343 ± 0.021 | 2.329 | 2.389 | 1.01 ± 0.01 |
| `-Os -march=native -flto + strip` | 28.264 ± 0.154 | 28.120 | 28.513 | 12.24 ± 0.15 |
| `-O2 -march=native -flto + PGO` | 12.834 ± 0.014 | 12.825 | 12.870 | 5.56 ± 0.06 |
| `-O3 -march=native -flto + PGO` | 12.720 ± 0.031 | 12.702 | 12.806 | 5.51 ± 0.06 |
| `-Ofast -march=native -flto + PGO` | 2.316 ± 0.016 | 2.298 | 2.343 | 1.00 ± 0.01 |
| `-Os -march=native -flto + PGO` | 25.414 ± 0.258 | 25.280 | 26.101 | 11.01 ± 0.16 |
| `-O2 -march=native -flto + PGO + strip` | 12.872 ± 0.143 | 12.823 | 13.278 | 5.58 ± 0.09 |
| `-O3 -march=native -flto + PGO + strip` | 12.720 ± 0.037 | 12.696 | 12.818 | 5.51 ± 0.06 |
| `-Ofast -march=native -flto + PGO + strip` | 2.309 ± 0.025 | 2.295 | 2.377 | 1.00 |
| `-Os -march=native -flto + PGO + strip` | 25.319 ± 0.035 | 25.286 | 25.415 | 10.97 ± 0.12 |

Das waren viele Benchmarks.
