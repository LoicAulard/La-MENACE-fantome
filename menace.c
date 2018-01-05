#include <stdio.h>
#include <stdlib.h>
#include "menace.h"

int main(int argc, char const *argv[]) {

  return 0;
}

int set_case(int terrain, int cases, int value) // cases diot etre le numéro de la case; value doit etre CROIX ROND ou VIDE
{
    return terrain|(value<<((case-1)*2));
}

int get_case(int terrain, int cases)// cases diot etre une des constant le numéro de la case;
{
  return (terrain&(3<<((case-1)*2)))/(cases/3);
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
