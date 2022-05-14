#ifndef TAKUZU_AUTOSOLVE_H
#define TAKUZU_AUTOSOLVE_H

#include "grid.h"

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


#endif //TAKUZU_AUTOSOLVE_H
