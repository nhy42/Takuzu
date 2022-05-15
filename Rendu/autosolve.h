#ifndef TAKUZU_AUTOSOLVE_H
#define TAKUZU_AUTOSOLVE_H

#include "grid.h"

struct move {
    int x;
    int y;
    int hypothesis;  // 1 or 0
    int changedOnce; // 1 or 0 // not used
    struct move * previous;
};
typedef struct move MOVE;
//typedef struct MOVE * MOVESTACK;  //bof

int giveHint(SIZEDGRID usergrid, int * x, int * y, int * val);

int checkIfUnderIsTheSame(SIZEDGRID usergrid, int x, int y);
int checkIfRightIsTheSame(SIZEDGRID usergrid, int x, int y);
int placeHintUnder(SIZEDGRID usergrid, int x, int y, int * outX, int * outY, int * val);
int placeHintRight(SIZEDGRID usergrid, int x, int y, int * outX, int * outY, int * val);

int checkIfSpaceBetweenTwoSameUnder(SIZEDGRID usergrid, int x, int y);
int checkIfSpaceBetweenTwoSameRight(SIZEDGRID usergrid, int x, int y);
void placeHintInSpace(int x, int y, int baseVal, int *outX, int *outY, int *val);

int checkIfLineHave2Empty(SIZEDGRID usergrid, int lineNum);
int checkIfColumnHave2Empty(SIZEDGRID usergrid, int columnNum);
int placeHintIfSameLine(SIZEDGRID usergrid, int lineNum, int * x, int * y, int * val);
int placeHintIfSameColumn(SIZEDGRID usergrid, int columnNum, int * x, int * y, int * val);
int isLineFull(SIZEDGRID usergrid, int lineNum);
int isColumnFull(SIZEDGRID usergrid, int columnNum);

int countSymbolInLine(SIZEDGRID usergrid, int lineNum, int * zero, int * one, int * minusOne);
int countSymbolInColumn(SIZEDGRID usergrid, int columnNum, int * zero, int * one, int * minusOne);
int placeHintFillLine(SIZEDGRID usergrid, int lineNum, int * x, int * y);
int placeHintFillColumn(SIZEDGRID usergrid, int columnNum, int * x, int * y);

MOVE * allocMove();
void freeMove(MOVE * moveToFree);
MOVE * newMoveWithValues(int x, int y, int hypothesis, int changedOnce, MOVE * previous);

void rollbackGridToHypothesis(SIZEDGRID * grid, MOVE ** moveList);
int getNextCaseToDo(SIZEDGRID usergrid, int rank, int * x, int * y, int * val);
int recursiveSolve(SIZEDGRID * usergrid, MOVE ** moveList, int printSteps);

#endif //TAKUZU_AUTOSOLVE_H
