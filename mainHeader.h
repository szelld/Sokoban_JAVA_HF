//
// Created by David on 2022. 11. 23..
//

#ifndef MAIN_C_MAINHEADER_H
#define MAIN_C_MAINHEADER_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mainHeader.h"


typedef struct karakter {
    int x; ///x. sor
    int y; ///y. oszlop
}karakter;


///mapControl.c
karakter leptet(int ***map, int const **originalMap, char beIrany, karakter  player, int *lepsSzam);

#endif //MAIN_C_MAINHEADER_H
