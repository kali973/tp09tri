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

/* ===================================================================== */

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

/* ===================================================================== */

void Choix(ITEM items[], int nb_items) {
    char cas[10];

    while (TRUE) {
        printf("*** Tri :\n");
        printf("- 1 ou A - numerique selon l'Age (croissant)\n");
        printf("- 2 ou D - numerique selon l'Age (Decroissant)\n");
        printf("- 3 ou N - alphabetique sur le Nom\n");
        printf("- 4 ou P - alphabetique sur le Prenom\n");
        printf("- 0 ou Q - quitter\n");

        scanf("%s", cas);

        switch (cas[0]) {
            case '0':
            case 'q':
            case 'Q':
                exit(0);
            case '1':
            case 'A':
            case 'a':
                TrierAgeAsc(items, nb_items);
                Afficher(items, nb_items);
                break;
            case '2':
            case 'D':
            case 'd':
                TrierAgeDes(items, nb_items);
                Afficher(items, nb_items);
                break;
            case '3':
            case 'N':
            case 'n':
                TrierNom(items, nb_items);
                Afficher(items, nb_items);
                break;
            case '4':
            case 'P':
            case 'p':
                TrierPrenom(items, nb_items);
                Afficher(items, nb_items);
                (nb_items, 5, sizeof(nb_items), nb_items);
                break;
            default:
                printf("! Choix incorrect [%s] : entrer une autre valeur\n\n", cas);
        }
    }
}

/* ===================================================================== */

int main(int argc, char *argv[]) {
    ITEM items[MAX_ITEM];
    int nb_items;

    Lire(items, &nb_items);
    Choix(items, nb_items);
    Afficher(items, nb_items);
    exit(0);
}

/* ====================================================== The End ====== */



