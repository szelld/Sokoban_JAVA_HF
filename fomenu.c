//
// Created by David on 2022. 11. 23..
//


#include "fomenu.h"
//#include "debugmalloc.h"



int fomenu (void) {
    printf("Sokoban\nUj jatek kezdesehez nyomjon 1-est!\nMentes beotltesehez, nyomjon 2-est\nA scoreboard megjelenitesehez nyomja meg a 3-est!\nA kilepeshez nyomja meg a 4-ast!\n");
    int state;
    scanf("%d", &state);
    while (state<0 || state >4) {
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