//
// Created by David on 2022. 11. 22..
//

#include <stdio.h>
#include <string.h>
#include "mainHeader.h"

void nevValasztas(char*filePath, char*scoreboardPath) {
    char fileName[4];
//    strcpy(filePath, "C:\\Users\\David\\CLionProjects\\1nagyzh\\cmake-build-debug\\sokevo\\");
//    strcpy(scoreboardPath, "sokevo\\");
    printf("Adja meg melyik palyaval nevet!\n");
    scanf("%s", fileName);
    strcpy(filePath, fileName);
    strcpy(scoreboardPath, fileName);
    strcat(filePath, ".txt\0");
    strcat(scoreboardPath, "_sb.txt\0");
}