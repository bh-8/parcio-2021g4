# Leistungsanalyse
### Messung 1: Vergleich der Laufzeiten (4096 Interlines)
- Datenaufteilungen: zeilen-, spalten- und elementweise Aufteilung
- Static Scheduling, da so am schnellsten
    ![Vergleich der Datenaufteilungen](pdf_attachment/ROWvCOLUMNvELEMENT.svg)
    + Zeilenweise (blau) [top mit 6 Threads, ~0.8s]
      - bei einem Thread läuft das Programm ca. 3s
      - zwei Threads halbieren die Laufzeit (~1.5s), 4 Threads brauchen ca. 1s
      - ab 6 Threads ist keine nennenswerte Leistungsverbesserung zu erkennen (~0.8s)
    + Spaltenweise (orange) [top mit 8 Threads, ~1-1.2s]
      - bei einem Thread läuft das Programm ca. 6 Sekunden
      - zwei Threads halbieren die Laufzeit (~3s), 4 Threads benötigen ~2s
      - die Laufzeit ist mit ca. 8 Threads am geringsten (~1.2s)
      - mit weiter steigender Threadanzahl bis 24 Threads steigt die Laufzeit auf ~2s wieder an
    + Elementweise (gelb) [top mit 12 Threads, ~3s]
      - diese Datenaufteilung ist von den gemessenen mit Abstand die Langsamste: ein Thread benötigt bis zu 22s
      - zwei Threads halbieren die Laufzeit (~11s), 4 Treads laufen ~6s
      - die Laufzeit verbessert sich mit einer Anzahl von 12 Threads auf ~3s
      - mehr Threads verbessern die Laufzeit jedoch nicht
- Scheduling-Algorithmen: Zeilenweise
  ![Row Scheduling](pdf_attachment/ROW.svg)
- Scheduling-Algorithmen: Spaltenweise
  ![Column Scheduling](pdf_attachment/COLUMN.svg)
- Scheduling-Algorithmen: Elementweise
  ![Element Scheduling](pdf_attachment/ELEMENT.svg)
---
### Messung 2

---
