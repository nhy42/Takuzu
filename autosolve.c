#include "grid.h"
#include "autosolve.h"
#include "interaction.h"


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

    // troisieme indice : les lignes avec deux trous, différentes

    for (int i = 0; i < usergrid.size; ++i) {
        if (checkIfColumnHave2Empty(usergrid, i)) {
            if (placeHintIfSameColumn(usergrid, i, x, y, val)) {
                //printf("e%d, %d\n", *x, *y);
                return 1;
            }
        }
        if (checkIfLineHave2Empty(usergrid, i)) {
            if (placeHintIfSameLine(usergrid, i, x, y, val)) {
                //printf("f%d, %d\n", *x, *y);
                return 1;
            }
        }
    }

    // quatrieme indice : si une ligne a deja size/2 d'une valeur dedans
    int zero, one, minusOne;
    for (int i = 0; i < usergrid.size; ++i) {
        if (countSymbolInLine(usergrid, i, &zero, &one, &minusOne)) {
            placeHintFillLine(usergrid, i, x, y);
            *val = zero == usergrid.size / 2 ? 1 : 0;
            //printf("g%d, %d\n", *x, *y);
            return 1;
        }
        if (countSymbolInColumn(usergrid, i, &zero, &one, &minusOne)) {
            placeHintFillColumn(usergrid, i, x, y);
            *val = zero == usergrid.size / 2 ? 1 : 0;
            //printf("h%d, %d, %d\n", *x, *y, i);
            return 1;
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
        if (isLineFull(usergrid, i)) {  // elimine automatiquement l'actuelle
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
                        *val = usergrid.grid[i][j] == 1 ? 0 : 1;
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

int placeHintIfSameColumn(SIZEDGRID usergrid, int columnNum, int * x, int * y, int * val) {
    for (int i = 0; i < usergrid.size; ++i) {
        if (isColumnFull(usergrid, i)) {  // elimine automatiquement l'actuelle
            //printf("deeper %d\n", i);
            int similar = 1;
            for (int j = 0; j < usergrid.size; ++j) {
                // bancale la condition non ?
                if (usergrid.grid[j][columnNum] != usergrid.grid[j][i] && usergrid.grid[j][columnNum] != -1) {
                    similar = 0;
                }
            }
            if (similar) {
                for (int j = 0; j < usergrid.size; ++j) {
                    if (usergrid.grid[j][columnNum] == -1) {
                        *x = j;
                        *y = columnNum;
                        *val = usergrid.grid[j][i] == 1 ? 0 : 1;
                        return 1;
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
        if (usergrid.grid[i][columnNum] == -1) {
            return 0;
        }
    }
    return 1;
}

int countSymbolInLine(SIZEDGRID usergrid, int lineNum, int * zero, int * one, int * minusOne) {
    *zero = 0, *one = 0, *minusOne = 0;
    for (int j = 0; j < usergrid.size; ++j) {
        if (usergrid.grid[lineNum][j] == 0) {
            *zero += 1;
        } else if (usergrid.grid[lineNum][j] == 1) {
            *one += 1;
        } else if (usergrid.grid[lineNum][j] == -1) {
            *minusOne += 1;
        }
    }
    return (*zero == usergrid.size / 2 || *one == usergrid.size / 2) && *minusOne != 0;
}

int countSymbolInColumn(SIZEDGRID usergrid, int columnNum, int * zero, int * one, int * minusOne) {
    *zero = 0, *one = 0, *minusOne = 0;
    for (int j = 0; j < usergrid.size; ++j) {
        if (usergrid.grid[j][columnNum] == 0) {
            *zero += 1;
        } else if (usergrid.grid[j][columnNum] == 1) {
            *one += 1;
        } else if (usergrid.grid[j][columnNum] == -1) {
            *minusOne += 1;
        }
    }
    return (*zero == usergrid.size / 2 || *one == usergrid.size / 2) && *minusOne != 0;
}

int placeHintFillLine(SIZEDGRID usergrid, int lineNum, int * x, int * y) {
    for (int j = 0; j < usergrid.size; ++j) {
        if (usergrid.grid[lineNum][j] == -1) {
            *x = lineNum;
            *y = j;
            return 1;
        }
    }
    return 0;
}

int placeHintFillColumn(SIZEDGRID usergrid, int columnNum, int * x, int * y) {
    for (int j = 0; j < usergrid.size; ++j) {
        if (usergrid.grid[j][columnNum] == -1) {
            *x = j;
            *y = columnNum;
            return 1;
        }
    }
    return 0;
}




MOVE * allocMove() {
    return (MOVE *) malloc(sizeof(MOVE));
}

void freeMove(MOVE * moveToFree) {
    if (moveToFree != NULL) {
        free(moveToFree);
    }
}

MOVE * newMoveWithValues(int x, int y, int hypothesis, int changedOnce, MOVE * previous) {
    MOVE * newOne = allocMove();
    newOne->x = x;
    newOne->y = y;
    newOne->hypothesis = hypothesis;
    newOne->changedOnce = changedOnce;
    newOne->previous = previous;
    return newOne;
}

void rollbackGridToHypothesis(SIZEDGRID * usergrid, MOVE ** moveList) {
    MOVE *temp = *moveList;
    int stop = 0;
    do {
        *moveList = temp->previous;
        usergrid->grid[temp->x][temp->y] = -1;
        if (temp->hypothesis == 1 || *moveList == NULL) {
            stop = 1;
        }
        freeMove(temp);
        temp = *moveList;
    } while (!stop);
    *moveList = temp;
}

int getNextCaseToDo(SIZEDGRID usergrid, int rank, int * x, int * y, int * val) {
    int count = 0;
    for (int i = 0; i < usergrid.size; ++i) {
        for (int j = 0; j < usergrid.size; ++j) {
            if (usergrid.grid[i][j] == -1) {
                if (rank / 2 == count / 2) {
                    *x = i;
                    *y = j;
                    *val = rank % 2 == 0 ? (rand() % 2) : (*val == 1 ? 0 : 1);
                    return 0;
                }
                count += 2;
            }
        }
    }
    return 1;
}

int recursiveSolve(SIZEDGRID * usergrid, MOVE ** moveList) {
    int x, y, val;
    while(giveHint(*usergrid, &x, &y, &val)) {
        *moveList = newMoveWithValues(x, y, 0, 0, *moveList);
        usergrid->grid[x][y] = val;
    }
    if (isGridValid(*usergrid)) {
        if (checkEnded(*usergrid)) {
            //printf("Go b");
            return 1;
        } else {
            int result;
            int maxRank = countEmpty(*usergrid) * 2;  // total number of guesses to do
            //if (maxRank >= 28) {printf("|%d|\n", maxRank);}
            //if (maxRank == 28) { printGrid(*usergrid, *usergrid, 1);}
            int rank = 0;
            // x, y, et val sont des sortes de temp, donc pas besoin de les redéfinir ici
            do {
                //printf("|%d|", maxRank);
                getNextCaseToDo(*usergrid, rank, &x, &y, &val);
                *moveList = newMoveWithValues(x, y, 1, 0, *moveList);
                usergrid->grid[x][y] = val;
                result = recursiveSolve(usergrid, moveList);
                rank++;
                if (result == 0) {
                    rollbackGridToHypothesis(usergrid, moveList);
                }
            } while (rank < maxRank && result == 0);
            if (rank == maxRank) {
                return 0;
            } else if (result == 1) {
                //printf("a");
                return 1;
            } else {
                printf("in recursiveSolve, do while broke");
                return 0;
            }
        }
    } else {
        return 0;
    }
}
