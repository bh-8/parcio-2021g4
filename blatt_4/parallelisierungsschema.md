# Parallelisierungsschema
### Teilaufgabe 1: Beschreibung der Datenaufteilung der Matrix auf die einzelnen Tasks.
- Welche Daten der Matrix werden von welchem Task verwaltet?
    + die Threads (Tasks) arbeiten zeilenweise auf der Matrix

- Visualisieren Sie die Datenaufteilung mit geeigneten Grafiken.
    <br/><img src="pdf_attachment/aufteilung.png" alt="Datenaufteilung" width="288" height="193">

---
### Teilaufgabe 2: Parallelisierungsschema für das Jacobi-Verfahren.
- Beschreiben Sie aus Sicht eines Tasks, wann die Berechnung und wann die Kommunikation mit seinen Nachbarn erfolgt. Unterscheiden Sie nach gemeinsamem und verteiltem Speicher.
    + <TODO...>

- Welche Daten benötigt der Task von seinen Nachbarn und wann tauscht er die Daten aus?
    + <TODO...>

- Auf welche Variablen bzw. Daten muss welcher Task zugreifen?
    + <TODO...>

---
### Teilaufgabe 3: Parallelisierungsschema für das Gauß-Seidel-Verfahren.
- Beschreiben Sie aus Sicht eines Tasks, wann die Berechnung und wann die Kommunikation mit seinen Nachbarn erfolgt. Unterscheiden Sie nach gemeinsamem und verteiltem Speicher.
    + <TODO...>

- Welche Daten benötigt der Task von seinen Nachbarn und wann tauscht er die Daten aus?
    + <TODO...>

- Auf welche Variablen bzw. Daten muss welcher Task zugreifen?
    + <TODO...>

---
### Teilaufgabe 4: Diskussion der Abbruchproblematik
- Es sind vier Fälle zu betrachten: Abbruch nach Iterationszahl und Genauigkeit für jeweils Jacobi und Gauß-Seidel.
- Wann wird ein Task feststellen, dass das Abbruchkriterium erreicht wurde und er seine Arbeit beenden kann?
    + Abbruch nach Iterationszahl:
      + Die Iterationen werden auf die verschiedenen Threads gleichmäßig verteilt (Iterationen/Threadanzahl). Das Programm terminiert, sobald jeder Thread seine zugewiesene Anzahl Iterationen abgearbeitet hat.
    + Abbruch nach Genauigkeit:
      + Die Threads teilen sich die 'residuum'-Variable und terminieren, sobald dieser Restfehler unter einem bestimmten Threshold liegt.
- In welcher Iteration beendet sich ein Task im Vergleich zu seinen Nachbarn, wenn er das Abbruchkriterium erreicht?
    + Da die Nachbartasks des terminierenden Tasks von den berechneten Werten abhängen, müssen diese angrenzenden Tasks eine Iteration weiter rechnen, um mit den finalen Werden des terminierten Tasks arbeiten zu können.

---
