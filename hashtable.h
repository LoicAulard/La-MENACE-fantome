#ifndef HASH_H
#define HASH_H

#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "menace.h"
#include "mytab.h"

typedef struct box_t
{
  int32_t terrain;
  int64_t bille;
  int   passage; //Contain the case that has been played (1-9) else 0
  struct _maillon** symetrie;
}box;

typedef struct hashtable_t
{
  struct liste_t* table[SIZE+1];
}hashtable;

void fill_hashtable(hashtable* h);
void init_hashtable(hashtable* h);
struct _maillon** merge_maillon_array(struct _maillon** array1, struct _maillon** array2);
void fill_symetrie_array(hashtable* h);
void change_score(hashtable* h);


box new_box(int32_t terrain);
void print_box(box b);

void print_hashtable(hashtable h);
void save_hashtable(hashtable *h, char *filename );
void load_hashtable(hashtable *h,char *filename);





#endif
