/* ===================================================================== *
 *
 * fichier tri.c
 *
 * ===================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tri.h"
#include "donnees.h"

void TrierAgeAsc(ITEM items[], int nb_items) {
    int i, j;
    ITEM swap;

    for (i = 0; i < nb_items; i++)
        for (j = i + 1; j < nb_items; j++)
            if (items[i].age > items[j].age) {
                swap = items[j];
                items[j] = items[i];
                items[i] = swap;
            }
}

void TrierAgeDes(ITEM items[], int nb_items) {
    int i, j;
    ITEM swap;

    for (i = 0; i < nb_items; i++)
        for (j = i + 1; j < nb_items; j++)
            if (items[i].age < items[j].age) {
                swap = items[j];
                items[j] = items[i];
                items[i] = swap;
            }
}

void TrierNom(ITEM items[], int nb_items) {
    int i, j;
    ITEM swap;

    for (i = 0; i < nb_items; i++)
        for (j = i + 1; j < nb_items; j++)
            if (items[i].nom < items[j].nom) {
                swap = items[j];
                items[j] = items[i];
                items[i] = swap;
            }
}

void TrierPrenom(ITEM items[], int nb_items) {
    int i, j;
    ITEM swap;

    for (i = 0; i < nb_items; i++)
        for (j = i + 1; j < nb_items; j++)
            if (items[i].prenom < items[j].prenom) {
                swap = items[j];
                items[j] = items[i];
                items[i] = swap;
            }
}

int main(int argc, char *argv[]) {

    Lire();
    return 0;
}




