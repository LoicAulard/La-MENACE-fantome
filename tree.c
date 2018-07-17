#include <stdlib.h>
#include <stdio.h>
#include "mytab.h"
#include "menace.h"
#include "tree.h"

int64_t count = 0;

node_t* create_node(int32_t terrain)
{
  count++;
  int i;
  node_t* t = mymalloc(sizeof(node_t));
  //printf("Allownigspace for following node\n");
  printf("%d | ",nb_case_libre(terrain));
  t->suivants = mycalloc(nb_case_libre(terrain)*sizeof(node_t*));
  t->symetries = NULL;
  t->terrain = terrain;
  for (i=1; i<=SIZE; i++)
  {
    t->bille = set_bille(t->bille, i, 60);
  }
  return t;
}

void destroy_node(node_t *n)
{
  myfree(n->suivants);
  myfree(n);
}

node_t** merge_node_array(node_t** array1, node_t** array2)
{
  if(array1 == NULL && array2 == NULL) return NULL;
  else if(array1 == NULL) return array2;
  else if(array2 == NULL) return array1;
  else
  {
    uint64_t i=0;
    /*Get the size of arrays*/
    printf("%p | ",array1);
    uint64_t size1 = mytabsize(array1, sizeof(node_t*));
    uint64_t size2 = mytabsize(array2, sizeof(node_t*));
    node_t** new_array = mymalloc((size1+size2)*sizeof(node_t*));
    /*Copy of first array*/
    while (i<size1)
    {
      new_array[i] = array1[i];
      i++;
    }
    /*Copy of second array*/
    while (i<size1+size2)
    {
      new_array[i] = array2[i-size1];
      i++;
    }
    /*Free old array*/
    myfree(array1);
    myfree(array2);
    return new_array;
  }
}

node_t* create_menace_tree(node_t* root)
{
  //printf("%ld | ", count);
  int i, index=0;
  if (partieFinie(root->terrain) == -1)
  {
    for(i=1; i<=SIZE;i++)
    {
      if(get_case(root->terrain,i) == VIDE)
      {
        //printf("Creation of next nodes\n");
        root->suivants[index] = create_node(set_case(root->terrain, i, _currentPlayer));
        change_player();
        create_menace_tree(root->suivants[index]);
        index++;
      }
    }
  }
  return root;
}

node_t** get_symmetry(node_t* root, uint32_t terrain)
{
  //afficheTerrain(root->terrain);
  if (isSymetric(root->terrain,terrain))
  {
    node_t** n = mymalloc(sizeof(node_t*));
    *n=root;
    return n;
  }
  else if(partieFinie(root->terrain)==-1)
  {
    int i;
    node_t** final = mymalloc(0);
    for (i=0; i<nb_case_libre(root->terrain);i++)
    {
      merge_node_array(final, get_symmetry(root->suivants[i], terrain));
    }
    return final;
  }
  else
  {
    return NULL;
  }
}

void set_symmetry_array(node_t* root, node_t* node)
{
  unsigned int i;
  afficheTerrain(node->terrain);
  printf("%p\n",node->suivants);
  uint64_t size = mytabsize(node->suivants, sizeof(node_t*));
  if (size != 0 && partieFinie(node->terrain) ==-1)
  {
    for(i = 0; i < size; i++)
    {
      printf("suivants\n");
      set_symmetry_array(root, node->suivants[i]);
    }
  }
  node->symetries = get_symmetry(root, node->terrain);
}
