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

typedef struct {
    char nom[30],
            prenom[20];
    int age;
    struct ITEM *next;
} ITEM;

/* ===================================================================== */

#endif //tp09TRI_TRI_H
