# La-MENACE-fantome
Intelligence artificielle de morpion


prototypes de fonctions:

CASES:
int setcase(int terrain, int int cases, int value); // cases diot etre une des constant CASEn; value doit etre CROIX ROND ou VIDE

int get_case(int terrain, int cases);// cases diot etre une des constant CASEn;

nb_case_libre(int terrain);


BOITES:

typedef struct _boite
{
  int terrain;
  int *possibilite;
  struct _boite **suivants;
  struct _boite *pere;
} boite;

boite CréérBoite(); // suivants,pere et possibilité à NULL, terrain à 0
void DétruireBoite();




