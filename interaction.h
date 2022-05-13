//
// Created by Paul on 15/04/2022.
//
#include "grid.h"
#include "example.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef TAKUZU_INTERFACE_H
#define TAKUZU_INTERFACE_H

void printGrid(SIZEDGRID grid, SIZEDGRID mask, int ignoreMask);
void pickCoords(int* x, int* y, int size);
int getSize();
int mainMenu();

#endif //TAKUZU_INTERFACE_H
