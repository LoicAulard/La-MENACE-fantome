#include <stdio.h>
#include <stdlib.h>
#include "menace.h"

int main(int argc, char const *argv[]) {

  return 0;
}

int set_case(int terrain, int cases, int value) // cases diot etre une des constant CASEn; value doit etre CROIX ROND ou VIDE
{
  switch (cases)
  {
    case CASE1: return terrain|value;
    break;

    case CASE2: return terrain|(value<<2);
    break;

    case CASE3: return terrain|(value<<4);
    break;

    case CASE4: return terrain|(value<<6);
    break;

    case CASE5: return terrain|(value<<8);
    break;

    case CASE6: return terrain|(value<<10);
    break;

    case CASE7: return terrain|(value<<12);
    break;

    case CASE8: return terrain|(value<<14);
    break;

    case CASE9: return terrain|(value<<16);
    break;

    default: fprintf(stderr,"Cette case n'existe pas.");
    exit(-1);
  }
}

int get_case(int terrain, int cases)// cases diot etre une des constant CASEn;
{
  return (terrain&cases)/(cases/3);
}

int nb_case_libre(int terrain)
{
  int cpt = 0, i;
  for(i=0; i<SIZE; i++)
  {
    cpt = cpt + ((terrain&(3<<i)) == 0);
  }

  return cpt;
}
