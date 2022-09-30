/* ===================================================================== *
 *
 * fichier donnees.c
 *
 * ===================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tri.h"
#include "donnees.h"

void Choix(ITEM *listItem);

int compareAge(const void *a, const void *b) {
    return ((ITEM *) b)->age - ((ITEM *) a)->age;
}

int compareAgeDec(const void *a, const void *b) {
    return ((ITEM *) a)->age - ((ITEM *) b)->age;
}

int compareName(const void *a, const void *b) {
    return ((ITEM *) a)->nom - ((ITEM *) b)->nom;
}

int compareFirstname(const void *a, const void *b) {
    return ((ITEM *) a)->prenom - ((ITEM *) b)->prenom;
}

void Lire() {
    int i;
    char *pe;
    ITEM *ListITEM = NULL;
    ITEM *LastCell = NULL;

    while (TRUE) {
        char cas[10];
        printf("*----------------------------*\n");

        printf("- 0 ou T - Quitter la Saisie pour le mode Tri\n");
        printf("- 1 ou A - Saisie de données\n");
        printf("- 2 ou Q - Quitter \n");

        scanf("%s", cas);
        switch (cas[0]) {
            case '0':
            case 't':
            case 'T':
                Choix(ListITEM);
                break;
            case '1':
            case 's':
            case 'S':
                // Allocation memory
                pe = (ITEM *) (malloc(sizeof(ITEM)));
                //Mandatory
                if (pe == NULL) {
                    printf(" no memory \n");
                    exit(1);
                }
                setParametersI(pe);
                // 1er element: traitement particulier, car ListEtudiant a fixer
                if (LastCell == NULL) {
                    ListITEM = pe; // liste fixee
                    LastCell = pe;
                } else {
                    // Rattachement
                    LastCell->next = pe;
                    LastCell = pe; // l'element que l'on vient de creer est desormais le last
                };
                break;
            case '2':
            case 'q':
            case 'Q':
                exit(0);
        }
    }
}

void setParametersI(ITEM *pe) {
    char nom[40];
    char prenom[20];
    int age;
    printf("*----------------------------*\n");
    printf("> nom    : ");
    scanf("%s", nom);
    strcpy(pe->nom, nom);

    printf("> prenom : ");
    scanf("%s", prenom);
    strcpy(pe->prenom, prenom);

    printf("> age    : ");
    scanf("%d", &age);
    pe->age = age;
    pe->next = NULL;
}

/* ===================================================================== */

void Afficher(ITEM *listItem) {

    ITEM *pe = listItem;
    printf("\n*** Liste des donnees :\n\n");
    while (pe != NULL) {
        printf("Nom    : %s \n", pe->nom);
        printf("Prenom : %s \n", pe->prenom);
        printf("Age    : %d \n\n", pe->age);
        pe = pe->next;
    }
}

void Choix(ITEM *ListITEM) {
    char cas[10];

    while (TRUE) {
        printf("*------------------------------------------*\n");

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
                qsort(ListITEM, MAX_ITEM, sizeof *ListITEM, compareAge);
                Afficher(ListITEM);
                break;
            case '2':
            case 'D':
            case 'd':
                qsort(ListITEM, MAX_ITEM, sizeof *ListITEM, compareAgeDec);
                Afficher(ListITEM);
                break;
            case '3':
            case 'N':
            case 'n':
                qsort(ListITEM, MAX_ITEM, sizeof *ListITEM, compareName);
                Afficher(ListITEM);
                break;
            case '4':
            case 'P':
            case 'p':
                qsort(ListITEM, MAX_ITEM, sizeof *ListITEM, compareFirstname);
                Afficher(ListITEM);
                break;
            default:
                printf("! Choix incorrect [%s] : entrer une autre valeur\n\n", cas);
        }
    }
}




