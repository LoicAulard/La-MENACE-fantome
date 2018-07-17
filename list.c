#include "list.h"

/*definitiopn des fonction*/
liste* new_liste()
{
  liste *r = malloc(sizeof(liste));
  if(r == NULL) assert(0);
  r->taille = 0;
  r->tete = NULL;
  r->queue = NULL;
  printf("%p\n", r);
  return r;
}

maillon* new_maillon(struct box_t d)
{
  maillon *m = malloc(sizeof(maillon));
  if(m  == NULL) assert(0);
  m->data = malloc(sizeof(box));
  if(m->data  == NULL) assert(0);
  *(m->data) = d;
  return m;
}

void add_tete(liste *l, struct box_t d)
{
  maillon *m =new_maillon(d);
  m->next = l->tete;
  l->tete = m;
  if(l->taille==0)
  {
    l->queue = m;
  }
  l->taille++;
}

void afficher_liste(liste *l)
{

  liste *t = new_liste();
  t->tete = l->tete;

  while(l->tete !=NULL)
  {
    afficheTerrain(l->tete->data->terrain);
    printf("\n");
    l->tete = (l->tete)->next;
  }
  printf("NULL\n");
  l->tete = t->tete;

}

struct box_t* rem_tete(liste *l)
{
  maillon *t = l->tete;
  struct box_t* r = t->data;

  l->tete = l->tete->next;
  free(t);
  l->taille--;

  return r;
}

void add_croissant(liste *l, struct box_t d)
{
  maillon *new, *tmp1;
  tmp1 = l->tete;
  while(l->tete->next != NULL && d.bille >= l->tete->next->data->bille)
  {
    l->tete =l->tete->next;
  }

  new =new_maillon(d);
  new->next = l->tete->next;
  (l->tete)->next = new;
  if(l->tete->next == NULL)
  {
    l->queue = new;
  }
  l->taille++;
  l->tete = tmp1;
}

int in_list(liste *l, struct box_t d)
{
  maillon* m = l->tete;
  while(m != NULL)
  {
    if(m->data->terrain == d.terrain) return 1;
    m = m->next;
  }
  return 0;
}

maillon* get_maillon(liste *l, int32_t terrain)
{
  maillon *m = l->tete;
  while(m != NULL)
  {
    if(m->data->terrain == terrain)
    {
      return m;
    }
    m = m->next;
  }
  return NULL;
}
