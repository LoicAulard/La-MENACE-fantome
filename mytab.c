#include <stdio.h>
#include <stdlib.h>
#include "mytab.h"


void* mymalloc(uint64_t i)
{
  uint64_t *p = malloc(i+8);
  if(p == NULL)
  {
    printf("malloc() error in %s %s:%d",__FILE__,__func__,__LINE__);
    exit(0);
  }
  p[0]=i;
  return (void*)(p+1);
}

void* mycalloc(uint64_t i)
{
  uint64_t *p = calloc(1,i+8);
  if(p == NULL)
  {
    printf("calloc() error in %s %s:%d",__FILE__,__func__,__LINE__);
    exit(0);
  }
  p[0]=i;
  return (void*)(p+1);
}

uint64_t mymemsize(void* t)
{
  return *(((uint64_t*)t)-1);
}

uint64_t mytabsize(void *p, uint64_t sizeof_element)
{
  return mymemsize(p)/sizeof_element;
}

void myfree(void *p)
{
  free(((uint64_t*)p)-1);
}

void affichage(uint32_t *p)
{
  uint64_t i;
  for (i=0; i<mytabsize(p,sizeof(uint32_t)); i++)
  {
    printf("%d\n",p[i]);
  }
}
