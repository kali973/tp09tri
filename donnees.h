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

extern void Lire(int argc, char **argv);

extern int Afficher(ITEM *listItem);

extern void setParametersI(ITEM *pe);

extern void Choix(ITEM *listItem);

#endif //tp09TRI_DONNEES_H
