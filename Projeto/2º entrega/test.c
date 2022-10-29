#include <stdio.h>
#include <stdlib.h>
#include "garfo.h"

int prio(Item *a){
    return ((node *) a)->wt;
}

int main(int argc, char* argv[]){
    head *h;
    FILE *f = fopen(argv[1], "r");
    int i, j;
    node * twint;
    if (f == NULL)
        exit(-2);
    fscanf(f,"%d %d",&i, &j);
    h = headinit(i, j, prio);
    for (j = 0;fscanf(f,"%d",&i) == 1; j++)
    {
        twint = (node *) malloc(sizeof(node));
        if (twint == NULL)
            exit(-1);
        twint->n2 = j;
        twint->wt = i;
        puthead(h, (Item *) twint);
    }
    while (h->e != 0)
    {
        twint = (node *) gethead(h);
        printf("%d %d\n", twint->n2, twint->wt);
        free(twint);
    }
    pullout(h, free);
    fclose(f);
}