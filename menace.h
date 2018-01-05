#ifndef MEN_H
#define MEN_H
#include <stdio.h>
#include <stdlib.h>

#define SIZE 9

#define LINE1 63
#define LINE2 4032
#define LINE3 258048

#define COLUMN1 12483
#define COLUMN2 49932
#define COLUMN3 199728

#define CASE1 3
#define CASE2 12
#define CASE3 48
#define CASE4 192
#define CASE5 768
#define CASE6 3072
#define CASE7 12288
#define CASE8 49152
#define CASE9 196608

#define CROIX 2
#define ROND  1
#define VIDE  0

typedef struct _boite
{
  int terrain;
  int *possibilite;
  struct _boite **suivants;
  struct _boite *pere;
} boite;



#endif
