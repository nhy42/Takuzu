void printGrid(SIZEDGRID grid, SIZEDGRID mask, int ignoreMask);
void pickCoords(int* x, int* y, int size);
int getSize();
int getValue(int x, int y);
SIZEDGRID getMask(int size);
void play();
void autoSolveInterface();
void genGridInterface();
int mainMenu();