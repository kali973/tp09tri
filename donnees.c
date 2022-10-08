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

#define BUFFER_SIZE 200

void Choix(ITEM *listItem);

void writeFile(char *fname, ITEM *listItem);

int readFile(char *fname);

void LoadDisplay(ITEM *listItem, int ind);

int compareAge(const void *a, const void *b) {
    return ((ITEM *) b)->age >> ((ITEM *) a)->age;
}

int compareAgeDec(const void *a, const void *b) {
    return ((ITEM *) a)->age < ((ITEM *) b)->age;
}

int compareName(const void *a, const void *b) {
    return ((ITEM *) a)->nom > ((ITEM *) b)->nom;
}

int compareFirstname(const void *a, const void *b) {
    return ((ITEM *) a)->prenom > ((ITEM *) b)->prenom;
}

void Lire(int argc, char **argv) {
    char *pe;
    char cas[10];
    ITEM *ListITEM = NULL;
    ITEM *LastCell = NULL;

    const char *nameFile = "/tri.txt";

    char buffer[BUFFER_SIZE];
    if ( getcwd( buffer, BUFFER_SIZE ) == NULL ) {
        fprintf( stderr, "Cannot get current working directory path\n" );
        if ( errno == ERANGE ) {
            fprintf( stderr, "Buffer size is too small.\n" );
        }
        exit( EXIT_FAILURE );
    }

    printf( "Current working directory: %s\n", buffer );

    const char *filename = strcat(buffer, nameFile);

    while (TRUE) {
        printf("*----------------------------*\n");
        printf("- 0 ou T - Tri\n");
        printf("- 1 ou S - Saisie des données\n");
        printf("- 2 ou L - Lecture des données\n");
        printf("- 3 ou E - Enregistrer des données\n");
        printf("- 4 ou Q - Quitter \n");

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
                break;
            case '2':
            case 'l':
            case 'L':
                if (readFile(filename) != -1) {
                    printf("Chargement terminé\n\n");
                }
                break;
            case '3':
            case 'e':
            case 'E':
                writeFile(filename, ListITEM);
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

void writeFile(char *fname, ITEM *ListITEM) {
    FILE *fp;
    int i = 0;

    fp = fopen(fname, "w+");
    if (fp == NULL) {
        printf("in readFile, file %s open error\n", fname);
        return;
    }
    ITEM *pe = ListITEM;

    while (pe != NULL) {
        fprintf(fp, "%30s", pe->nom);
        fprintf(fp, "%20s", pe->prenom);
        fprintf(fp, "%3d", pe->age);
        pe = pe->next;
        i++;
    }

    printf("\n*** Nombre d'enregistrement => %d\n\n", i);
    fclose(fp);
}

int readFile(char *fname) {
    FILE *fp;
    int ind = 0;
    int ret;
    ITEM *pe;
    ITEM *ListITEM = NULL;
    ITEM *LastCell = NULL;

    fp = fopen(fname, "r");
    if (fp == NULL) {
        printf("in readFile, file %s open error => File not found\n\n", fname);
        return -1;
    }

    while (fgetc(fp) != EOF){
        pe = (ITEM *) malloc(sizeof(ITEM));
        if (pe == NULL) {
            printf(" no memory \n");
            exit(1);
        }
        ret = fscanf(fp, "%30s %20s %3d", &pe[ind].nom, &pe[ind].prenom, &pe[ind].age);

        if (ret == 3) {
            strcpy(pe->nom, &pe[ind].nom);
            strcpy(pe->prenom, &pe[ind].prenom);
            int *v = &pe[ind].age;
            pe->age = *v;
            ind++;

            if (LastCell == NULL) {
                ListITEM = pe;
                LastCell = pe;
            } else {
                LastCell->next = pe;
                LastCell = pe;
            }
        }
    }

    fclose(fp);
    printf("\n*** Lecture des donnees fin => %d\n\n", ind);
    if (ind > 0)  {
        LoadDisplay(ListITEM,ind);
    }
    return ListITEM;
}

void LoadDisplay(ITEM *listItem, int ind) {

    printf("\n*** Liste des donnees après chargement:\n\n");
    int i = 0;
    for (i=0; i< ind; i++){
        printf("Nom    : %s \n", listItem->nom);
        printf("Prenom : %s \n", listItem->prenom);
        printf("Age    : %d \n\n", listItem->age);
        listItem = listItem->next;
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

void Afficher(ITEM *ListITEM) {

    ITEM *pe = ListITEM;
    printf("\n*** Liste des donnees :\n\n");
    int ind = 0;
    while (pe->next != NULL ) {
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
                qsort(ListITEM, sizeof *ListITEM / sizeof ListITEM, sizeof *ListITEM, compareAge);
                Afficher(ListITEM);
                break;
            case '2':
            case 'D':
            case 'd':
                qsort(ListITEM, sizeof *ListITEM / sizeof ListITEM, sizeof *ListITEM, compareAgeDec);
                Afficher(ListITEM);
                break;
            case '3':
            case 'N':
            case 'n':
                qsort(ListITEM, sizeof *ListITEM / sizeof ListITEM, sizeof *ListITEM, compareName);
                Afficher(ListITEM);
                break;
            case '4':
            case 'P':
            case 'p':
                qsort(ListITEM, sizeof *ListITEM / sizeof ListITEM, sizeof *ListITEM, compareFirstname);
                Afficher(ListITEM);
                break;
            default:
                printf("! Choix incorrect [%s] : entrer une autre valeur\n\n", cas);
        }
    }
}




