#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "menace.h"
#include "tree.h"
#include "hashtable.h"

void jouer_partie(hashtable *h, int mode)
{
  char c;
  int result = 0 , i = 0, coup = 0;
  maillon *m;
  while (i<=SIZE && partieFinie(_currentTerrain) == -1)
  {
    if(mode == IA_VS_IA)
    {
      m = get_maillon(h->table[i], _currentTerrain);
      coup = ProchainCoup(m->data->bille);
      set_case(_currentTerrain, coup, _currentPlayer);
      m->data->passage = coup;
      change_player();
    }
    else if(mode == PLAYER_VS_IA)
    {
      if(_playerIA == (i%2)+1)
      {
        printf("IA--Recuperation du maillon\n");
        m = get_maillon(h->table[i], _currentTerrain);
        if(m==NULL)
        {
          printf("ERROR!");
          exit(-1);
        }
        printf("IA--Determination du prochain coup : ");
        coup = ProchainCoup(m->data->bille);
        printf("%d <- %d\n", coup,get_bille(m->data->bille, coup));
        printf("IA--Mise a jour du terrain\n");
        _currentTerrain = set_case(_currentTerrain, coup, _currentPlayer);
        printf("IA--Enregistrement du passsage\n");
        m->data->passage = coup;
        printf("IA--Changement de joueur\n");
        change_player();
      }
      else
      {
        do
        {
          printf("Sur quelle case souhaitez vous jouer ? (entre 1 et 9)\n");
          scanf(" %d",&coup);
        }
        while(get_case(_currentTerrain,coup) != VIDE);
        printf("J--Recuperation du maillon\n");
        m = get_maillon(h->table[i], _currentTerrain);
        printf("J--Mise a jour du terrain\n");
        _currentTerrain = set_case(_currentTerrain, coup, _currentPlayer);
        printf("J--Enregistrement du passsage\n");
        m->data->passage = coup;
        printf("J--Changement de joueur\n");
        change_player();
      }
      afficheTerrain(_currentTerrain);
    }
    i++;
  }
  change_score(h);
  _currentTerrain = 0;

}


int main(int argc, char const *argv[])
{
//   _currentPlayer = CROIX;
//   _currentTerrain = 0;
//   int c;
//   char name[50];
//   hashtable h;
//
// /*Hahstable*/
//   init_hashtable(&h);
//
//
// /*************/
//
//   printf("Toute réponses ne respectant pas les conditions entraine un comportement indeterminé.\n");
//   printf("Voulez-vous chargé une IA prééxistante ? (o/n)\n");
//   c = getchar();
//   if(c == 'o')
//   {
//     printf("Entrez le nom du fichier (50 caracteres max)\n");
//     scanf(" %s", name);
//     load_hashtable(&h, name);
//   }
//   else
//   {
//     printf("Création d'une nouvelle IA\n");
//     printf("--PREMIER MAILLON--\n");
//     h.table[0]->tete = new_maillon(new_box(0));
//     printf("--FILLING HASHTABLE--\n");
//     fill_hashtable(&h);
//     printf("--SYMETRIE--\n");
//     fill_symetrie_array(&h);
//     printf("IA crée\n");
//   }
//   printf("Voulez-vous :\n1:Jouer contre l'IA\n2:Faire jouer l'IA contre elle même\n");
//   scanf(" %d", &c);
//   printf("%d \\ %d\n", c, c==1);
//   if(c == 1)
//   {
//     printf("Voulez vous commencer ? (1:oui 2:non)\n");
//     scanf(" %d", &_playerIA);
//     _playerIA = (_playerIA%2)+1;
//     jouer_partie(&h, PLAYER_VS_IA);
//   }
//   else if( c == 2)
//   {
//     int nbrPartie = 0, i = 0;
//     printf("Combin de partie souhaitez vous que l'IA effectue ?\n");
//     scanf("%d ", &nbrPartie);
//     for(i=0; i<nbrPartie;i++)
//     {
//       printf("Partie %d\n",i);
//       jouer_partie(&h, IA_VS_IA);
//     }
//   }
//   else
//   {
//     printf("Option inexistante : %c\n",c);
//   }
// //--------------------------------------------------------------------------------
//   init_hashtable(&h);
//
//   printf("--SAVE--\n");
//   save_hashtable(&h, "toto.ia");
//
//   printf("--LOAD--\n");
//   hashtable h1;
//   init_hashtable(&h1);
//   load_hashtable(&h1, "toto.ia");
//
//
//   //print_hashtable(h);
//
//   //print_hashtable(h);

  uint64_t a = 0x7E000000000000;
  printf("%d\n", get_bille(a, 3));
  return 0;
}
