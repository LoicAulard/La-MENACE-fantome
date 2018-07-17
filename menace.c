#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "menace.h"


//---------------------------manipulation de cases---------------------------------
int set_case(int terrain, int cases, int value) // cases diot etre le numéro de la case; value doit etre CROIX ROND ou VIDE
{
    return terrain|(value<<((cases-1)*2));
}

int32_t get_case(int32_t terrain, int32_t cases)// cases diot etre une des constant le numéro de la case;
{
  return (terrain&CreerMasque(cases,MASQUE_CASE))/(CreerMasque(cases,MASQUE_CASE)/3);
}

int nb_case_libre(int terrain)
{
  int cpt = 0, i;
  for(i=0; i<SIZE; i++)
  {
    cpt = cpt + (get_case(terrain, i+1) == VIDE);
  }

  return cpt;
}

int64_t CreerMasque(int Case, int typeMasque)		//case de 1 à 9 et non de 0 à 8
{
	assert(Case!=0);
  int64_t res;
	if(typeMasque==MASQUE_CASE)
  {
    res = 3;
    res = res <<(Case-1)*2;
    printf("MASQUE_CASE : %x\n", res);
    return res;
  }
	else if(typeMasque==MASQUE_BILLE)
  {
    res = 127;
    res = res <<(Case-1)*2;
    printf("MASQUE_BILLE : %x\n", res);
    return res;
  }
  else
        return 0;
}

//--------------------------symétries et rotations----------------------------------------------------
int symetrie_v(int32_t t1, int32_t t2) //on regarde si t1 est une syùétrie verticale de t2
{
	return 	(get_case(t1,1)==get_case(t2,3))&&(get_case(t1,2)==get_case(t2,2))&&(get_case(t1,3)==get_case(t2,1))&&
		(get_case(t1,4)==get_case(t2,6))&&(get_case(t1,5)==get_case(t2,5))&&(get_case(t1,6)==get_case(t2,4))&&
		(get_case(t1,7)==get_case(t2,9))&&(get_case(t1,8)==get_case(t2,8))&&(get_case(t1,9)==get_case(t2,7));
}


int symetrie_h(int32_t t1, int32_t t2) //on regarde si t1 est une syùétrie horizontale de t2
{
	return 	(get_case(t1,1)==get_case(t2,7))&&(get_case(t1,4)==get_case(t2,4))&&(get_case(t1,7)==get_case(t2,1))&&
		(get_case(t1,2)==get_case(t2,8))&&(get_case(t1,5)==get_case(t2,5))&&(get_case(t1,8)==get_case(t2,2))&&
		(get_case(t1,3)==get_case(t2,9))&&(get_case(t1,6)==get_case(t2,6))&&(get_case(t1,9)==get_case(t2,3));
}


int symetrie_d1(int32_t t1, int32_t t2) //on regarde si t1 est une syùétrie diagonale(/) de t2
{
	return 	(get_case(t1,1)==get_case(t2,9))&&(get_case(t1,2)==get_case(t2,6))&&(get_case(t1,3)==get_case(t2,3))&&
		(get_case(t1,4)==get_case(t2,8))&&(get_case(t1,5)==get_case(t2,5))&&(get_case(t1,6)==get_case(t2,2))&&
		(get_case(t1,7)==get_case(t2,7))&&(get_case(t1,8)==get_case(t2,4))&&(get_case(t1,9)==get_case(t2,1));
}


int symetrie_d2(int32_t t1, int32_t t2) //on regarde si t1 est une syùétrie diagonale(\) de t2
{
	return 	(get_case(t1,1)==get_case(t2,1))&&(get_case(t1,2)==get_case(t2,4))&&(get_case(t1,3)==get_case(t2,7))&&
		(get_case(t1,4)==get_case(t2,2))&&(get_case(t1,5)==get_case(t2,5))&&(get_case(t1,6)==get_case(t2,8))&&
		(get_case(t1,7)==get_case(t2,3))&&(get_case(t1,8)==get_case(t2,6))&&(get_case(t1,9)==get_case(t2,9));
}

int rotationD90(int32_t t1,int32_t t2)//on regarde si en tournant t1 de 90 degrés vers la droite on obtient t2
{
	return (get_case(t1,1)==get_case(t2,3)) && (get_case(t1,2)==get_case(t2,6)) && (get_case(t1,3)==get_case(t2,9))
  && (get_case(t1,4) == get_case(t2,2)) && (get_case(t1,5)== get_case(t2,5)) && (get_case(t1,6) == get_case(t2,8)) && (get_case(t1,7)== get_case(t2,1))
  && (get_case(t1,8)==get_case(t2,4)) && (get_case(t1,9) == get_case(t2,7)) ;
}
int rotation180(int32_t t1,int32_t t2)//on regarde si en tournant t1 de 90 degrés vers la droite on obtient t2
{
	return (get_case(t1,1)==get_case(t2,9)) && (get_case(t1,2)==get_case(t2,8)) && (get_case(t1,3)==get_case(t2,7))
  && (get_case(t1,4) == get_case(t2,6)) &&(get_case(t1,5)== get_case(t2,5))&& (get_case(t1,6) == get_case(t2,4)) && (get_case(t1,7)== get_case(t2,3))
  && (get_case(t1,8)==get_case(t2,2)) && (get_case(t1,9) == get_case(t2,1)) ;
}

int rotationG90(int32_t t1,int32_t t2)//on regarde si en tournant t1 de 180 degrés vers la gauche on obtient t2
{
	return (get_case(t1,1)==get_case(t2,7)) && (get_case(t1,2)==get_case(t2,4)) && (get_case(t1,3)==get_case(t2,1))
  && (get_case(t1,4) == get_case(t2,8)) &&(get_case(t1,5)== get_case(t2,5))&& (get_case(t1,6) == get_case(t2,2)) && (get_case(t1,7)== get_case(t2,9))
  && (get_case(t1,8)==get_case(t2,6)) && (get_case(t1,9) == get_case(t2,3)) ;
}

int isSymetric(int32_t t1, int32_t t2)
{
  return symetrie_v(t1, t2) || symetrie_h(t1, t2) || symetrie_d1(t1, t2)
      || symetrie_d2(t1, t2) || rotation180(t1,t2) || rotationD90(t1, t2)
      || rotationG90(t1, t2) || t1 == t2;
}

//----------------------------------------------manipulation de graphe--------------------------------------

void creer_graphe(boite* b, int32_t* figure, boite** addresse)
{
  if(b!=NULL && nb_case_libre(b->terrain)!=0)
  {
    int32_t i=0, j=0, n=0, caseLibre = nb_case_libre(b->terrain), symbole = VIDE;
    boite* tmp = NULL;
    b->suivants = mymalloc(sizeof(boite*)*caseLibre);
    for(i=0; i<SIZE;i++)
  	{
  		if(get_case(b->terrain,i+1)==VIDE)
  		{

        if(caseLibre%2 == 1)
        {
          symbole = ROND;
        }
        else
        {
          symbole = CROIX;
        }

        tmp = creer_noeud(set_case(b->terrain, i+1, symbole));
        if((j=verify_tab(tmp->terrain,figure))<=0)
        {
          b->suivants[n] = tmp;
          figure[-j] = tmp->terrain;
          addresse[-j] = b->suivants[n];
          creer_graphe(b->suivants[n], figure, addresse);
        }
        else
        {
          b->suivants[n] = addresse[j];
        }

        n++;

  		}
  	}
  }
}

int32_t verify_tab(int32_t terrain, int32_t* tab)
{
	int32_t i = 0;
	for(i=0; tab[i]!=0; i++)
	{
		if (verify_sym(terrain,tab[i])) return i;
	}
	return -i;
}
int32_t verify_sym(int32_t terrain, int32_t t2)
{
    if (symetrie_v(terrain, t2) || symetrie_h(terrain, t2) || symetrie_d1(terrain, t2)
        || symetrie_d2(terrain, t2) || rotation180(terrain,t2) || rotationD90(terrain, t2)
        || rotationG90(terrain, t2) || terrain == t2) return 1;
    else
        return 0;
}

boite* creer_noeud(int32_t terrain)
{
	boite* b= mymalloc(sizeof(boite));
	b->terrain = terrain;
	b->bille = 1;
  b->bille = (b->bille<<63);
  (b->bille)--;
	b->suivants = NULL;
	return b;

}

void save_graphe(boite* b, boite** adresse, FILE* save)
{
  int32_t n=0;
  if(b!=NULL)
  {
    int32_t i = 0;
    if(checkfree(b, adresse))
    {
      fwrite(&(b->bille), sizeof(int64_t), 1, save);
      while(adresse[n]!=NULL)                                                   //on trouve la premiere place libre dans adresse
        n++;
      adresse[n]=b;
    }

    for(i = 0; i<nb_case_libre(b->terrain); i++)
    {
      save_graphe(b->suivants[i],adresse,save);
    }
  }
}

void charger_graphe(boite* b, boite** adresse, FILE* load)
{
  int32_t n=0;
  if(b!=NULL)
  {
    int32_t i = 0;
    printf("%p   %p   %ld   %p\n",b,&(b->bille),sizeof(int64_t),load);
    if(checkfree(b, adresse) && fread(&(b->bille), sizeof(int64_t), 1, load)==1)
    {
      //fread(&(b->bille), sizeof(int64_t), 1, load);
      while(adresse[n]!=NULL)                                                   //on trouve la premiere place libre dans adresse
        n++;
      adresse[n]=b;
    }

    for(i = 0; i<nb_case_libre(b->terrain); i++)
    {
      charger_graphe(b->suivants[i],adresse,load);
    }
  }
}

void free_graphe(boite* b, boite** adresse)
{
  if(b!=NULL && checkfree(b,adresse))                                           //On verifie que b ne pointe pas sur NULL et qu'il na pas déjà été libéré
  {
    uint32_t i = 0, caseLibre = nb_case_libre(b->terrain), n=0;                 //declaration des variable
    boite* adr[SIZE] = {NULL};                                                  //adr est une copie de b->suivants.
    for(i=0; i<caseLibre; i++)                                                  //on effectue la copie
    {
      adr[i]=b->suivants[i];
    }
    while(adresse[n]!=NULL)                                                     //on trouve la premiere place libre dans adresse
      n++;
    adresse[n]=b;                                                               //on stocke b dans addresse
    if(b->suivants!=NULL)
      myfree(b->suivants);
    myfree(b);                                                                  //on libere b
    for(i=0; i<caseLibre; i++)
    {
      free_graphe(adr[i],adresse);                                              //on poursuit sur les fils
    }
  }
}

int checkfree(boite* b, boite** adresse)
{
  uint32_t i = 0;
  for(i=0; i<mytabsize(adresse, sizeof(boite*)); i++)
  {
    if(adresse[i]==b) return 0;
  }
  return 1;
}


//-------------------------------------manipulation de billes------------------------------------------------
uint64_t get_bille(uint64_t billes, int Case)
{
  return (billes&CreerMasque(Case,MASQUE_BILLE))/(CreerMasque(Case,MASQUE_BILLE)/127);
}
uint64_t set_bille(uint64_t billes, int Case, uint64_t value) //renvoie l'entier billes avec la bille souhaitée modifiée
{
    return (billes&(0xFFFFFFFFFFFFFFFF - (0x7F<<(Case-1)*7)))|(value<<((Case-1)*7));
}

void set_passage(boite * b)
{
    int64_t i =1;
    i= i<<63;
    b->bille = b->bille + i;
}
uint64_t sommeBilles(uint64_t billes)
{
	uint32_t i;
	uint32_t somme=get_bille(billes,1);
	for (i=1;i<9;i++)
	{
		somme+= get_bille(billes,i+1);
	}
	return somme;
}

//-------------------manipulation partie-------------------------------------
int ProchainCoup(uint64_t billes)	//renvoie la case (1 à 9) où l'IA devra jouer le prochain coup
{
	uint32_t nombre_aleatoire = rand()%sommeBilles(billes);
	uint32_t sommes_tmp=0;
	int i;
	for(i=0;i<9;i++)
	{
		if ((nombre_aleatoire >= sommes_tmp) && (nombre_aleatoire < sommes_tmp + get_bille(billes,i+1)))
			return i+1;
		else
			sommes_tmp+=get_bille(billes,i+1);
	}
	return 0;
}


int partieFinie(uint32_t terrain)
{
    //horizontal
    if((terrain & 0x3F) == 0x15) return ROND;
    if((terrain & 0x3F) == 0x2A) return CROIX;

    if((terrain & 0xFC0) == 0x540) return ROND;
    if((terrain & 0xFC0) == 0xA80) return CROIX;

    if((terrain & 0x3F000) == 0x15000) return ROND;
    if((terrain & 0x3F000) == 0x2A000) return CROIX;
    //vertical
    if((terrain & 0x30C3) == 0x1041) return ROND;
    if((terrain & 0x30C3) == 0x2082) return CROIX;

    if((terrain & 0xC30C) == 0x4104) return ROND;
    if((terrain & 0xC30C) == 0x8208) return CROIX;

    if((terrain & 0x30C30) == 0x10410) return ROND;
    if((terrain & 0x30C30) == 0x20820) return CROIX;
    //diagonal
    if((terrain & 0x30303) == 0x10101) return ROND;
    if((terrain & 0x30303) == 0x20202) return CROIX;

    if((terrain & 0x3330) == 0x1110) return ROND;
    if((terrain & 0x3330) == 0x2220) return CROIX;

    if (nb_case_libre(terrain) == 0) return 0;//personne ne gagnemais le terrain est complet

    return -1;
}
int32_t changerSymbole(int32_t symbole)
{
  if(symbole == ROND) return CROIX;
  if(symbole == CROIX) return ROND;
  return VIDE;
}
//----------------------------------------------------------------------------
void modifier_billes(boite* b, int8_t gagnant)
{
  int32_t i, new , caseLibre,n;
  while(b != NULL)
  {
    n = 0;
    new = b->terrain;
    caseLibre = nb_case_libre(b->terrain);

    for(i = 0; i<SIZE;i++)
    {
      if(caseLibre%2 == 1)
      {
        new = set_case(b->terrain,i+1,ROND);
        while(!est_passe(b->suivants[n]))
        {
          n++;
        }
        if(gagnant == ROND && verify_sym(new, b->suivants[n]->terrain))
        {
          b->bille = set_bille(b->bille, i+1, get_bille(b->bille, i+1)+3);
        }
        else if(gagnant == CROIX && verify_sym(new, b->suivants[n]->terrain))
        {
          b->bille = set_bille(b->bille, i+1, get_bille(b->bille, i+1)-1);
        }
        else if(gagnant == VIDE && verify_sym(new, b->suivants[n]->terrain))
        {
          b->bille = set_bille(b->bille, i+1, get_bille(b->bille, i+1)+1);
        }
      }
      else
      {
        new = set_case(b->terrain,i+1,CROIX);
        while(!est_passe(b->suivants[n]))
        {
          n++;
        }
        if(gagnant == ROND && verify_sym(new, b->suivants[n]->terrain))
        {
          b->bille = set_bille(b->bille, i+1, get_bille(b->bille, i+1)-1);
        }
        else if(gagnant == CROIX && verify_sym(new, b->suivants[n]->terrain))
        {
          b->bille = set_bille(b->bille, i+1, get_bille(b->bille, i+1)+3);
        }
        else if(gagnant == VIDE && verify_sym(new, b->suivants[n]->terrain))
        {
          b->bille = set_bille(b->bille, i+1, get_bille(b->bille, i+1)+1);
        }
      }
    }
    b = b->suivants[n];
  }

}

int est_passe(boite* b)
{
  return b->bille>>63;
}

//-----------------------interface utilisateur-----------------------------
void afficheTerrain(uint32_t terrain)
{
    int i,j;
  for(i=0;i<SIZE/3;i++)
  {
    for (j=0;j<SIZE/3;j++)
    {
        if(get_case(terrain,i*(SIZE/3)+1+j)==ROND)
            printf("O|");
        else if(get_case(terrain,i*(SIZE/3)+1+j)==CROIX)
            printf("X|");
        else
            printf("-|");
    }
    printf("\n");
  }
  printf("\n");
}
int promptCoup()
{
    printf("entrez un entier entre 1 et 9 pour déterminer la case où jouer\n (1 pour en haut à gauche et 9 pour en bas à droite)\n");
    int i;
    scanf("%d",&i);
    while((i<=0) || (i>9))
    {
        printf("N'entrez qu'un entier de 1 à 9");
      scanf("%d",&i);
    }
    return i;

}

int32_t promptGamemode()
{

    int32_t i=-1;
     while(i<0)
        {
            printf("Voulez vous jouer contre l'IA ou voulez vous que l'IA joue contre elle-même? \n(0 pour JvsIA et N (positif) pour N parties de IAvsIA)");
            scanf("%d",&i);
        }
    return i;
}

boite* choix_graphe()
{
    int32_t i = -1;
    FILE* file = fopen("graphe.xox","r");

    if(file!=NULL)
    {
        while(i!= 1 && i !=0)
        {
            printf("Fichier d'IA trouvé.Voulez vous jouer avec cet IA ou en créer une nouvelle?\n(0 pour jouer,1 pour créer)\n");
            scanf("%d",&i);
        }
        if(i!=0)
        {
            printf("Création d'une nouvelle IA.\n");
        }
    }
    else
    {
         printf("Aucun fichier valable d'IA n'a été trouvé. Création d'un nouveau potentiel terminator.\n");
    }
    int32_t* figure = mymalloc(sizeof(int32_t)*850);
    boite** adresse = mymalloc(sizeof(boite*)*850);
    boite* b = creer_noeud(0);
    creer_graphe(b,figure,adresse);
    myfree(figure);
    myfree(adresse);


    printf("%d\n",i);
    if(i==0)
    {
      boite** loadadresse = mymalloc(sizeof(boite*)*850);
      charger_graphe(b,loadadresse,file);
      myfree(loadadresse);
      fclose(file);
    }


    return b;
}
int promptPremierJoueur()
{
  int32_t i=-1;
  while(i!= 1 && i !=0)
  {
    printf("Qui commence?\n0:Vous\n1:l'IA\n");
    scanf("%d",&i);
  }
  return i;
}


void change_player()
{
  if(_currentPlayer == ROND) _currentPlayer = CROIX;
  else if(_currentPlayer == CROIX) _currentPlayer = ROND;
  else printf("BIZARRE !\n");
}
