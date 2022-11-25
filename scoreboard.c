//
// Created by David on 2022. 11. 23..
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mainHeader.h"


typedef struct Jatekos {
    char nev[100];
    int lepesszam;
    struct Jatekos *next;
}Jatekos;

Jatekos *lanclista_beszur_eleje (Jatekos *eleje, char *nev, int lepesszam) {
    Jatekos *uj = (Jatekos *) malloc(sizeof(Jatekos));
    strcpy(uj->nev, nev);
    uj->lepesszam = lepesszam;
    uj->next = eleje;
    eleje = uj;
    return eleje;
}


void lanclista_beszur (Jatekos *iter, char *nev, int lepesszam) {
    Jatekos *uj = (Jatekos *) malloc(sizeof(Jatekos));
    strcpy(uj->nev, nev);
    uj->lepesszam = lepesszam;
    uj->next = iter->next;
    iter->next = uj;
}


void scoreboardFelszabadit (Jatekos *eleje) {
    Jatekos *iter, *seged;
    for (iter = eleje; iter->next != NULL; iter = iter->next) {
        seged = iter->next;
        free(iter);
        iter = seged;
    }
    free (iter);
}

void scoreboard (Jatekos *elso, char *scoreboardNev, char *nev, int lepesszam) {
    FILE *filein = fopen(scoreboardNev, "r");
    if (filein == NULL) {
        fclose(filein);
        perror("Nem sikerult megnyitni a scoreboardot!  \n");
    }
    char *p;
    char sor[1000];

    Jatekos *iter, *uj;
    elso = NULL;
    iter = NULL;

    while (!feof(filein)) {
        fgets(sor, 1000, filein);
        uj = (Jatekos*) malloc(sizeof (Jatekos));
        p = strtok(sor,":");
        strcpy(uj->nev, p);
        p = strtok(NULL,"\n");
        uj->lepesszam = atoi(p);
        uj->next = NULL;

        if (elso == NULL) {
            elso = uj;
            iter = uj;
        }
        else {
            iter->next = uj;
            iter = uj;
        }
    }
    fclose(filein);

    iter = elso;
    Jatekos *seged=elso;
    while (iter->next != NULL && iter->lepesszam < lepesszam) {
        seged = iter;
        iter = iter->next;
    }

    if (iter == elso) {
        elso = lanclista_beszur_eleje(elso, nev, lepesszam);
    }
    else {
        lanclista_beszur(seged, nev, lepesszam);
    }

    filein = fopen(scoreboardNev, "w");

    for (iter = elso; iter->next != NULL; iter = iter->next) {
        fprintf(filein,"%s:%d\n", iter->nev,iter->lepesszam);
    }
    fprintf(filein,"%s:%d\n", iter->nev,iter->lepesszam);
    scoreboardFelszabadit(elso);
    fclose(filein);
}

void scoreboardKiir (char *fileName) {
    FILE *fileIn = fopen(fileName, "r");
    char sor[60];
    while (!feof(fileIn)) {
        fgets(sor,60,fileIn);
        printf("%s", sor);
    }
    printf("\n");
    fclose(fileIn);
}

