/* ===================================================================== *
 *
 * fichier donnees.c
 *
 * ===================================================================== */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <unistd.h>
#include "tri.h"
#include "donnees.h"

#define BUFFER_SIZE 8000

void Choix(ITEM *listItem);

int writeFile(char *fname, ITEM *listItem);

ITEM *readFile(char *fname);

void LoadDisplay(ITEM *listItem, int ind);

int effacer(const char *filename);

int compareAge(const void *a, const void *b) {
    return ((ITEM *) b)->age < ((ITEM *) a)->age;
}

int compareAgeDec(const void *a, const void *b) {
    return ((ITEM *) a)->age > ((ITEM *) b)->age;
}

int compareName(const void *a, const void *b) {
    return ((ITEM *) a)->nom > ((ITEM *) b)->nom;
}

int compareFirstname(const void *a, const void *b) {
    return ((ITEM *) a)->prenom > ((ITEM *) b)->prenom;
}

/*--------------------------------------------*/
/* Fonction de lecture de la liste chainée    */
/*--------------------------------------------*/

void Lire(int argc, char **argv) {
    char *pe;
    char cas[10];
    ITEM *ListITEM = NULL;
    ITEM *LastCell = NULL;

    const char *nameFile = "/tri.txt";

    char buffer[BUFFER_SIZE];
    if (getcwd(buffer, BUFFER_SIZE) == NULL) {
        fprintf(stderr, "Cannot get current working directory path\n");
        if (errno == ERANGE) {
            fprintf(stderr, "Buffer size is too small.\n");
        }
        exit(EXIT_FAILURE);
    }

    printf("Current working directory: %s\n", buffer);

    const char *filename = strcat(buffer, nameFile);

    while (TRUE) {

        printf("\n");
        printf("- 0 ou T - Tri\n");
        printf("- 1 ou S - Saisie des données\n");
        printf("- 2 ou L - Lecture des données\n");
        printf("- 3 ou E - Effacer les données\n");
        printf("- 4 ou Q - Quitter \n\n");

        printf("=> ");
        scanf("%s", cas);
        switch (cas[0]) {
            case '0':
            case 't':
            case 'T':
                if (ListITEM == NULL) {
                    ListITEM = readFile(filename);
                }
                Choix(ListITEM);
                break;
            case '1':
            case 's':
            case 'S':
                // Allocation memory
                pe = (ITEM *) (malloc(sizeof(ITEM)));

                if (pe == NULL) {
                    printf(" no memory \n");
                    exit(1);
                }
                setParametersI(pe);

                if (LastCell == NULL) {
                    ListITEM = pe; // liste fixee
                    LastCell = pe;
                } else {
                    // Rattachement
                    LastCell->next = pe;
                    LastCell = pe;
                };
                writeFile(filename, ListITEM);
                break;
            case '2':
            case 'l':
            case 'L':
                if (readFile(filename) != -1) {
                    printf("Chargement terminé\n\n");
                } else {
                    printf("Chargement non effectué\n\n");
                }
                break;
            case '3':
            case 'e':
            case 'E':
                if (effacer(filename) != 0) {
                    printf("Non Suppression des données.\n\n");
                } else {
                    printf("Suppression des données terminées.\n\n");
                }
                break;
            case '4':
            case 'q':
            case 'Q':

                free(pe);
                free(LastCell);
                free(ListITEM);
                exit(0);
        }
    }
}

/*------------------------------------------------*/
/* Fonction de suppression des données du fichier */
/*------------------------------------------------*/

int effacer(const char *filename) {

    FILE *fp;
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("in readFile, file %s open error\n", filename);
        return -1;
    }
    fclose(fp);
    return 0;
}

/*--------------------------------------------*/
/* Fonction d'écriture de la liste chainée   */
/*--------------------------------------------*/

int writeFile(char *fname, ITEM *ListITEM) {
    FILE *fp;
    int i = 0;

    fp = fopen(fname, "w+");
    if (fp == NULL) {
        printf("in readFile, file %s open error\n", fname);
        return -1;
    }
    ITEM *pe = ListITEM;

    while (pe != NULL) {
        fprintf(fp, "%29s %19s %d\n", pe->nom, pe->prenom, pe->age);
        pe = pe->next;
        i++;
    }

    printf("\n*** Nombre d'enregistrement => %d\n\n", i);
    fclose(fp);
    return 0;
}

ITEM *readFile(char *fname) {
    FILE *fp;
    int ind = 0;

    ITEM *pe;
    ITEM *ListITEM = NULL;
    ITEM *LastCell = NULL;

    fp = fopen(fname, "r");
    if (fp == NULL) {
        printf("in readFile, file %s open error => File not found\n\n", fname);
        return NULL;
    }

    char *buffer = (char *) malloc(BUFFER_SIZE);
    char nom[30];
    char prenom[20];
    int age;
    char c;
    while ((c = fgetc(fp)) != EOF) {
        fgets(buffer, BUFFER_SIZE, fp);
        if (ferror(fp)) {
            fprintf(stderr, "Reading error with code %d\n", errno);
            return NULL;
        }
        pe = (ITEM *) malloc(sizeof(ITEM));

        sscanf(buffer, "%29s %19s %d", nom, prenom, &age);
        strcpy(pe->nom, &nom);
        strcpy(pe->prenom, &prenom);
        pe->age = age;
        ind++;
        if (LastCell == NULL) {
            ListITEM = pe;
            LastCell = pe;
        } else {
            LastCell->next = pe;
            LastCell = pe;
        }
    }

    fclose(fp);
    printf("\n*** Lecture des donnees fin => %d\n\n", ind);
    if (ind > 0) {
        LoadDisplay(ListITEM, ind);
    }
    return ListITEM;
}

/*--------------------------------------------*/
/* Fonction d'Affichage de la liste chainée   */
/*--------------------------------------------*/

void LoadDisplay(ITEM *listItem, int ind) {

    printf("\n*** Liste des donnees après chargement:\n\n");
    int i = 0;
    for (i = 0; i < ind; i++) {
        printf("Nom    : %s \n", listItem->nom);
        printf("Prenom : %s \n", listItem->prenom);
        printf("Age    : %d \n\n", listItem->age);
        listItem = listItem->next;
    }
}

/*--------------------------------------------*/
/* Fonction de chargement de la liste chainée */
/*--------------------------------------------*/

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

/*--------------------------------------------*/
/* Fonction d'Affichage de la liste chainée   */
/*--------------------------------------------*/

int Afficher(ITEM *ListITEM, int showON) {

    ITEM *pe = ListITEM;

    int ind = 0;
    while (pe != NULL) {
        if (showON) {
            printf("Nom    : %s \n", pe->nom);
            printf("Prenom : %s \n", pe->prenom);
            printf("Age    : %d \n\n", pe->age);
        }
        pe = pe->next;
        ind++;
    }
    return ind;
}

/*--------------------------------------------*/
/*  Fonction de tri de la liste chainée       */
/*--------------------------------------------*/

void Choix(ITEM *ListITEM) {
    char cas[10];
    int ind = 0;
    while (TRUE) {

        printf("\033[H\033[2J");
        printf("\033[36m");
        printf("*------------------------------------------*\n");

        printf("*   Tri :\n\n");
        printf("- 1 ou A - numerique selon l'Age (croissant)\n");
        printf("- 2 ou D - numerique selon l'Age (Decroissant)\n");
        printf("- 3 ou N - alphabetique sur le Nom\n");
        printf("- 4 ou P - alphabetique sur le Prenom\n");
        printf("- 0 ou Q - quitter\n\n");
        printf("=> ");

        scanf("%s", cas);
        printf("\n");

        switch (cas[0]) {
            case '0':
            case 'q':
            case 'Q':

                exit(0);
            case '1':
            case 'A':
            case 'a':
                ind = Afficher(ListITEM, FALSE);
                qsort(ListITEM, ind, sizeof ListITEM->age, compareAge);
                printf("*------------------------------------------*\n");
                printf("Affichage après tri sur age (croissant)\n");
                printf("*------------------------------------------*\n");
                Afficher(ListITEM, TRUE);
                break;
            case '2':
            case 'D':
            case 'd':
                ind = Afficher(ListITEM, FALSE);
                qsort(ListITEM, ind, sizeof ListITEM->age, compareAgeDec);
                Afficher(ListITEM, TRUE);
                break;
            case '3':
            case 'N':
            case 'n':
                ind = Afficher(ListITEM, FALSE);
                qsort(ListITEM, ind, sizeof ListITEM->nom, compareName);
                Afficher(ListITEM, TRUE);
                break;
            case '4':
            case 'P':
            case 'p':
                ind = Afficher(ListITEM, FALSE);
                qsort(ListITEM, ind, sizeof ListITEM->prenom, compareFirstname);
                Afficher(ListITEM, TRUE);
                break;
            default:
                printf("! Choix incorrect [%s] : entrer une autre valeur\n\n", cas);
        }
    }
}




