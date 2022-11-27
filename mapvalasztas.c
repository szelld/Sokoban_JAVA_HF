//
// Created by David on 2022. 11. 22..
//

#include "mapvalasztas.h"
//#include "debugmalloc.h"


void filePathValasztas(char *filePath, char *savePath) {
    char fileName[4];
//    strcpy(filePath, "C:\\Users\\David\\CLionProjects\\1nagyzh\\cmake-build-debug\\sokevo\\");
//    strcpy(scoreboardPath, "sokevo\\");
    printf("Adja meg a palya nevet!\n");
    scanf("%s", fileName);
    //realloc(filePath,strlen(fileName)+5* sizeof (char));
    //realloc(scoreboardPath,strlen(fileName)+5* sizeof (char));
    strcpy(filePath, fileName);
    strcpy(savePath, fileName);
    strcat(filePath, ".txt\0");
    strcat(savePath, "_save.txt\0");
}

void scoreboardPathValasztas(char *scoreboardPath) {
    char fileName[4];
//    strcpy(filePath, "C:\\Users\\David\\CLionProjects\\1nagyzh\\cmake-build-debug\\sokevo\\");
//    strcpy(scoreboardPath, "sokevo\\");
    printf("Adja meg a scoreboardhoz tartozo palya nevet!\n");
    scanf("%s", fileName);
    //realloc(filePath,strlen(fileName)+5* sizeof (char));
    //realloc(scoreboardPath,strlen(fileName)+5* sizeof (char));
    strcpy(scoreboardPath, fileName);
    strcat(scoreboardPath, "_sb.txt\0");
}

bool nyerhetE (int **map, int sor, int oszlop) {

    if (map[sor][oszlop] == 'X') {
        if (map[sor][oszlop-1] == '#' || map[sor][oszlop-1] == 'X' || map[sor][oszlop-1] == '*') {
            if (map[sor-1][oszlop] == '#' || map[sor-1][oszlop] == 'X' || map[sor-1][oszlop] == '*') {
                return false;
            }
            if (map[sor+1][oszlop] == '#' || map[sor+1][oszlop] == 'X' || map[sor+1][oszlop] == '*') {
                return false;
            }
        }
        if (map[sor][oszlop+1] == '#' || map[sor][oszlop+1] == 'X' || map[sor][oszlop+1] == '*') {
            if (map[sor - 1][oszlop] == '#' || map[sor - 1][oszlop] == 'X' || map[sor - 1][oszlop] == '*') {
                return false;
            }
            if (map[sor + 1][oszlop] == '#' || map[sor + 1][oszlop] == 'X' || map[sor + 1][oszlop] == '*') {
                return false;
            }
        }
    }
    return true;
}