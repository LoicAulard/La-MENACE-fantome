#include "hashtable.h"

void init_hashtable(hashtable* h)
{
  int i;
  for (i=0; i<=SIZE; i++)
  {
    h->table[i]=new_liste();
  }
}

void fill_hashtable(hashtable* h)
{
  int i=0,j=0;
  maillon* m = NULL;
  box d;
  for(i=0; i<SIZE; i++)
  {
    m = h->table[i]->tete;
    printf("%p\n", m);
    while (m != NULL)
    {
      for(j=1; j<=SIZE; j++)
      {
        if (get_case(m->data->terrain,j) == VIDE)
        {
          d = new_box(set_case(m->data->terrain,j,_currentPlayer));
          set_bille(d.bille, j, 0);
          if(in_list(h->table[i+1], d) == 0)
          {
            add_tete(h->table[i+1], d);
          }
        }
      }
      m=m->next;
    }
    change_player();
  }
  _currentPlayer = CROIX;
}

void fill_symetrie_array(hashtable* h)
{
  int i=0;
  maillon *m=NULL,*n = NULL;
  maillon **array1 = NULL;
  for (i=0; i<=SIZE;i++)
  {

    m = h->table[i]->tete;
    while (m!=NULL)
    {
      n = h->table[i]->tete;
      while (n!=NULL)
      {
        // printf("m_box :\n");
        // print_box(*(m->data));
        // printf("n_box :\n");
        // print_box(*(n->data));
        if(isSymetric(m->data->terrain,n->data->terrain))
        {
          //printf("SYMETRIE CATCH\n");
          array1 = mymalloc(sizeof(maillon*));
          *(array1) = n;
          m->data->symetrie = merge_maillon_array(m->data->symetrie,array1);
        }
        n=n->next;
      }
      m=m->next;
    }
  }
}

maillon** merge_maillon_array(maillon** array1, maillon** array2)
{
  if(array1 == NULL && array2 == NULL) return NULL;
  else if(array1 == NULL) return array2;
  else if(array2 == NULL) return array1;
  else
  {
    uint64_t i=0;
    /*Get the size of arrays*/
    //printf("%p | ",array1);
    uint64_t size1 = mytabsize(array1, sizeof(maillon*));
    uint64_t size2 = mytabsize(array2, sizeof(maillon*));
    maillon** new_array = mymalloc((size1+size2)*sizeof(maillon*));
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

box new_box(int32_t terrain)
{
  int i=0;
  box b;
  b.terrain = terrain;
  for(i=1;i<=SIZE;i++)
  {
    b.bille = set_bille(b.bille, i, 64);
  }
  b.passage = 0;
  b.symetrie = NULL;
  return b;
}

void change_score(hashtable* h)
{
  unsigned int i = 0, j=0 ;
  int point =0;
  maillon *m;
  for(i=0;i<=SIZE;i++)
  {
    m = h->table[i]->tete;
    while (m!=NULL)
    {
      if(m->data->passage!=0)
      {
        if(_victoryIA == WIN )
        {
          if(i%_playerIA == 0) point = 3;
          else point = -1;
        }
        if(_victoryIA == DRAW)
        {
          point = 1;
        }
        if(_victoryIA == LOST)
        {
          if(i%_playerIA == 0) point = -1;
          else point = 3;
        }
        m->data->bille = set_bille(m->data->bille, m->data->passage, get_bille(m->data->bille, m->data->passage)+point);
        for(j=0; j<mytabsize(m->data->symetrie,sizeof(maillon*));j++)
        {
          m->data->symetrie[i]->data->bille = set_bille(m->data->symetrie[i]->data->bille, m->data->symetrie[i]->data->passage, get_bille(m->data->symetrie[i]->data->bille, m->data->symetrie[i]->data->passage)+point);
        }
        break;
      }
      m=m->next;
    }
  }
}

void print_hashtable(hashtable h)
{
  int i=0;
  for(i=0; i<=SIZE; i++)
  {
    afficher_liste(h.table[i]);
  }
}

void print_box(box b)
{
  printf("terrain = %x | billes = %x | pasage = %d | symetrie = %p\n",b.terrain, b.bille, b.passage, b.symetrie );
}

void save_hashtable(hashtable *h, char *filename )
{
  int i = 0;
  maillon *m = NULL;
  FILE* file = fopen(filename, "w");
  for (i=0; i<=SIZE; i++)
  {
    m=h->table[i]->tete;
    while (m!=NULL)
    {
      fwrite(&i, sizeof(int),1,file);
      fwrite(m->data,sizeof(box),1, file);
      m=m->next;
    }
  }
  fclose(file);
}

void load_hashtable(hashtable *h,char *filename)
{
  box data;
  int i = 0;
  FILE* file = fopen(filename, "r");
  while(fread(&i, sizeof(int), 1, file)==1)
  {
    fread(&data, sizeof(box), 1, file);
    printf("%d\n",i);
    add_tete(h->table[i],data);
  }
  fclose(file);
}
