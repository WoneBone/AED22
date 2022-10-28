#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"
#include "defs.h"


typedef struct graf{
    LinkedList** graf;
    int nv;
    int ne;
} garfo;

typedef struct node {
    int n2;
    int wt;
} node;

typedef struct head{

    Item **heads;
    int wt;
    int nv

} head;

garfo* garfointit( int nv);
void putingarfo(garfo* g,Item v[],int max_wt,int test(Item,Item));
void facagarfo(garfo* g);
int test(Item w1,Item w2);
Item headinit(int nv);
void puthead(head* a,head *b);
void fixheadup(head*a);
void fixheadown(head*a);
Item* gethead(head*a, int max_wt);

