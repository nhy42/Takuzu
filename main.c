#include <stdio.h>
// a delete ensuite
#include <stdlib.h>
#include "example.h"
#include "grid.h"
// end a delete ensuite
#include "interaction.h"

int main() {/*
    SIZEDGRID test = allocGrid(8);
    fillWithInt(&test, -1);
    printGrid(test, test, 1);
    */
    printf("Bienvenue !\n ");
    int exitCode = 0;
    while (exitCode != -1) {
        exitCode = mainMenu();
    }
}