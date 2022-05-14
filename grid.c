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

SIZEDGRID getGrid16() {
    SIZEDGRID grid;
    grid.grid = convertToTakuzu16(exampleGrid16);
    grid.size = 16;
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
