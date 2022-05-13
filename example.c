//
// Created by Paul on 15/04/2022.
//

#include "example.h"
#include <stdlib.h>


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