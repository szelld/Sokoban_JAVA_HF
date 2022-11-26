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

typedef struct Jatekos {
    char nev[100];
    int lepesszam;
    struct Jatekos *next;
}Jatekos;


///fomenu.c
int fomenu (void);
int jatekvege(void);


///scoreboard.c
Jatekos *lanclista_beszur_eleje (Jatekos *eleje, char *nev, int lepesszam);
void lanclista_beszur (Jatekos *iter, char *nev, int lepesszam);
void scoreboardFelszabadit (Jatekos *eleje);
void scoreboard (Jatekos *elso, char *scoreboardNev, char *nev, int lepesszam);
void scoreboardKiir (char *fileName);


///mapvalasztas.c
void filePathValasztas(char *filePath);
void scoreboardPathValasztas(char *scoreboardPath);
bool nyerhetE (int **map, int sor, int oszlop);


///mapControl.c
karakter leptet(int ***map, int const **originalMap, char beIrany, karakter  player, int *lepsSzam);



#endif //MAIN_C_MAINHEADER_H
