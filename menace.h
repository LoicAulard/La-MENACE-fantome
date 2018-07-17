#ifndef MEN_H
#define MEN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "mytab.h"

//Definition des constante symbolique.
#define SIZE 9

#define CROIX 1
#define ROND  2
#define VIDE  0

#define PLAYER1 1
#define PLAYER2 2

#define WIN 1
#define DRAW 0
#define LOST -1

#define MASQUE_CASE 0
#define MASQUE_BILLE 1

#define IA_VS_IA 0
#define PLAYER_VS_IA 1

int _currentPlayer;
int _victoryIA;
int _playerIA;
int32_t _currentTerrain;

typedef struct _boite
{
  int32_t terrain;
  int64_t bille;
  struct _boite **suivants;
} boite;

int set_case(int terrain, int cases, int value);
int get_case(int terrain, int cases);
uint64_t get_bille(uint64_t billes, int Case);
uint64_t set_bille(uint64_t billes, int Case, uint64_t value);
uint64_t sommeBilles(uint64_t billes);
int nb_case_libre(int terrain);
int symetrie_v(int32_t t1, int32_t t2); /*NTU*/
int symetrie_h(int32_t t1, int32_t t2); /*NTU*/
int symetrie_d1(int32_t t1, int32_t t2);/*NTU*/
int symetrie_d2(int32_t t1, int32_t t2);/*NTU*/
int rotationD90(int32_t t1,int32_t t2); /*NTU*/
int rotationG90(int32_t t1,int32_t t2); /*NTU*/
int64_t CreerMasque(int Case, int typeMasque);
void creer_graphe(boite* b, int32_t* figure, boite** addresse);
int32_t verify_tab(int32_t terrain, int32_t* tab);
/*Differences ???*/
int isSymetric(int32_t t1, int32_t t2);
int32_t verify_sym(int32_t terrain, int32_t t2);
/*----------------*/
boite* creer_noeud(int32_t terrain);
void afficheTerrain(uint32_t terrain);
void charger_graphe(boite* b, boite** adresse, FILE* file);
void save_graphe(boite* b, boite** adresse, FILE* file);
void free_graphe(boite* b, boite** adresse);
int checkfree(boite* b, boite** adresse);
int ProchainCoup(uint64_t billes);
/**********Partie_finie********************
* Return -1 if the game is not ended else *
* it return the winner and 0 if it is     *
* a draw.                                 *
******************************************/
int partieFinie(uint32_t terrain);
void set_passage(boite * b);
int est_passe(boite* b);
void modifier_billes(boite* b, int8_t gagnant);
//---Interface utilisateur
int promptCoup();
int32_t promptGamemode();
boite* choix_graphe();
int32_t changerSymbole(int32_t symbole);
int promptPremierJoueur();
void change_player();




#endif
