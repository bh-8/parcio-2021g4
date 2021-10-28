#include <stdio.h>

#define MAPSIZE 3
#define SPACES 3

// Definieren Sie ein enum cardd
enum cardd {
    W=1,
    E=2,
    N=4,
    S=8
};

// Definieren Sie ein 3x3-Array namens map, das Werte vom Typ cardd enthält
static enum cardd map[MAPSIZE][MAPSIZE];

// Die Funktion set_dir soll an Position x, y den Wert dir in das Array map eintragen
// Überprüfen Sie x und y um mögliche Arrayüberläufe zu verhindern
// Überprüfen Sie außerdem dir auf Gültigkeit
void set_dir (size_t x, size_t y, enum cardd dir)
{
    if (MAPSIZE <= x || MAPSIZE <= y)
        return;
    if ((1 <= dir && dir <= 2) ||
        (4 <= dir && dir <= 6) ||
        (8 <= dir && dir <= 10))
            map[x][y] = dir;
}

char* get_char(enum cardd dir)
{
    char* ret;
    switch((size_t) dir) {
        case N: ret = "N";
            break;
        case S: ret = "S";
            break;
        case W: ret = "W";
            break;
        case E: ret = "E";
            break;
        case N|W: ret = "NW";
              break;
        case N|E: ret = "NE";
              break;
        case S|W: ret = "SW";
              break;
        case S|E: ret = "SE";
              break;
        default: ret = "0";
    }
    return ret;
}

// Die Funktion show_map soll das Array in Form einer 3x3-Matrix ausgeben
void show_map (void)
{
    for (size_t i = 0; i < MAPSIZE; ++i) {
        for (size_t j = 0; j < MAPSIZE; ++j) {
            char* dir = get_char(map[i][j]);
            for (size_t cur = 0, count = 0; count <= SPACES; ++count) {
                if (0 != dir[cur])
                    putchar(dir[cur++]);
                else
                    putchar(' ');
            }
        }
        printf("\n");
    }
}

int main (void)
{
    // In dieser Funktion darf nichts verändert werden!
    set_dir(0, 1, N);
    set_dir(1, 0, W);
    set_dir(1, 4, W);
    set_dir(1, 2, E);
    set_dir(2, 1, S);

    show_map();

    set_dir(0, 0, N|W);
    set_dir(0, 2, N|E);
    set_dir(0, 2, N|S);
    set_dir(2, 0, S|W);
    set_dir(2, 2, S|E);
    set_dir(2, 2, E|W);
    set_dir(1, 3, N|S|E);
    set_dir(1, 1, N|S|E|W);

    show_map();

    return 0;
}
