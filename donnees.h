//
// Created by root on 29/09/22.
//

#ifndef tp09TRI_DONNEES_H
#define tp09TRI_DONNEES_H
/* ===================================================================== *
 *
 * header donnees.h
 *
 * ===================================================================== */

#include "tri.h"

/* declaration des fonctions definies dans donnees.c */

extern void Lire();

extern int Afficher(ITEM *listItem);

extern void setParametersI(ITEM *pe);

extern void Choix(ITEM *listItem, int ind);

extern int writeFile(char *fname, ITEM *listItem);

extern int readFile(char *fname, ITEM **);

extern void LoadDisplay(ITEM *listItem, int ind);

extern int effacer(const char *filename);

#endif //tp09TRI_DONNEES_H
