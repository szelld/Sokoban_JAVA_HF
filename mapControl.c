//
// Created by david on 2022. 11. 25..
//


#include "mainHeader.h"

karakter leptet(int ***map, int const **originalMap, char beIrany, karakter  player, int *lepesSzam) {
                switch (beIrany) {
                case 'w':
                    if (*map[player.x - 1][player.y] == 'X') {
                        if (*map[player.x - 2][player.y] == '#' || *map[player.x - 2][player.y] == 'X' || *map[player.x - 2][player.y] == '*') {
                            printf("Nem tudsz erre lepni!\n");
                        } else {
                            if (*map[player.x - 2][player.y] == '0') {
                                *map[player.x][player.y] = originalMap[player.x][player.y];
                                *map[player.x - 2][player.y] = '*';
                                *map[player.x - 1][player.y] = 'I';          ///Meg kell keresni miért ír ki plusz 0-kat
                                player.x -= 1;
                            } else {
                                *map[player.x][player.y] = originalMap[player.x][player.y];
                                *map[player.x - 2][player.y] = 'X';
                                *map[player.x - 1][player.y] = 'I';
                                player.x -= 1;
                            }
                        }
                    } else if (*map[player.x - 1][player.y] == ' ') {
                        *map[player.x][player.y] = originalMap[player.x][player.y];
                        *map[player.x - 1][player.y] = 'I';
                        player.x -= 1;
                    } else if (*map[player.x - 1][player.y] == '0') {
                        *map[player.x][player.y] = originalMap[player.x][player.y];
                        *map[player.x - 1][player.y] = 'I';
                        player.x -= 1;
                    } else if (*map[player.x - 1][player.y] == '*') {
                        if (*map[player.x - 2][player.y] == '#' || *map[player.x][player.y - 2] == 'X') {
                            printf("Nem tudsz erre lepni!\n");
                        } else {
                            *map[player.x][player.y] = originalMap[player.x][player.y];
                            *map[player.x - 1][player.y] = 'I';
                            *map[player.x - 2][player.y] = 'X';
                            player.x -= 1;
                        }
                    } else {
                        printf("Nem tudsz erre lepni!\n");
                    }
                    break;
                case 's':
                    if (*map[player.x + 1][player.y] == 'X') {
                        if (*map[player.x + 2][player.y] == '#' || *map[player.x + 2][player.y] == 'X' || *map[player.x + 2][player.y] == '*') {
                            printf("Nem tudsz erre lepni!\n");
                        } else {
                            if (*map[player.x + 2][player.y] == '0') {
                                *map[player.x][player.y] =  originalMap[player.x][player.y];
                                *map[player.x + 2][player.y] = '*';
                                *map[player.x + 1][player.y] = 'I';
                                player.x += 1;
                            } else {
                                *map[player.x][player.y] = originalMap[player.x][player.y];
                                *map[player.x + 2][player.y] = 'X';
                                *map[player.x + 1][player.y] = 'I';
                                player.x += 1;
                            }
                        }
                    } else if (*map[player.x + 1][player.y] == ' ') {
                        *map[player.x][player.y] = originalMap[player.x][player.y];
                        *map[player.x + 1][player.y] = 'I';
                        player.x += 1;
                    } else if (*map[player.x + 1][player.y] == '0') {
                        *map[player.x][player.y] = originalMap[player.x][player.y];
                        *map[player.x + 1][player.y] = 'I';
                        player.x += 1;
                    } else if (*map[player.x + 1][player.y] == '*') {
                        if (*map[player.x + 2][player.y] == '#' || *map[player.x][player.y - 2] == 'X') {
                            printf("Nem tudsz erre lepni!\n");
                        } else {
                            *map[player.x][player.y] = originalMap[player.x][player.y];
                            *map[player.x + 1][player.y] = 'I';
                            *map[player.x + 2][player.y] = 'X';
                            player.x += 1;
                        }
                    } else {
                        printf("Nem tudsz erre lepni!\n");
                    }
                    break;
                case 'a':
                    if (*map[player.x][player.y - 1] == 'X') {
                        if (*map[player.x][player.y - 2] == '#' || *map[player.x][player.y - 2] == 'X' || *map[player.x][player.y - 2] == '*') {
                            printf("Nem tudsz erre lepni!\n");
                        } else {
                            if (*map[player.x][player.y - 2] == '0') {
                                *map[player.x][player.y] = originalMap[player.x][player.y];
                                *map[player.x][player.y - 2] = '*';
                                *map[player.x][player.y - 1] = '|';
                                player.y -= 1;
                            } else {
                                *map[player.x][player.y] = originalMap[player.x][player.y];
                                *map[player.x][player.y - 2] = 'X';
                                *map[player.x][player.y - 1] = '|';
                                player.y -= 1;
                            }
                        }
                    } else if (*map[player.x][player.y - 1] == ' ') {
                        *map[player.x][player.y] = originalMap[player.x][player.y];
                        *map[player.x][player.y - 1] = '|';
                        player.y -= 1;
                    } else if (*map[player.x][player.y - 1] == '0') {
                        *map[player.x][player.y] = originalMap[player.x][player.y];
                        *map[player.x][player.y - 1] = '|';
                        player.y -= 1;
                    } else if (*map[player.x][player.y - 1] == '*') {
                        if (*map[player.x][player.y - 2] == '#' || *map[player.x][player.y - 2] == 'X') {
                            printf("Nem tudsz erre lepni!\n");
                        } else {
                            *map[player.x][player.y] = originalMap[player.x][player.y];
                            *map[player.x][player.y - 1] = '|';
                            *map[player.x][player.y - 2] = 'X';
                            player.y -= 1;
                        }
                    } else {
                        printf("Nem tudsz erre lepni!\n");
                    }
                    break;
                case 'd':
                    if (*map[player.x][player.y + 1] == 'X') {
                        if (*map[player.x][player.y + 2] == '#' || *map[player.x][player.y + 2] == 'X' || *map[player.x][player.y + 2] == '*') {
                            printf("Nem tudsz erre lepni!\n");
                        } else {
                            if (*map[player.x][player.y + 2] == '0') {
                                *map[player.x][player.y] = originalMap[player.x][player.y];
                                *map[player.x][player.y + 2] = '*';
                                *map[player.x][player.y + 1] = '|';
                                player.y += 1;
                            } else {
                                *map[player.x][player.y] = originalMap[player.x][player.y];
                                *map[player.x][player.y + 2] = 'X';
                                *map[player.x][player.y + 1] = '|';
                                player.y += 1;
                            }
                        }
                    } else if (*map[player.x][player.y + 1] == ' ') {
                        *map[player.x][player.y] = originalMap[player.x][player.y];
                        *map[player.x][player.y + 1] = '|';
                        player.y += 1;
                    } else if (*map[player.x][player.y + 1] == '0') {
                        *map[player.x][player.y] = originalMap[player.x][player.y];
                        *map[player.x][player.y + 1] = '|';
                        player.y += 1;
                    } else if (*map[player.x][player.y + 1] == '*') {
                        if (*map[player.x][player.y + 2] == '#' || *map[player.x][player.y + 2] == 'X') {
                            printf("Nem tudsz erre lepni!\n");
                        } else {
                            *map[player.x][player.y] = originalMap[player.x][player.y];
                            *map[player.x][player.y + 1] = '|';
                            *map[player.x][player.y + 2] = 'X';
                            player.y += 1;
                        }
                    } else {
                        printf("Nem tudsz erre lepni!\n");
                    }
                    break;
                default:
                    printf("Nem jo billentyut nyomtal meg! A jatek a W A S D billentyukkel iranyithato!\n");
                    *lepesSzam--;
                    break;
            }
            return player;
}