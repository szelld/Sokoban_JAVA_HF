//
// Created by David on 2022. 11. 07..
//

#ifndef MAIN_C_SCOREBOARD_H
#define MAIN_C_SCOREBOARD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Jatekos {
    char nev[100];
    int lepesszam;
    struct Jatekos *next;
}Jatekos;


Jatekos *lanclista_beszur_eleje (Jatekos *eleje, char *nev, int lepesszam);
void lanclista_beszur (Jatekos *iter, char *nev, int lepesszam);
void scoreboardFelszabadit (Jatekos *eleje);
void scoreboard (Jatekos *elso, char *scoreboardNev, char *nev, int lepesszam);
void scoreboardKiir (char *fileName);



#endif //MAIN_C_SCOREBOARD_H
