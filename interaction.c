//
// Created by Paul on 15/04/2022.
//
#include "grid.h"
#include "interaction.h"
#include "autosolve.h"
#include <stdio.h>
#include <stdlib.h>

void printGrid(SIZEDGRID grid, SIZEDGRID mask, int ignoreMask) { // si ingoreMask = 1, passer n'importe quoi en masque
    printf("      ");
    for (int i = 0; i < grid.size; i++) {
        printf("%c  ", i + '0');
    }
    printf("\n\n");
    for (int i = 0; i < grid.size; i++) {
        printf("%d     ", i);
        for (int j = 0; j < grid.size; j++) {
            if (mask.grid[i][j] == 1 || ignoreMask) {
                printf("%c  ", grid.grid[i][j] == -1 ? '_' : grid.grid[i][j] + '0');
            } else {
                printf("_  ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void pickCoords(int* x, int* y, int size) {
    printf("Choisissez une case.\n");
    int temp = -1;
    while (temp >= size || temp < 0) {
        temp = -1;
        printf("Ligne:\n> ");
        //getchar();
        scanf("%d", &temp);
    }
    *x = temp;
    temp = -1;
    while (!(0 <= temp && temp < size)) {
        printf("Colonne:\n> ");
        getchar();
        scanf("%d", &temp);
    }
    *y = temp;
}

int getSize() {
    printf("Quelle taille de grille souhaitez vous ?\n1) 4\n2) 8\n3) 16\n> ");
    int answer = -1;
    getchar();
    while ((answer > 4 || answer < 1) && answer != 8 && answer != 16) {
        // ^ comme ca on accepte aussi 4, 8 et 16 (jme suis fait avoir en faisant les tests, donc BON)
        printf("\n1) 4\n2) 8\n3) 16\n> ");
        scanf("%d", &answer);
    }
    switch (answer) {
        case 1:
        case 4:
            return 4;
        case 2:
        case 8:
            return 8;
        case 3:
        case 16:
            return 16;
        default:
            printf("In getSize(), interface.c, answer is NaN");
            return 0;
    }
}

int getValue(int x, int y) {
    int answer = -1;
    while (answer > 1 || answer < 0) {
        printf("Valeur de la case en (%d, %d):\n> ", x, y);
        scanf("%d", &answer);
    }
    return answer;
}

SIZEDGRID getMask(int size) {
    SIZEDGRID mask;
    printf("Voulez-vous :");
    int answer = -1;
    while (answer > 3 || answer < 1) {
        printf("\n1) Générer un masque\n2) Saisir un masque\n3) Jouer\n> ");
        scanf("%d", &answer);
    }
    if (answer == 1 || answer == 3) {
        // là j'avoue que j'ai pas compris la différence dans l'énoncé
        mask = genMask(size);
    } else {
        mask = allocGrid(size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                mask.grid[i][j] = getValue(i, j);
            }
        }
    }
    return mask;
}

void play() {
    int size = getSize();
    SIZEDGRID grid;
    if (size == 4) {
        grid = getGrid4();
    } else if (size == 8) {
        grid = getGrid8();
    } else {
        printf("Pas encore implémenté\nSize = 8\n");
        size = 8;
        grid = getGrid8();
    }

    // isValid(grid, 0, 3, 1, 0) ? printf("valid") : printf("not");

    SIZEDGRID mask = getMask(size);
    printf("Voici le masque :\n");
    printGrid(mask, mask, 1);
    int life = 3, end = 0; // todo : changer le nb de vies

    SIZEDGRID usergrid = allocGrid(size);
    fillWithInt(&usergrid, -1);
    addOneOnTwoUsingMaks(grid, &usergrid, mask);

    int val;
    while (life > 0 && !end) {
        printf("Voici la grille :\n");
        printGrid(usergrid, mask, 1);

        int x, y;
        pickCoords(&x, &y, size);
        while (mask.grid[x][y]) {
            printf("Cette case ne peut pas être modifiee\nEntrez une autre case :\n");
            pickCoords(&x, &y, size);
        }
        val = getValue(x, y);
        if (isValid(usergrid, x, y, val, 1)) {
            usergrid.grid[x][y] = val;
            if (checkEnded(usergrid)) {
                end = 1;
            }
        } else {
            if (giveHint(usergrid, &x, &y, &val)) {
                printf("Et pourquoi pas mettre un petit %d en (%d, %d)\n", val, x, y);
            } else {
                printf("Il n'est pas possible de fournir un indice\n");
            }
            life--;
        }
    }



    if (life == 0) {
        printf("Perdu !\nLa grille etait :\n");
        printGrid(grid, grid, 1);
    } else {
        printf("Felicitations ! Vous avez termine la grille\n");
    }
    // EH SALUT TOI, FREE TA MEMOIRE
    freeGrid(&usergrid);
    freeGrid(&mask);
    freeGrid(&grid);
}


void autoSolveInterface() {

}

void genGridInterface() {

}


int mainMenu() {
    printf("Que souhaitez vous faire ?\n");
    int answer = -1;
    while (answer > 4 || answer < 1) {
        printf("1) Jouer\n2) Résoudre automatiquement une grille\n3) Générer une grille\n4) Quitter\n> ");
        scanf("%d", &answer);
    }
    getchar(); // marche meme pas :(
    switch (answer) {
        case 1:
            play();
            return 0;
        case 2:
            autoSolveInterface();
            return 0;
        case 3:
            genGridInterface();
            return 0;
        case 4:
            return -1;
        default:
            printf("In mainMenu(), interface.c, answer is NaN");
            return 0;
    }
}
