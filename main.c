#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "menace.h"


int main()
{

    srand(time(NULL));
  boite * b =choix_graphe();                                                    //b contient la premiere boite du graphe
  int32_t choixjoueur = promptGamemode();                                       //premier choix de mode de jeu du joueur
  uint8_t symbole_courant,tour,i;
  int32_t compteur,test;
  int32_t terrain_suivant;
  boite * boite_courant;


  while(choixjoueur != -1)                                                      //tant que le joueur n'a pas decider de quitter le programme
  {
    if(choixjoueur==0)                                                          //si le joueur veut jouer contre l'IA
    {
        boite_courant=b;                                                        //on part du debut du graphe
        set_passage(boite_courant);                                             //on indique qu'on passe par le debut du graphe
        //debut d'une partie
        if(promptPremierJoueur()==0)                                            //si le joueur commence
            {
                tour=1;
                test=0;

            }
        else                                                                    //si l'IA commence
            {
                tour=-1;
                test=1;
            }
        symbole_courant=ROND;                                                   //les Ronds commencent

        while(partieFinie(boite_courant->terrain)==0 && nb_case_libre(boite_courant->terrain)>0)//tant que la partie n'est pas finie ou tant qu'il reste des cases e remplir dans le terrain
        {
            if(tour==1)                                                         //si c'est le tour du joueur
            {
                terrain_suivant=set_case(boite_courant->terrain,promptCoup(boite_courant->terrain),symbole_courant);//on demande au joueur ou il veut jouer
                 tour=-1;       //on passe au tour de l'IA
            }
            else
            {
                printf("Au tour de l'IA:\n");
                terrain_suivant = set_case(boite_courant->terrain,ProchainCoup(boite_courant->bille),symbole_courant);//on deduit le prochain coup de l'IA
                tour=1;     //on passe au tour du joueur
            }
            for (i=0; i < nb_case_libre(terrain_suivant);i++)                   //des que le coup est joue, on regarde si le terrain obtenu apres coup est une symetrie d'un des fils de la boete oe on se situe actuellement
            {
                if(verify_sym(terrain_suivant,boite_courant->suivants[i]->terrain))
                  {
                    boite_courant=boite_courant->suivants[i];                   //des que la symetrie est trouvee on descend dans le fils correspondant au terrain obtenu
                    set_passage(boite_courant);                                 //on indique qu'on est passe par ce noeud du graphe
                  }
            }
            symbole_courant = changerSymbole(symbole_courant);                                    //croix devient rond,rond devient croix
            afficheTerrain(boite_courant->terrain);

        }
        if(((partieFinie(boite_courant->terrain)==ROND) && (test== 0)) | ((partieFinie(boite_courant->terrain)==CROIX) &&( test==1)))
        {
            printf("Le joueur gagne!\n");                                     //si les ronds ont gagne et que le joueur a pris les ronds, alors le joueur gagne,idem avec les croix
        }
        else if (((partieFinie(boite_courant->terrain)==ROND) && (test== 1)) | ((partieFinie(boite_courant->terrain)==CROIX) &&( test== 0)) )
        {
          printf("L'IA a gagne!");                                              //inversement,l'IA gagne
        }
        else
            printf("Egalite!");                                                 //si il n'y avait plus de cases libres et personne n'a gagne, egalite

        if(partieFinie(boite_courant->terrain)==ROND)                           //si les ronds ont gagne alors l'IA va modifier ses billes en sachant qu les Ronds ont gagne
            modifier_billes(b,ROND);
        else if(partieFinie(boite_courant->terrain)==CROIX)                     //idem avec les croix
            modifier_billes(b,CROIX);
        else                                                                    //idem si egalite
            modifier_billes(b,VIDE);
    }

    else                                                                        //si le joueur veut faire jouer l'IA contre elle-meme
    {
      for(compteur=0;compteur<choixjoueur;compteur++)                           //on repete N parties, N donne par le joueur
      {
        boite_courant=b;                                                        //on part (ou repart) du haut du graphe
        set_passage(boite_courant);                                             //on indique qu'on passe par le haut du graphe
        symbole_courant=ROND;                                                   //les ronds commencent
        //---debut d'une partie IA contre IA
        while(partieFinie(boite_courant->terrain)==0 && nb_case_libre(boite_courant->terrain)>0 )       //tant que la partie n'est paas finie ou qu'il reste des cases e combler
        {
          terrain_suivant = set_case(boite_courant->terrain,ProchainCoup(boite_courant->bille),symbole_courant);//l'IA joue
          for (i=0; i < nb_case_libre(terrain_suivant);i++)                     //avec le terrain obtenu on cherhce le fils correspondant
          {
            if(verify_sym(terrain_suivant,boite_courant->suivants[i]->terrain))
            {
              boite_courant=boite_courant->suivants[i];                         //on fois trouve on descend dans le fils correspondant
              set_passage(boite_courant);
            }                                                                   //on indique qu'on passe par ce fils
          }
          changerSymbole(symbole_courant);                                      // on inverse le symbole
        }
        if(partieFinie(boite_courant->terrain)==ROND)                           // en fonction de l'issue de la partie on modifie les billes de l'IA
            modifier_billes(b,ROND);
        else if(partieFinie(boite_courant->terrain)==CROIX)
            modifier_billes(b,CROIX);
        else
            modifier_billes(b,VIDE);
      }
      printf("Apprentissage termine.\n");
    }
    choixjoueur = promptGamemode();                                              // on redemande le choix du mode de jeu au joueur
  }
  //---si il a decide de quitter, on sauvegarde le graphe
  boite** adresseSave = mymalloc(sizeof(boite*)*850);
  FILE* file = fopen("graphe.xox","w");
  save_graphe(b,adresseSave,file);
  fclose(file);
  myfree(adresseSave);
    //puis on libere le graphe
  boite** adresseFree = mymalloc(sizeof(boite*)*850);
  free_graphe(b,adresseFree);
  myfree(adresseFree);
}
