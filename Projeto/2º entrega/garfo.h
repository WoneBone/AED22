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
    int e;
    int wt;
    int nv;
    int (*prio)(Item *);
    int *pr;
} head;

/* funções de grafos */
garfo* garfointit( int nv);
void putingarfo(garfo* g,Item v[],int max_wt,int test(Item,Item));
void facagarfo(garfo* g);
int test(Item w1,Item w2);
void djigja(garfo *g, int s, int st[], int wt[], int max_wt);

/* funções de acervos */
head *headinit(int nv, int max_wt, int prio(Item *));
void puthead(head* a,Item *b);
void fixheadup(head*a, int p);
void fixheadown(head*a, int pos);
Item* gethead(head*a);
void pullout(head *a, void freeI(Item ));

