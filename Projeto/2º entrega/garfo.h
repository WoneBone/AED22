#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"


typedef struct graf{
    LinkedList** graf;
    int nv;
    int ne;
} garfo;

typedef struct node {
    int n2;
    int wt;
} node;

garfo* garfointit( int nv);
void putingarfo(garfo* g,Item v[],int max_wt,int test(Item,Item));
void facagarfo(garfo* g);
int test(Item w1[],Item w2[]);