//
// Created by david on 2022. 11. 27..
//

#ifndef MAIN_C_MAPVALASZTAS_H
#define MAIN_C_MAPVALASZTAS_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>


void filePathValasztas(char *filePath, char *savePath);
void scoreboardPathValasztas(char *scoreboardPath);
bool nyerhetE (int **map, int sor, int oszlop);

#endif //MAIN_C_MAPVALASZTAS_H
