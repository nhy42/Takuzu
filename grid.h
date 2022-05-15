#ifndef TAKUZU_GRID_H
#define TAKUZU_GRID_H

typedef int** GRID;

typedef struct {
    GRID grid;
    int size;
} SIZEDGRID;


SIZEDGRID genMask(int size);
SIZEDGRID allocGrid(int size);
void freeGrid(SIZEDGRID * grid);
int** convertToTakuzu4(int tab4[4][4]);
int** convertToTakuzu8(int tab8[8][8]);
int** convertToTakuzu16(int tab8[16][16]);
SIZEDGRID getGrid4();
SIZEDGRID getMask4(); // debug
SIZEDGRID getGrid8();
SIZEDGRID getGrid16();
void fillWithInt(SIZEDGRID * gridToFill, int valueToFill);
void addOneOnTwoUsingMaks(SIZEDGRID gridOne, SIZEDGRID * gridTwo, SIZEDGRID mask);
int checkZeroEqualOne(SIZEDGRID usergrid, int x, int y, int val);
int checkMax2Following(SIZEDGRID usergrid, int x, int y, int val);
int checkSimilarLinesOrColumns(SIZEDGRID usergrid, int x, int y, int val);
int isNewValValid(SIZEDGRID usergrid, int x, int y, int val, int showErr);
int isGridValid(SIZEDGRID usergrid);
int checkEnded(SIZEDGRID usergrid);
int countEmpty(SIZEDGRID usergrid);

#endif //TAKUZU_GRID_H
