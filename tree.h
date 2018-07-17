#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct node
{
  int32_t terrain;
  int64_t bille;
  _Bool   passage;
  struct node **symetries;
  struct node **suivants;
}node_t;

int64_t count;
/*
* This function create a node*/
node_t* create_node(int32_t terrain);
void destroy_node(node_t *n);

node_t* create_menace_tree(node_t* root);
node_t** merge_node_array(node_t** array1, node_t** array2);

void set_symmetry_array(node_t* root, node_t* node);
node_t** get_symmetry(node_t* root, uint32_t terrain);

void change_player();





#endif
