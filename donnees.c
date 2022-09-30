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

/* =======================================*/
/* fonction comparaison fournie a qsort() */
static int compare (const void* str1,const void* str2)
{
    const char **pp1=(const char **) &str1;
    const char **pp2=(const char **) &str2;
    return(strcmp(*pp1,*pp2));
}

void Lire() {
    int i;
    char *pe;
    ITEM *ListITEM = NULL;
    ITEM *LastCell = NULL;

    while (TRUE) {
        char cas[10];
        printf("*----------------------------*\n");

        printf("- 0 ou Q - Quitter la Saisie\n");
        printf("- 1 ou A - Saisie de données\n");

        scanf("%s", cas);
        switch (cas[0]) {
            case '0':
            case 'q':
            case 'Q':
                Choix(ListITEM);
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
                qsort (ListITEM, sizeof ListITEM / sizeof *ListITEM, sizeof *ListITEM, compare);
                Afficher(ListITEM);
                break;
            case '2':
            case 'D':
            case 'd':
                qsort (ListITEM, sizeof ListITEM / sizeof *ListITEM, sizeof *ListITEM, compare);
                Afficher(ListITEM);
                break;
            case '3':
            case 'N':
            case 'n':
                qsort (ListITEM, sizeof ListITEM / sizeof *ListITEM, sizeof *ListITEM, compare);
                Afficher(ListITEM);
                break;
            case '4':
            case 'P':
            case 'p':
                qsort (ListITEM, sizeof ListITEM / sizeof *ListITEM, sizeof *ListITEM, compare);
                Afficher(ListITEM);
                break;
            default:
                printf("! Choix incorrect [%s] : entrer une autre valeur\n\n", cas);
        }
    }
}




