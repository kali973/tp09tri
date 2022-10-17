//
// Created by root on 29/09/22.
//

#ifndef tp09TRI_TRI_H
#define tp09TRI_TRI_H
/* ===================================================================== *
 *
 * header tri.h
 *
 * ===================================================================== */

#define FALSE 0
#define TRUE 1
#define MAX_ITEM 100
#define  MAX_NAME_FR 30
#define  MAX_PRENOM_FR 20

typedef struct {
    char nom[MAX_NAME_FR];
    char prenom[MAX_PRENOM_FR];
    int age;
    struct ITEM *next;
} ITEM;

/* ===================================================================== */

#endif //tp09TRI_TRI_H
