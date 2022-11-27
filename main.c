#include "mainHeader.h"
#include "scoreboard.h"
#include "fomenu.h"
#include "mapvalasztas.h"
#include "debugmalloc.h"



int main() {

    FILE*f;
    char filePath[18], scoreboardPath[18], saveFilePath[25];
    bool gameE = false;
    int state, lepes = 0;

FOMENU:
    state = fomenu();
    switch (state) {
        case 1:
            gameE = true;
            filePathValasztas(filePath, saveFilePath);
            f = fopen(filePath, "r");
            goto JATEK;
        case 2:
            gameE = true;
            filePathValasztas(filePath, saveFilePath);
            f = fopen(saveFilePath, "r");
            goto JATEK;
        case 3: {
            //char scoreboardNev[18];
            scoreboardPathValasztas(scoreboardPath);
            scoreboardKiir(scoreboardPath);
            goto FOMENU;
        }
        case 4:
            if (gameE) {
                goto QUITE_GAME;
            }
            else {
                goto QUITE_NOGAME;
            }
    }

    JATEK:
    printf("Adja meg a nevet:");
    char nev[50];
    scanf("%s", nev);
    scoreboardPathValasztas(scoreboardPath);
    //filePathValasztas(filePath, saveFilePath);


    struct karakter karakter;
    char sor[1000];
    int maxHossz=0, sorokDb=0, sorHossz[20]={0}, i, j;

    /// Ellenorzes, hogy jol nyitottuk-e meg
    if (f == NULL) {
        perror("Nem jo a map! ");
    }
    if (state == 2) {
        char *p;
        fgets(sor, 1000, f);
        p = strtok(sor, " ");
        lepes = atoi(p);
        p = strtok(NULL, " ");
        karakter.x = atoi(p);
        p = strtok(NULL, "\n");
        karakter.y = atoi(p);
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
    if (state == 1) {
        f = fopen(filePath, "r");
    }
    else {
        f = fopen(saveFilePath, "r");
        fgets(sor, 1000, f);
    }


    int ladaDb=0;
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
                case '0':
                    map[i][j] = '0';
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

    map[karakter.x][karakter.y] = 'I'; ///Ez a sor azért kell mert így kerül be a játékos karaktere ha mentést töltünk be, mert a _save.txt-ben az eredeti karakter van azon a helyen

    fclose(f);


    bool vegeE=true; /// Eza valtozo fogja megallitani a jatek magjat
    bool nyerhet = true;
    char beIrany;
    int  vegex, vegey;
    printf("A jatek betoltve. A kezdeshez nyomjon entert!\n");
    do {
        scanf("%c", &beIrany);
    }while (beIrany != '\n');


/// A jatek maja


    while (vegeE) {
        FILE*save = fopen(saveFilePath, "w");
        if (save == NULL) {
            perror("Nem jo a save! ");
        }
        fprintf(save, "%d %d %d\n", lepes, karakter.x, karakter.y);

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
                if (map[x][y] == 'I' || map[x][y] == '|') {
                    fprintf(save, "%c", originalMap[x][y]);
                }
                else {
                    fprintf(save, "%c", map[x][y]);
                }
                y++;
            }
            printf("\n");
            fprintf(save, "\n");
            x++;
        }
        if (!nyerhet) {
            fclose(save);
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
                case 'q':
                    vegeE = false;
                    goto QUITE_GAME;
                default:
                    printf("Nem jo billentyut nyomtal meg! A jatek a W A S D billentyukkel iranyithato!\n");
                    lepes--;
                    break;
            }
            lepes++;
        }
        fclose(save);
    }

    Jatekos *eleje = NULL;
    scoreboard(eleje, scoreboardPath, nev, lepes);

    state = jatekvege();
    switch (state) {
        case 1:
            goto FOMENU;
        case 2:
            goto QUITE_GAME;
    }

QUITE_GAME:

    for (i=0; i<sorokDb; i++) {
        free(map[i]);
    }
    free(map);
    for (i=0; i<sorokDb; i++) {
        free(originalMap[i]);
    }
    free(originalMap);

QUITE_NOGAME:

    return 0;
}
