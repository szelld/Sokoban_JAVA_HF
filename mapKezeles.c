//
// Created by David on 2022. 11. 23..
//


#include <stdlib.h>
#include <stdbool.h>
#include "mainHeader.h"

bool nyerhetE (int **map, int sor, int oszlop) {

    if (map[sor][oszlop] == 'X') {
        if (map[sor][oszlop-1] == '#' || map[sor][oszlop-1] == 'X' || map[sor][oszlop-1] == '*') {
            if (map[sor-1][oszlop] == '#' || map[sor-1][oszlop] == 'X' || map[sor-1][oszlop] == '*') {
                return false;
            }
            if (map[sor+1][oszlop] == '#' || map[sor+1][oszlop] == 'X' || map[sor+1][oszlop] == '*') {
                return false;
            }
        }
        if (map[sor][oszlop+1] == '#' || map[sor][oszlop+1] == 'X' || map[sor][oszlop+1] == '*') {
            if (map[sor - 1][oszlop] == '#' || map[sor - 1][oszlop] == 'X' || map[sor - 1][oszlop] == '*') {
                return false;
            }
            if (map[sor + 1][oszlop] == '#' || map[sor + 1][oszlop] == 'X' || map[sor + 1][oszlop] == '*') {
                return false;
            }
        }
    }
    return true;
}

//main.c scoreboard.c fomenu.c mapvalasztas.c mapKezeles.c