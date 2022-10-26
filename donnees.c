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

/*--------------------------------------------*/
/* Fonction de lecture de la liste chainée    */
/*--------------------------------------------*/

void Lire() {
    int ind = 0;
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
        scanf("%1s", cas);
        switch (cas[0]) {
            case '0':
            case 't':
            case 'T':
                ind = readFile(filename, &ListITEM);
                if (ind == 0) {
                    printf("Fichier vide => %s\n", filename);
                } else {
                    Choix(ListITEM, ind);
                }
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
                if (readFile(filename, &ListITEM) != -1) {
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
                if (pe != NULL) {
                    free(pe);
                    pe = NULL;
                }
                if (LastCell != NULL) {
                    free(LastCell);
                    LastCell = NULL;
                }
                if (ListITEM != NULL) {
                    free(ListITEM);
                    ListITEM = NULL;
                }
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

/*--------------------------------------------*/
/* Fonction de lecture de la liste chainée   */
/*--------------------------------------------*/

int readFile(char *fname, ITEM **List) {
    FILE *fp;
    int ind = 0;

    ITEM *pe;
    ITEM *ListITEM = NULL;
    ITEM *LastCell = NULL;

    fp = fopen(fname, "r");
    if (fp == NULL) {
        printf("in readFile, file %s open error => File not found\n\n", fname);
        return -1;
    }

    char *buffer = (char *) malloc(BUFFER_SIZE);
    char nom[MAX_NAME_FR];
    char prenom[MAX_PRENOM_FR];
    int age;

    while ((fgetc(fp)) != EOF) {
        fgets(buffer, BUFFER_SIZE, fp);
        if (ferror(fp)) {
            fprintf(stderr, "Reading error with code %d\n", errno);
            return -1;
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
    free(buffer);
    buffer = NULL;
    printf("\n*** Lecture des donnees fin => %d\n\n", ind);
    if (ind > 0) {
        LoadDisplay(ListITEM, ind);
    }
    *List = ListITEM;
    return ind;
}

/*--------------------------------------------*/
/* Fonction d'Affichage de la liste chainée   */
/*--------------------------------------------*/

void LoadDisplay(ITEM *listItem, int ind) {

    printf("\n*** Liste des donnees après chargement:\n\n");

    int i;
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
    char nom[MAX_NAME_FR];
    char prenom[MAX_PRENOM_FR];
    int age;
    printf("*----------------------------*\n");
    printf("> nom    : ");
    scanf("%29s", nom);
    strcpy(pe->nom, nom);

    printf("> prenom : ");
    scanf("%19s", prenom);
    strcpy(pe->prenom, prenom);

    printf("> age    : ");
    scanf("%d", &age);
    pe->age = age;
    pe->next = NULL;
}

/*--------------------------------------------*/
/* Fonction d'Affichage de la liste chainée   */
/*--------------------------------------------*/

int Afficher(ITEM *ListITEM) {

    ITEM *pe;
    pe = ListITEM;
    int ind = 0;
    while (pe != NULL) {
        printf("Nom    : %s \n", pe->nom);
        printf("Prenom : %s \n", pe->prenom);
        printf("Age    : %d \n\n", pe->age);
        pe = pe->next;
        ind++;
    }
}

int Sort(ITEM *List, int ind, char cas) {

    int i, j, k, tempKey;
    char tempData[30];
    struct ITEM *current;
    struct ITEM *next;

    for (i = 0; i < ind - 1; i++, ind--) {
        current = List;
        next = List->next;

        for (j = 1; j < ind; j++) {

            if (current->nom > next->nom) {
                strcpy(tempData, current->nom);
                strcpy(current->nom, next->nom);
                strcpy(next->nom, tempData);

                strcpy(tempData, current->prenom);
                strcpy(current->prenom, next->prenom);
                strcpy(next->prenom, tempData);

                tempKey = current->age;
                current->age = next->age;
                next->age = tempKey;
            }
            current = current->next;
            next = next->next;
        }
    }
    return List;
}

/*--------------------------------------------*/
/*  Fonction de tri                           */
/*--------------------------------------------*/

int Trier(ITEM *List, int ind, char cas) {

    int i, j, k, tempKey;
    char tempData[30];
    struct ITEM *current;
    struct ITEM *next;

    switch (cas) {
        case '1':
            for (i = 0; i < ind; i++, ind--) {
                current = List;
                next = List->next;

                for (j = 1; j < ind; j++) {

                    if (current->age > next->age) {
                        strcpy(tempData, current->nom);
                        strcpy(current->nom, next->nom);
                        strcpy(next->nom, tempData);

                        strcpy(tempData, current->prenom);
                        strcpy(current->prenom, next->prenom);
                        strcpy(next->prenom, tempData);

                        tempKey = current->age;
                        current->age = next->age;
                        next->age = tempKey;
                    }
                    current = current->next;
                    next = next->next;
                }
            }
            break;
        case '2':
            for (i = 0; i < ind; i++, ind--) {
                current = List;
                next = List->next;

                for (j = 1; j < ind; j++) {

                    if (current->age < next->age) {
                        strcpy(tempData, current->nom);
                        strcpy(current->nom, next->nom);
                        strcpy(next->nom, tempData);

                        strcpy(tempData, current->prenom);
                        strcpy(current->prenom, next->prenom);
                        strcpy(next->prenom, tempData);

                        tempKey = current->age;
                        current->age = next->age;
                        next->age = tempKey;
                    }
                    current = current->next;
                    next = next->next;
                }
            }
            break;
        case '3':
            for (i = 0; i < ind; i++, ind--) {
                current = List;
                next = List->next;

                for (j = 1; j < ind; j++) {

                    if (current->nom > next->nom) {
                        strcpy(tempData, current->nom);
                        strcpy(current->nom, next->nom);
                        strcpy(next->nom, tempData);

                        strcpy(tempData, current->prenom);
                        strcpy(current->prenom, next->prenom);
                        strcpy(next->prenom, tempData);

                        tempKey = current->age;
                        current->age = next->age;
                        next->age = tempKey;
                    }
                    current = current->next;
                    next = next->next;
                }
            }
            break;
        case '4':
            for (i = 0; i < ind; i++, ind--) {
                current = List;
                next = List->next;

                for (j = 1; j < ind; j++) {

                    if (current->prenom > next->prenom) {
                        strcpy(tempData, current->nom);
                        strcpy(current->nom, next->nom);
                        strcpy(next->nom, tempData);

                        strcpy(tempData, current->prenom);
                        strcpy(current->prenom, next->prenom);
                        strcpy(next->prenom, tempData);

                        tempKey = current->age;
                        current->age = next->age;
                        next->age = tempKey;
                    }
                    current = current->next;
                    next = next->next;
                }
            }
            break;
    }
    return List;
}

/*--------------------------------------------*/
/*  Fonction de tri de la liste chainée       */
/*--------------------------------------------*/

void Choix(ITEM *listItem, int ind) {
    char cas[10];
    int ListReturn;
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
                printf("*------------------------------------------*\n");
                printf("Affichage après tri sur age (croissant)\n");
                printf("*------------------------------------------*\n");
                ListReturn = Trier(listItem, ind, cas[0]);
                Afficher(listItem);
                break;
            case '2':
            case 'D':
            case 'd':
                printf("*------------------------------------------*\n");
                printf("Affichage après tri sur age (décroissant)\n");
                printf("*------------------------------------------*\n");
                ListReturn = Trier(listItem, ind, cas[0]);
                Afficher(listItem);
                break;
            case '3':
            case 'N':
            case 'n':
                printf("*------------------------------------------*\n");
                printf("Affichage après tri sur nom (croissant)\n");
                printf("*------------------------------------------*\n");
                ListReturn = Trier(listItem, ind, cas[0]);
                Afficher(listItem);
                break;
            case '4':
            case 'P':
            case 'p':
                printf("*------------------------------------------*\n");
                printf("Affichage après tri sur prénom (croissant)\n");
                printf("*------------------------------------------*\n");
                ListReturn = Trier(listItem, ind, cas[0]);
                Afficher(listItem);
                break;
            default:
                printf("! Choix incorrect [%s] : entrer une autre valeur\n\n", cas);
        }
    }
}




