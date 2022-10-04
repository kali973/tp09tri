/* ===================================================================== *
 *
 * fichier donnees.c
 *
 * ===================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tri.h"
#include "donnees.h"

#define MAX_FILE_NAME  20
#define MAX_LINE  80

void Choix(ITEM *listItem);

int haveFile(char *fname);

void printFile(char *fname);

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
void Trier(ITEM items[], int nb_items) {
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

void Lire(int argc, char **argv) {
    int i;
    char *pe;
    ITEM *ListITEM = NULL;
    ITEM *LastCell = NULL;

    char mode;

    while (TRUE) {
        char cas[10];
        printf("*----------------------------*\n");

        printf("- 0 ou T - Tri\n");
        printf("- 1 ou S - Saisie des données\n");
        printf("- 2 ou L - Lecture des données\n");
        printf("- 3 ou Q - Quitter \n");

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
            case 'l':
            case 'L':

                if (!(haveFile("/root/CLionProjectsTP/tp09tri/tri.txt"))) {
                    printf(" file %s does not exist\n", "tri.txt");
                    exit(1);
                }

                printFile("/root/CLionProjectsTP/tp09tri/tri.txt");
                break;
            case '3':
            case 'q':
            case 'Q':
                exit(0);
        }
    }

}

void printFile(char *fname) {
    FILE *fp;
    char lineContent[MAX_LINE];
    fp = fopen(fname, "r");
    if (fp == NULL) {
        printf("in printFile, file %s open error\n", fname);
        exit(1);
    }
    while ((fgets(lineContent, sizeof(lineContent), fp) != NULL)) {
        printf("%s", lineContent);
    };
    fclose(fp);
}

int haveFile(char *fname) {
    FILE *fp;
    fp = fopen(fname, "r");
    if (fp == NULL) {
        return 0;
    } else {
        fclose(fp);
        return 1;
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




