#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include "hashtable.h"

/*Definition des Structures*/
typedef struct _maillon
{
    struct box_t* data;
    struct _maillon *next;
}maillon;

typedef struct liste_t
{
  uint64_t taille;
  maillon *tete;
  maillon *queue;
} liste ;

/*Declaration des fonctions*/
liste* new_liste();
maillon* new_maillon(struct box_t d);
void add_tete(liste *l, struct box_t d);
struct box_t* rem_tete(liste *l);
void afficher_liste(liste *l);
void add_croissant(liste *l, struct box_t d);
int in_list(liste *l, struct box_t d);
maillon* get_maillon(liste *l, int32_t terrain);


#endif
