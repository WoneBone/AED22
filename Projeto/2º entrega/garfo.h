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

    int *heads;
    int e;
    int wt;
    int nv;
    int *pr;
    int *pos;
} head;

/* funções de grafos */
garfo* garfointit( int nv);
void putingarfo(garfo* g,Item v[],int max_wt,int test(Item,Item));
void facagarfo(garfo* g);
int test(Item w1,Item w2);
void garfada (garfo *g);
void djigja(garfo *g, int o, int d, int st[], int max_wt);

/* funções de acervos */
head *headinit(int nv, int max_wt);
void puthead(head* a,int b, int v);
void fixheadup(head*a, int p);
void fixheadown(head*a, int pos);
int smolprius(head *a);
int gethead(head*a);
void pullout(head *a);
int headnotempty(head *a);
int getprius(head *a, int v);
void chgprius(head *a, int v, int pr);

