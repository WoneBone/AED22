#include <stdio.h>
#include <stdlib.h>
#include "garfo.h"


int main(int argc, char* argv[]){
    garfo *a;
    FILE *f = fopen(argv[1], "r");
    int i, j, wt, max_wt;
    int *st;
    node *n1, *n2;
    if (f == NULL)
        exit(-2);
    fscanf(f,"%d %d",&i, &max_wt);
    st = (int*) malloc((i + 1) * sizeof(int));
    a = garfointit(i + 1 );
    while (fscanf(f,"%d %d %d",&i, &j, &wt) == 3)
    {
        n1 = (node *) malloc(sizeof(node));
        n2 = (node *) malloc(sizeof(node));
        if(n1 == NULL || n2 == NULL)
            exit(-1);
        n1 -> n2 = j; n1->wt = wt;
        n2 -> n2 = i; n2->wt = wt;
        a->graf[i] =insertUnsortedLinkedList(a->graf[i],n1);
        a->graf[j] = insertUnsortedLinkedList(a->graf[j], n2);
        a->ne++;
    }
    garfada(a);
    scanf("%d %d", &i, &j);

    djigja(a, i, j, st, max_wt);


    for(; j != st[j] ; j = st[j]){
        printf("%d", j);
    }


    facagarfo(a);
    fclose(f);
    free(st);
}