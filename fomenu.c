//
// Created by David on 2022. 11. 23..
//


#include "mainHeader.h"


int fomenu (void) {
    printf("Sokoban\nA jatek kezdesehez nyomjon 1-est!\nA scoreboard megjelenitesehez nyomja meg a 2-est!\nA kilepeshez nyomja meg a 3-ast!\n");
    int state;
    scanf("%d", &state);
    while (state<0 || state >3) {
        printf("Rossz szam, adja meg ujra!\n");
        scanf("%d", &state);
    }
    return state;
}

int jatekvege(void) {
    printf("Ha a fomenube szeretne visszaterni, nyomjon 1-est\nHa ki szeretne lepni, nyomjon 2-ast!\n");
    int state;
    scanf("%d", &state);
    while (state<0 || state >2) {
        printf("Rossz szam, adja meg ujra!\n");
        scanf("%d", &state);
    }
    return state;
}