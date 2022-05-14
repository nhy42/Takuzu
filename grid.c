#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"
#include "builtinGrids.h"



SIZEDGRID genMask(int size) {
    time_t t;
    srand((unsigned) time(&t));
    SIZEDGRID mask = allocGrid(size);
    for (int i = 0; i < size*size/2; i++) {
        int x, y;
        x = rand() % size;
        y = rand() % size;
        if (mask.grid[x][y]) {
            i--;
        } else {
            mask.grid[x][y] = 1;
        }
    }
    return mask;
}

SIZEDGRID allocGrid(int size) {
    SIZEDGRID newGrid;
    newGrid.size = size;
    newGrid.grid = calloc(size, size * size * sizeof(int));
    for (int i = 0; i < size; i++) {
        newGrid.grid[i] = calloc(size, size * sizeof(int));
    }
    return newGrid;
}

void freeGrid(SIZEDGRID * grid) {
    for (int i = 0; i < grid->size; ++i) {
        free(grid->grid[i]);
    }
    free(grid->grid);
}

int** convertToTakuzu4(int tab4[4][4]) {
    int** pointerToReturn = malloc(4 * sizeof(int *));
    for (int i = 0; i < 4; i++) {
        pointerToReturn[i] = malloc(4 * sizeof(int));
        for (int j = 0; j < 4; j++) {
            pointerToReturn[i][j] = tab4[i][j];
        }
    }
    return pointerToReturn;
}

int** convertToTakuzu8(int tab8[8][8]) {
    int** pointerToReturn = malloc(8 * sizeof(int *));
    for (int i = 0; i < 8; i++) {
        pointerToReturn[i] = malloc(8 * sizeof(int));
        for (int j = 0; j < 8; j++) {
            pointerToReturn[i][j] = tab8[i][j];
        }
    }
    return pointerToReturn;
}

int** convertToTakuzu16(int tab8[16][16]) {
    int** pointerToReturn = malloc(16 * sizeof(int *));
    for (int i = 0; i < 16; i++) {
        pointerToReturn[i] = malloc(16 * sizeof(int));
        for (int j = 0; j < 16; j++) {
            pointerToReturn[i][j] = tab8[i][j];
        }
    }
    return pointerToReturn;
}

SIZEDGRID getGrid4() {
    SIZEDGRID grid;
    grid.grid = convertToTakuzu4(exampleGrid4);
    grid.size = 4;
    return grid;
}

SIZEDGRID getGrid8() {
    SIZEDGRID grid;
    grid.grid = convertToTakuzu8(exampleGrid8);
    grid.size = 8;
    return grid;
}

void fillWithInt(SIZEDGRID* gridToFill, int valueToFill) {
    // also named caressWithInt, jsp trop pourquoi
    for (int i = 0; i < gridToFill->size; ++i) {
        for (int j = 0; j < gridToFill->size; ++j) {
            gridToFill->grid[i][j] = valueToFill;
        }
    }
}

void addOneOnTwoUsingMaks(SIZEDGRID gridOne, SIZEDGRID * gridTwo, SIZEDGRID mask) {
    for (int i = 0; i < gridOne.size; ++i) {
        for (int j = 0; j < gridOne.size; ++j) {
            if (mask.grid[i][j]) {
                gridTwo->grid[i][j] = gridOne.grid[i][j];
            }
        }
    }
}

int checkZeroEqualOne(SIZEDGRID usergrid, int x, int y, int val) {
    // vérifie s'il est possible qu'il y ai autant de zero que de 1 par lignes et pas colonnes
    int zeroEqualOne = 1;
    int i = 0;
    int zero = 0, one = 0, currentVal;
    // lignes
    while (zeroEqualOne && i < usergrid.size) {
        zero = 0, one = 0;
        for (int j = 0; j < usergrid.size; j++) {
            currentVal = (x == i && y == j) ? val : usergrid.grid[i][j];
            if (currentVal == 0) {
                zero++;
            } else if (currentVal == 1) {
                one++;
            }
        }
        if (zero > usergrid.size / 2 || one > usergrid.size / 2) {
            zeroEqualOne = 0;
        }
        i++;
    }
    // colonnes
    i = 0;
    while (zeroEqualOne && i < usergrid.size) {
        zero = 0, one = 0;
        for (int j = 0; j < usergrid.size; j++) {
            currentVal = (x == j && y == i) ? val : usergrid.grid[j][i];
            if (currentVal == 0) {
                zero++;
            } else if (currentVal == 1) {
                one++;
            }
        }
        if (zero > usergrid.size / 2 || one > usergrid.size / 2) {
            zeroEqualOne = 0;
        }
        i++;
    }
    return zeroEqualOne;
}

int checkMax2Following(SIZEDGRID usergrid, int x, int y, int val) {
    int twoSameMax = 1;
    int last, alreadyGotOne, currentVal;
    // lignes
    for (int i = 0; i < usergrid.size; i++) {
        last = -2, alreadyGotOne = 0;
        for (int j = 0; j < usergrid.size; j++) {
            currentVal = (x == i && y == j) ? val : usergrid.grid[i][j];
            if (currentVal == -1) {
                last = -2, alreadyGotOne = 0;
            } else if (currentVal == last) {
                if (alreadyGotOne) {
                    twoSameMax = 0;
                } else {
                    alreadyGotOne = 1;
                }
            } else {
                last = currentVal, alreadyGotOne = 0;
            }
        }
    }
    // colonnes
    for (int i = 0; i < usergrid.size; i++) {
        last = -2, alreadyGotOne = 0;
        for (int j = 0; j < usergrid.size; j++) {
            currentVal = (x == j && y == i) ? val : usergrid.grid[j][i];
            if (currentVal == -1) {
                last = -2, alreadyGotOne = 0;
            } else if (currentVal == last) {
                if (alreadyGotOne) {
                    twoSameMax = 0;
                } else {
                    alreadyGotOne = 1;
                }
            } else {
                last = currentVal, alreadyGotOne = 0;
            }
        }
    }
    return twoSameMax;
}

int checkSimilarLinesOrColumns(SIZEDGRID usergrid, int x, int y, int val) {
    int notSameColOrLines = 1;
    int similar, currentVal, currentVal2;
    // lignes
    for (int i = 0; i < usergrid.size - 1; i++) {
        for (int j = i + 1; j < usergrid.size; j++) {
            similar = 1;
            for (int k = 0; k < usergrid.size; k++) {
                currentVal = (x == i && y == k) ? val : usergrid.grid[i][k];
                currentVal2 = (x == j && y == k) ? val : usergrid.grid[j][k];
                if (currentVal == -1 || currentVal2 == -1 || currentVal != currentVal2) {
                    similar = 0;
                }
            }
            if (similar) {
                notSameColOrLines = 0;
            }
        }
    }
    // colonnes
    for (int i = 0; i < usergrid.size; i++) {
        for (int j = i + 1; j < usergrid.size; j++) {
            similar = 1;
            for (int k = 0; k < usergrid.size; k++) {
                currentVal = (x == k && y == i) ? val : usergrid.grid[k][i];
                currentVal2 = (x == k && y == j) ? val : usergrid.grid[k][j];
                if (currentVal == -1 || currentVal2 == -1 || currentVal != currentVal2) {
                    similar = 0;
                }
            }
            if (similar) {
                // printf("ici %d %d", i, j);
                notSameColOrLines = 0;
            }
        }
    }
    return notSameColOrLines;
}

int isValid(SIZEDGRID usergrid, int x, int y, int val, int showErr) {
    int zeroEqualOne, twoSameMax, notSameColOrLines;
    // rule 1 : zeroEqualOne
    zeroEqualOne = checkZeroEqualOne(usergrid, x, y, val);
    // rule 2 : deux max a la suite
    twoSameMax = checkMax2Following(usergrid, x, y, val);
    // rule 3 : pas de colone ou de ligne pareilles
    notSameColOrLines = checkSimilarLinesOrColumns(usergrid, x, y, val);
    if (showErr) {
        if (!zeroEqualOne) {
            printf("Le nombre de zero par ligne/colonne doit etre egal au nombre de un\n");
        } else if (!twoSameMax) {
            printf("Maximum deux memes valeurs a la suite\n");
        } else if (!notSameColOrLines) {
            printf("Deux colonnes/lignes ne peuvent pas etre similaires\n");
        }
    }
    return zeroEqualOne && twoSameMax && notSameColOrLines;
}

int checkEnded(SIZEDGRID usergrid) {
    for (int i = 0; i < usergrid.size; ++i) {
        for (int j = 0; j < usergrid.size; ++j) {
            if (usergrid.grid[i][j] == -1) {
                return 0;
            }
        }
    }
    return 1;
}

int giveHint(SIZEDGRID usergrid, int * x, int * y, int * val) {
    // premiers indices, quand ya deux chiffres pareils à coté
    for (int i = 0; i < usergrid.size; ++i) {
        for (int j = 0; j < usergrid.size; ++j) {
            if (checkIfUnderIsTheSame(usergrid, i, j)) {
                if (placeHintUnder(usergrid, i, j, x, y, val)) {
                    //printf("a%d, %d\n", *x, *y);
                    return 1;
                }
            }
            if (checkIfRightIsTheSame(usergrid, i, j)) {
                if (placeHintRight(usergrid, i, j, x, y, val)) {
                    //printf("b%d, %d\n", *x, *y);
                    return 1;
                }
            }
        }
    }

    // second indice, le chiffre entre deux chiffres

    for (int i = 0; i < usergrid.size; ++i) {
        for (int j = 0; j < usergrid.size; ++j) {
            if (checkIfSpaceBetweenTwoSameUnder(usergrid, i, j)) {
                placeHintInSpace(i + 1, j, usergrid.grid[i][j], x, y, val);
                //printf("c%d, %d\n", *x, *y);
                return 1;
            }
            if (checkIfSpaceBetweenTwoSameRight(usergrid, i, j)) {
                placeHintInSpace(i, j + 1, usergrid.grid[i][j], x, y, val);
                //printf("d%d, %d\n", *x, *y);
                return 1;
            }
        }
    }
    /**/

    // indice 3 : les lignes avec deux trous, différentes
    for (int i = 0; i < usergrid.size; ++i) {
        if (checkIfColumnHave2Empty(usergrid, i)) {
            if (placeHintIfSameColumn(usergrid, i, x, y, val)) {
                return 1;
            }
        }
        if (checkIfLineHave2Empty(usergrid, i)) {
            if (placeHintIfSameLine(usergrid, i, x, y, val)) {
                return 1;
            }
        }
    }
    return 0;
}

int checkIfUnderIsTheSame(SIZEDGRID usergrid, int x, int y) {
    if (x + 1 < usergrid.size && usergrid.grid[x][y] != -1) {
        if (usergrid.grid[x][y] == usergrid.grid[x + 1][y]) {
            return 1;
        }
    }
    return 0;
}

int checkIfRightIsTheSame(SIZEDGRID usergrid, int x, int y) {
    if (y + 1 < usergrid.size && usergrid.grid[x][y] != -1) {
        if (usergrid.grid[x][y] == usergrid.grid[x][y+1]) {
            return 1;
        }
    }
    return 0;
}

int placeHintUnder(SIZEDGRID usergrid, int x, int y, int * outX, int * outY, int * val) {
    //up
    if (x-1 >= 0) {
        if (usergrid.grid[x-1][y] == -1) {
            //printf("t1%d, %d, %d\n", usergrid.grid[x-1][y], x, y);
            *outX = x-1;
            *outY = y;
            *val = usergrid.grid[x][y] == 1 ? 0 : 1;
            return 1;
        }
    }
    //down
    if (x+2 < usergrid.size) {
        if (usergrid.grid[x+2][y] == -1) {
            //printf("t2%d, %d, %d\n", usergrid.grid[x+2][y], x, y);
            *outX = x+2;
            *outY = y;
            *val = usergrid.grid[x][y] == 1 ? 0 : 1;
            return 1;
        }
    }
    return 0;
}

int placeHintRight(SIZEDGRID usergrid, int x, int y, int * outX, int * outY, int * val) {
    // left
    if (y-1 >= 0) {
        if (usergrid.grid[x][y-1] == -1) {
            *outX = x;
            *outY = y-1;
            *val = usergrid.grid[x][y] == 1 ? 0 : 1;
            return 1;
        }
    }
    // right
    if (y+2 < usergrid.size) {
        if (usergrid.grid[x][y+2] == -1) {
            *outX = x;
            *outY = y+2;
            *val = usergrid.grid[x][y] == 1 ? 0 : 1;
            return 1;
        }
    }
    return 0;
}

int checkIfSpaceBetweenTwoSameUnder(SIZEDGRID usergrid, int x, int y) {
    if (x+2 < usergrid.size && usergrid.grid[x][y] != -1) {
        if (usergrid.grid[x][y] == usergrid.grid[x+2][y] && usergrid.grid[x+1][y] == -1) {
            return 1;
        }
    }
    return 0;
}

int checkIfSpaceBetweenTwoSameRight(SIZEDGRID usergrid, int x, int y) {
    if (y+2 < usergrid.size && usergrid.grid[x][y] != -1) {
        if (usergrid.grid[x][y] == usergrid.grid[x][y+2] && usergrid.grid[x][y+1] == -1) {
            return 1;
        }
    }
    return 0;
}

void placeHintInSpace(int x, int y, int baseVal, int *outX, int *outY, int *val) {
    *outX = x;
    *outY = y;
    *val = baseVal == 1 ? 0 : 1;
}

int checkIfLineHave2Empty(SIZEDGRID usergrid, int lineNum) {
    int minusOneCounter = 0;
    for (int j = 0; j < usergrid.size; ++j) {
        if (usergrid.grid[lineNum][j] == -1) {
            minusOneCounter++;
        }
    }
    return minusOneCounter == 2 ? 1 : 0;
}

int checkIfColumnHave2Empty(SIZEDGRID usergrid, int columnNum) {
    int minusOneCounter = 0;
    for (int j = 0; j < usergrid.size; ++j) {
        if (usergrid.grid[j][columnNum] == -1) {
            minusOneCounter++;
        }
    }
    return minusOneCounter == 2 ? 1 : 0;
}

int placeHintIfSameLine(SIZEDGRID usergrid, int lineNum, int * x, int * y, int * val) {
    for (int i = 0; i < usergrid.size; ++i) {
        if (isLineFull(usergrid, lineNum)) {  // elimine automatiquement l'actuelle
            int similar = 1;
            for (int j = 0; j < usergrid.size; ++j) {
                // bancale la condition non ?
                if (usergrid.grid[lineNum][j] != usergrid.grid[i][j] && usergrid.grid[lineNum][j] != -1) {
                    similar = 0;
                }
            }
            if (similar) {
                for (int j = 0; j < usergrid.size; ++j) {
                    if (usergrid.grid[lineNum][j] == -1) {
                        *x = lineNum;
                        *y = j;
                        *val = usergrid.grid[i][j];
                    }
                }
            }
        }
    }
    return 0;
}

int placeHintIfSameColumn(SIZEDGRID usergrid, int columnNum, int * x, int * y, int * val) {
    for (int i = 0; i < usergrid.size; ++i) {
        if (isColumnFull(usergrid, columnNum)) {  // elimine automatiquement l'actuelle
            int similar = 1;
            for (int j = 0; j < usergrid.size; ++j) {
                // bancale la condition non ?
                if (usergrid.grid[j][columnNum] != usergrid.grid[i][j] && usergrid.grid[j][columnNum] != -1) {
                    similar = 0;
                }
            }
            if (similar) {
                for (int j = 0; j < usergrid.size; ++j) {
                    if (usergrid.grid[j][columnNum] == -1) {
                        *x = j;
                        *y = columnNum;
                        *val = usergrid.grid[j][i];
                    }
                }
            }
        }
    }
    return 0;
}

int isLineFull(SIZEDGRID usergrid, int lineNum) {
    for (int i = 0; i < usergrid.size; ++i) {
        if (usergrid.grid[lineNum][i] == -1) {
            return 0;
        }
    }
    return 1;
}

int isColumnFull(SIZEDGRID usergrid, int columnNum) {
    for (int i = 0; i < usergrid.size; ++i) {
        if (usergrid.grid[columnNum][i] == -1) {
            return 0;
        }
    }
    return 1;
}