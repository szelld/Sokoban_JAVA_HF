//
// Created by David on 2022. 11. 23..
//

#include <stdio.h>
#include "mainHeader.h"


int fomenu (void) {
    printf("Sokoban\nA jatek kezdesehez nyomjon 1-est!\nA scoreboard megjelenitesehez nyomja meg a 2-est!\n");
    int state;
    scanf("%d", &state);
    while (state<0 || state >2) {
        printf("Rossz szam, adja meg ujra!\n");
        scanf("%d", &state);
    }
    return state;
}