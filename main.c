#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "mainHeader.h"
#include "debugmalloc.h"


typedef struct karakter {
    int x; ///x. sor
    int y; ///y. oszlop
}karakter;


int main() {

    int state = fomenu();
    char *filePath, *scoreboardPath[18];
    Jatekos *eleje = NULL;
    switch (state) {
        case 1:
            goto JATEK;
            break;
        case 2: {
            char scoreboardNev[18];
            nevValasztas(filePath, scoreboardNev);
            scoreboardKiir(scoreboardNev);
        }
            break;
    }

    JATEK:
    printf("Adja meg a nevet:");
    char nev[50];
    scanf("%s", nev);
    nevValasztas(filePath, scoreboardPath);

    FILE*f = fopen(filePath, "r");
    char sor[1000];
    int maxHossz=0, sorokDb=0, sorHossz[20]={0}, i, j;

    /// Ellenorzes, hogy jol nyitottuk-e meg
    if (f == NULL) {
        perror("Nem jo a map ");
    }

    /// Meghatarozzuk hogy mekkor tomb kell majd a palyahoz
    while (fgets(sor, 1000, f) != 0) {
        if (strlen(sor) > maxHossz)
            maxHossz= strlen(sor);
        sorHossz[sorokDb] = strlen(sor);
        sorokDb++;
        //printf("%s", sor);
    }
    fclose(f);

/// A pálya letrehozasa es elso kiiratasa:
    f = fopen(filePath, "r");
    struct karakter karakter;
    int ladaDb=0;  /// A temp azert kell hogy el tudja menteni hogy a lepes elott milyen ertek volt a karakter vagy a lada helyen, karakter a 0. index, a lada az 1-es,
    int **map;
    map = (int**) malloc(sorokDb*sizeof(int*));
    for (i = 0; i<sorokDb; i++) {
        map[i] = (int*) malloc(maxHossz * sizeof(int));
    }
/// Ebben a tömb azért kell hogy tujdam majd hogy melyik x y koordinátán milyen karakter volt eredetileg
    int **originalMap;
    originalMap = (int**) malloc(sorokDb*sizeof(int*));
    for (i = 0; i<sorokDb; i++) {
        originalMap[i] = (int*) malloc(maxHossz * sizeof(int));
    }

    i=0;

    do {
        j=0;
        while (j != sorHossz[i]) {
            map[i][j] = fgetc(f);
            switch (map[i][j]) {
                case '@':
                    map[i][j] = 'I'; /// Itt az karakterunk, eltaroljuk a helyet
                    originalMap[i][j] = ' ';
                    karakter.x = i;
                    karakter.y = j;
                    break;
                case '.':
                    map[i][j] = '0'; /// Ez a cel
                    originalMap[i][j] = '0';
                    ladaDb++;
                    break;
                case '$':
                    map[i][j] = 'X'; /// Ez a lada
                    originalMap[i][j] = ' ';
                    break;
                case '*':
                    map[i][j] = '*';
                    originalMap[i][j] = '0';
                    ladaDb++;
                    break;
                default:
                    originalMap[i][j] = ' ';
                    break;
            }
            //printf("%c",map[i][j]);
            j++;
        }
        i++;
    }while (i != sorokDb);
    fclose(f);


    bool vegeE=true; /// Eza valtozo fogja megallitani a jatek magjat
    bool nyerhet = true;
    char beIrany;
    int lepes = 0, vegex, vegey;
    printf("A jatek betoltve. A kezdeshez nyomjon entert!\n");
    do {
        scanf("%c", &beIrany);
    }while (beIrany != '\n');


/// A jatek maja


    while (vegeE) {

        int x = 0, nyertDb = 0, y;

        while (x < sorokDb) {
            y = 0;
            while (y < maxHossz-1) {
                if (map[x][y] == '*') {
                    nyertDb++;
                }
                printf("%c", map[x][y]);
                if (!nyerhetE(map, x, y)){
                    nyerhet = false;
                    vegex = x;
                    vegey = y;
                }
                y++;
            }
            printf("\n");
            x++;
        }
        if (!nyerhet) {
            printf("Rossz lepes! Vesztettel! %d %d \n", vegex, vegey);
            break;
        }
        //printf("%d %d\n",nyertDb, ladaDb);
        if (nyertDb == ladaDb) {
            printf("Paja sikeresen teljesitve!\n");
            vegeE = false;
        } else {

            printf("Adja meg az iranyt:");
            scanf(" %c", &beIrany);
            //printf("%c\n", beIrany);

            switch (beIrany) {
                case 'w':
                    if (map[karakter.x - 1][karakter.y] == 'X') {
                        if (map[karakter.x - 2][karakter.y] == '#' || map[karakter.x - 2][karakter.y] == 'X' || map[karakter.x - 2][karakter.y] == '*') {
                            printf("Nem tudsz erre lepni!\n");
                        } else {
                            if (map[karakter.x - 2][karakter.y] == '0') {
                                map[karakter.x][karakter.y] = originalMap[karakter.x][karakter.y];
                                map[karakter.x - 2][karakter.y] = '*';
                                map[karakter.x - 1][karakter.y] = 'I';          ///Meg kell keresni miért ír ki plusz 0-kat
                                karakter.x -= 1;
                            } else {
                                map[karakter.x][karakter.y] = originalMap[karakter.x][karakter.y];
                                map[karakter.x - 2][karakter.y] = 'X';
                                map[karakter.x - 1][karakter.y] = 'I';
                                karakter.x -= 1;
                            }
                        }
                    } else if (map[karakter.x - 1][karakter.y] == ' ') {
                        map[karakter.x][karakter.y] = originalMap[karakter.x][karakter.y];
                        map[karakter.x - 1][karakter.y] = 'I';
                        karakter.x -= 1;
                    } else if (map[karakter.x - 1][karakter.y] == '0') {
                        map[karakter.x][karakter.y] = originalMap[karakter.x][karakter.y];
                        map[karakter.x - 1][karakter.y] = 'I';
                        karakter.x -= 1;
                    } else if (map[karakter.x - 1][karakter.y] == '*') {
                        if (map[karakter.x - 2][karakter.y] == '#' || map[karakter.x][karakter.y - 2] == 'X') {
                            printf("Nem tudsz erre lepni!\n");
                        } else {
                            map[karakter.x][karakter.y] = originalMap[karakter.x][karakter.y];
                            map[karakter.x - 1][karakter.y] = 'I';
                            map[karakter.x - 2][karakter.y] = 'X';
                            karakter.x -= 1;
                        }
                    } else {
                        printf("Nem tudsz erre lepni!\n");
                    }
                    break;
                case 's':
                    if (map[karakter.x + 1][karakter.y] == 'X') {
                        if (map[karakter.x + 2][karakter.y] == '#' || map[karakter.x + 2][karakter.y] == 'X' || map[karakter.x + 2][karakter.y] == '*') {
                            printf("Nem tudsz erre lepni!\n");
                        } else {
                            if (map[karakter.x + 2][karakter.y] == '0') {
                                map[karakter.x][karakter.y] =  originalMap[karakter.x][karakter.y];
                                map[karakter.x + 2][karakter.y] = '*';
                                map[karakter.x + 1][karakter.y] = 'I';
                                karakter.x += 1;
                            } else {
                                map[karakter.x][karakter.y] = originalMap[karakter.x][karakter.y];
                                map[karakter.x + 2][karakter.y] = 'X';
                                map[karakter.x + 1][karakter.y] = 'I';
                                karakter.x += 1;
                            }
                        }
                    } else if (map[karakter.x + 1][karakter.y] == ' ') {
                        map[karakter.x][karakter.y] = originalMap[karakter.x][karakter.y];
                        map[karakter.x + 1][karakter.y] = 'I';
                        karakter.x += 1;
                    } else if (map[karakter.x + 1][karakter.y] == '0') {
                        map[karakter.x][karakter.y] = originalMap[karakter.x][karakter.y];
                        map[karakter.x + 1][karakter.y] = 'I';
                        karakter.x += 1;
                    } else if (map[karakter.x + 1][karakter.y] == '*') {
                        if (map[karakter.x + 2][karakter.y] == '#' || map[karakter.x][karakter.y - 2] == 'X') {
                            printf("Nem tudsz erre lepni!\n");
                        } else {
                            map[karakter.x][karakter.y] = originalMap[karakter.x][karakter.y];
                            map[karakter.x + 1][karakter.y] = 'I';
                            map[karakter.x + 2][karakter.y] = 'X';
                            karakter.x += 1;
                        }
                    } else {
                        printf("Nem tudsz erre lepni!\n");
                    }
                    break;
                case 'a':
                    if (map[karakter.x][karakter.y - 1] == 'X') {
                        if (map[karakter.x][karakter.y - 2] == '#' || map[karakter.x][karakter.y - 2] == 'X' || map[karakter.x][karakter.y - 2] == '*') {
                            printf("Nem tudsz erre lepni!\n");
                        } else {
                            if (map[karakter.x][karakter.y - 2] == '0') {
                                map[karakter.x][karakter.y] = originalMap[karakter.x][karakter.y];
                                map[karakter.x][karakter.y - 2] = '*';
                                map[karakter.x][karakter.y - 1] = '|';
                                karakter.y -= 1;
                            } else {
                                map[karakter.x][karakter.y] = originalMap[karakter.x][karakter.y];
                                map[karakter.x][karakter.y - 2] = 'X';
                                map[karakter.x][karakter.y - 1] = '|';
                                karakter.y -= 1;
                            }
                        }
                    } else if (map[karakter.x][karakter.y - 1] == ' ') {
                        map[karakter.x][karakter.y] = originalMap[karakter.x][karakter.y];
                        map[karakter.x][karakter.y - 1] = '|';
                        karakter.y -= 1;
                    } else if (map[karakter.x][karakter.y - 1] == '0') {
                        map[karakter.x][karakter.y] = originalMap[karakter.x][karakter.y];
                        map[karakter.x][karakter.y - 1] = '|';
                        karakter.y -= 1;
                    } else if (map[karakter.x][karakter.y - 1] == '*') {
                        if (map[karakter.x][karakter.y - 2] == '#' || map[karakter.x][karakter.y - 2] == 'X') {
                            printf("Nem tudsz erre lepni!\n");
                        } else {
                            map[karakter.x][karakter.y] = originalMap[karakter.x][karakter.y];
                            map[karakter.x][karakter.y - 1] = '|';
                            map[karakter.x][karakter.y - 2] = 'X';
                            karakter.y -= 1;
                        }
                    } else {
                        printf("Nem tudsz erre lepni!\n");
                    }
                    break;
                case 'd':
                    if (map[karakter.x][karakter.y + 1] == 'X') {
                        if (map[karakter.x][karakter.y + 2] == '#' || map[karakter.x][karakter.y + 2] == 'X' || map[karakter.x][karakter.y + 2] == '*') {
                            printf("Nem tudsz erre lepni!\n");
                        } else {
                            if (map[karakter.x][karakter.y + 2] == '0') {
                                map[karakter.x][karakter.y] = originalMap[karakter.x][karakter.y];
                                map[karakter.x][karakter.y + 2] = '*';
                                map[karakter.x][karakter.y + 1] = '|';
                                karakter.y += 1;
                            } else {
                                map[karakter.x][karakter.y] = originalMap[karakter.x][karakter.y];
                                map[karakter.x][karakter.y + 2] = 'X';
                                map[karakter.x][karakter.y + 1] = '|';
                                karakter.y += 1;
                            }
                        }
                    } else if (map[karakter.x][karakter.y + 1] == ' ') {
                        map[karakter.x][karakter.y] = originalMap[karakter.x][karakter.y];
                        map[karakter.x][karakter.y + 1] = '|';
                        karakter.y += 1;
                    } else if (map[karakter.x][karakter.y + 1] == '0') {
                        map[karakter.x][karakter.y] = originalMap[karakter.x][karakter.y];
                        map[karakter.x][karakter.y + 1] = '|';
                        karakter.y += 1;
                    } else if (map[karakter.x][karakter.y + 1] == '*') {
                        if (map[karakter.x][karakter.y + 2] == '#' || map[karakter.x][karakter.y + 2] == 'X') {
                            printf("Nem tudsz erre lepni!\n");
                        } else {
                            map[karakter.x][karakter.y] = originalMap[karakter.x][karakter.y];
                            map[karakter.x][karakter.y + 1] = '|';
                            map[karakter.x][karakter.y + 2] = 'X';
                            karakter.y += 1;
                        }
                    } else {
                        printf("Nem tudsz erre lepni!\n");
                    }
                    break;
                default:
                    break;
            }
        }
        lepes++;
    }

    scoreboard(eleje, scoreboardPath, nev, lepes);


    for (i=0; i<sorokDb; i++) {
        free(map[i]);
    }
    free(map);
    for (i=0; i<sorokDb; i++) {
        free(originalMap[i]);
    }
    free(originalMap);
    scoreboardFelszabadit(eleje);
    return 0;
}