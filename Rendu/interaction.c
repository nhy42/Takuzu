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
        printf("%d ", i);
        if (i < 10) {
            printf(" ");
        }
    }
    printf("\n\n");
    for (int i = 0; i < grid.size; i++) {
        printf("%d    ", i);
        if (i < 10) {
            printf(" ");
        }
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
    while (answer > 2 || answer < 1) {
        printf("\n1) Generer un masque\n2) Saisir un masque\n> ");//3) Jouer\n
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
        //printf("Pas encore implémenté\nSize = 8\n");
        size = 16;
        grid = getGrid16();
    }

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
        if (isNewValValid(usergrid, x, y, val, 1)) {
            usergrid.grid[x][y] = val;
            if (checkEnded(usergrid)) {
                end = 1;
            }
        } else {
            life--;
            printf("Il vous reste %d vies\n", life);
            if (giveHint(usergrid, &x, &y, &val)) {
                printf("Et pourquoi pas mettre un petit %d en (%d, %d)\n", val, x, y);
            } else {
                printf("Il n'est pas possible de fournir un indice\n");
            }
        }
    }



    if (life == 0) {
        printf("Perdu !\nLa grille etait :\n");
        printGrid(grid, grid, 1);
    } else {
        printf("Felicitations ! Vous avez fini la grille !\n");
    }
    // EH SALUT TOI, FREE TA MEMOIRE
    freeGrid(&usergrid);
    freeGrid(&mask);
    freeGrid(&grid);
}

void autoSolveInterface() {
    int size = getSize();
    if (size == 16) {
        printf("Attention, la resolution pour une grille en 16x16 n'est pas conseillee, car trop longue.\n");
    }
    printf("Voulez-vous :\n");
    int answer = -1;
    while (answer > 2 || answer < 1) {
        // ^ comme ca on accepte aussi 4, 8 et 16 (jme suis fait avoir en faisant les tests, donc BON)
        printf("\n1) Entrer la grille\n2) Utiliser une grille predefinie\n> ");
        scanf("%d", &answer);
    }
    SIZEDGRID grid, mask, usergrid;
    usergrid = allocGrid(size);
    fillWithInt(&usergrid, -1);
    switch (answer) {
        case 1:
            grid = allocGrid(size);
            mask = allocGrid(size);
            printf("Vous devrez ensuite entrer un masque pour choisir les valeurs inconnues, entrez n'importe quelle valeur pour ces cases\n");
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    grid.grid[i][j] = getValue(i, j);
                }
            }
            printGrid(grid, grid, 1);
            printf("Entrez maintenant le masque\n");
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    mask.grid[i][j] = getValue(i, j);
                }
            }
            printf("Voici la grille :");
            printGrid(grid, mask, 0);
            addOneOnTwoUsingMaks(grid, &usergrid, mask);
            break;
        case 2:
            if (size == 4) {
                grid = getGrid4();
            } else if (size == 8) {
                grid = getGrid8();
            } else if (size == 16) {
                grid = getGrid16();
            } else {
                printf("Erreur inconnue");
                freeGrid(&usergrid);
                freeGrid(&mask);
                freeGrid(&grid);
                return;
            }
            mask = genMask(size);
            addOneOnTwoUsingMaks(grid, &usergrid, mask);
            printf("Grille de depart :\n");
            printGrid(usergrid, usergrid, 1);
            break;
        default:
            printf("Erreur inconnue");
    }

    answer = -1;
    while (answer > 2 || answer < 1) {
        // ^ comme ca on accepte aussi 4, 8 et 16 (jme suis fait avoir en faisant les tests, donc BON)
        printf("Voulez vous afficher les etapes de resolution ?\n");
        printf("\n1) Oui\n2) Non\n> ");
        scanf("%d", &answer);
    }

    MOVE * moveList = NULL;
    if (recursiveSolve(&usergrid, &moveList, (answer == 2 ? 0 : 1))) {
        printf("La resolution a fonctionnee\n");
        printGrid(usergrid, usergrid, 1);
    } else {
        printf("La resolution a echouee :(\n");
    }
    freeGrid(&usergrid);
    freeGrid(&grid);
    freeGrid(&mask);

    /*
    SIZEDGRID grid = getGrid8();//getGrid4();//
    SIZEDGRID mask = genMask(8);//getMask4();//
    SIZEDGRID usergrid = allocGrid(8);//allocGrid(4);//
    fillWithInt(&usergrid, -1);
    addOneOnTwoUsingMaks(grid, &usergrid, mask);
    printGrid(usergrid, mask, 1);

    MOVE * moveList = NULL;

    if (recursiveSolve(&usergrid, &moveList)) {
        printf("ck\n");
        printf("PTDR QUOI\n");
    } else {
        printf("aww, not wowwkin\n");
    }

    printf("Wait what ca a marché !?\n");
    printGrid(usergrid, mask, 1);*/

/*
    MOVE * moveList = NULL;
    moveList = newMoveWithValues(1, 1, 0, 0, moveList);
    moveList = newMoveWithValues(1, 1, 0, 0, moveList);
    moveList = newMoveWithValues(1, 1, 0, 0, moveList);
    moveList = newMoveWithValues(1, 1, 1, 0, moveList);
    moveList = newMoveWithValues(1, 1, 0, 0, moveList);
    moveList = newMoveWithValues(1, 1, 0, 0, moveList);
    printf("rahoue");
    rollbackGridToHypothesis(&usergrid, &moveList);
    printf("ono");

    MOVE * temp = moveList;
    do {
        printf("%d\n", temp);
        temp = temp->previous;
    } while (temp->previous != NULL);
    */
    /*
    int x, y, val = 0, e;
    getNextCaseToDo(usergrid, 0,&x, &y, &val);
    printf("%d, %d : %d\n", x, y, val);
    getNextCaseToDo(usergrid, 1, &x, &y, &val);
    printf("%d, %d : %d\n", x, y, val);
    getNextCaseToDo(usergrid, 2, &x, &y, &val);
    printf("%d, %d : %d\n", x, y, val);*/

}

void genGridInterface() {
    printf("Ceci est simplement une demonstration de generation de grille 4x4 grace a notre algorithme de resolution.\n");
    SIZEDGRID usergrid = allocGrid(4);
    fillWithInt(&usergrid, -1);
    MOVE * moveList = NULL;
    printf("Input :\n");
    printGrid(usergrid, usergrid, 1);
    recursiveSolve(&usergrid, &moveList, 1);
    printf("Output :\n");
    printGrid(usergrid, usergrid, 1);
    freeGrid(&usergrid);
}

int mainMenu() {
    printf("Que souhaitez vous faire ?\n");
    int answer = -1;
    while (answer > 4 || answer < 1) {
        printf("1) Jouer\n2) Resoudre automatiquement une grille\n3) Generer une grille\n4) Quitter\n> ");
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
