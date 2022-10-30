#include "garfo.h"


/*************************************************************
*   garfointit()
*   
*   Argumentos: nv - Número de vértiuces
*
*   Returns: Garfo inicializado
*
*   Side effects: none
*
*   Descrição: Inicializa um garfo
* 
*
**************************************************************/
garfo* garfointit(int nv){
    garfo * g = (garfo *) malloc(sizeof(garfo));
    if (g == NULL)
        exit(-1);
    
    g->graf = (LinkedList **) calloc(nv, sizeof(LinkedList*));
    if (g->graf == NULL)
        exit(-1);
    g->nv = nv;
    g->ne = 0;

    return g;
}

/*************************************************************
*   garfointit()
*   
*   Argumentos: g - garfo a preencher
*               v[] - vetor de vértices
*               max_wt - valor máximo de peso de aresta (acima disto não pões no grafo)
*               test - função que verifica a existência de aresta entre dois vértices e devolve o seu peso ou -1 se não existir
*
*   Returns:
*
*   Side effects: none
*
*   Descrição: Preenche um garfo com os vetrores em v
* 
*
**************************************************************/
void putingarfo(garfo* g,Item v[],int max_wt,int test(Item,Item)){
    int i = 0, j = 0, wt = max_wt;
    node *n1, *n2;

    for (i = 0; i < g->nv; i++){
        for (j = i + 1; j < g->nv; j++){
            wt = test(v[i], v[j]);
            if (wt <= max_wt && wt >= 0){
                n1 = (node *) malloc(sizeof(node));
                n2 = (node *) malloc(sizeof(node));
                if(n1 == NULL || n2 == NULL)
                    exit(-1);
                n1 -> n2 = j; n1->wt = wt;
                n2 -> n2 = i; n2->wt = wt;

                g->graf[i] =insertUnsortedLinkedList(g->graf[i],n1);
                g->graf[j] = insertUnsortedLinkedList(g->graf[j], n2);
                g->ne++;
            }
        }
    }
}

/*************************************************************
*   garfointit()
*   
*   Argumentos: g - garfo a libertar
*
*   Returns:
*
*   Side effects: none
*
*   Descrição: dá free de grafo
* 
*
**************************************************************/

void facagarfo(garfo* g){
    int i = 0;

    for (; i < g->nv; i++){
        freeLinkedList(g->graf[i], free);
    }
    free(g->graf);
    free(g);
}
/*************************************************************
*   garfada()
*   
*   Argumentos: g - garfo imprimir
*
*   Returns:
*
*   Side effects: none
*
*   Descrição: imprime o grafo para o stdout. Deve ser usada apenas como debug
* 
*
**************************************************************/
void garfada (garfo *g){
    int i;
    LinkedList *lp;
    node *n;
    for(i = 0; i < g->nv; i++) {
        lp = g->graf[i];
        while (lp != NULL) {
            n = (node *) getItemLinkedList(lp);
            lp = getNextNodeLinkedList(lp);
            printf("%d:%d  ", n->n2, n->wt);
        }
        fprintf(stdout, " -1\n");
    }
}

void djigja(garfo *g, int o, int d, int inhead[], int max_wt){
    int v, w;
    head *a= headinit(g->nv, max_wt);
    node *t, *i;
    LinkedList *n;

    for (v = 0; v < a->nv; v++){
        inhead[v] = -1;
    }
    
    t = (node *) malloc(sizeof(node));
    if (t == NULL)
        exit(-1);
    inhead[o] = o;
    t->n2 = o;
    t->wt = 0;
    puthead(a, t->n2, t->wt);

    while(headnotempty(a) == 1){
        t->wt = smolprius(a);
        t->n2 = gethead(a);

        if (t->n2 == d)
            break;
        n = g->graf[t->n2];
        while(n != NULL){
            i = getItemLinkedList(n);
            if (inhead[i->n2] == -1){
                puthead(a, i->n2, i->wt + t->wt);
                inhead[i->n2] = t -> n2;
            }
            else if ((w = i->wt + t->wt) < getprius(a, i->n2) && getprius(a, i->n2) < max_wt + 1){
                chgprius(a, i->n2, w);
                inhead[i->n2] = t -> n2;
            }
            n = getNextNodeLinkedList(n);
        }
    }
    free(t);
   // pullout(a);

}
/*************************************************************
*   headinit()
*   
*   Argumentos: nv - númeto total de vértice
*               max_wt - prioridade a partir da qual se considera que não há ligação
*
*   Returns: pointer to acervo
*
*   Side effects: none
*
*   Descrição: allocação de acervo
* 
*
**************************************************************/
head *headinit(int nv, int max_wt){
    head *h = (head *) malloc(sizeof(head));
    int i = 0;
    if( h == NULL)
        exit(-1);

    h->heads = (int*) calloc(nv,sizeof(int *));
    h->pr = (int *) malloc(nv * sizeof(int));
    h->pos = (int *) malloc(nv * sizeof(int));

    if( !((long int) h->heads && (long int) h->pr && (long int) h->pos))
        exit(-1);
    for (; i < nv; i++){
        h->pr[i] = max_wt + 1;
        h->pos[i] = -1;
        h -> heads[i] = -1;
    }
    
    h->nv = nv;
    h->wt = max_wt;
    h->e = 0;
    return h;
}

void puthead(head* a, int b, int pr){  

    a->heads[a->e] = b;
    a->pr[a->e] = pr;
    a->pos[b] = a->e; 
    
    fixheadup(a, a->e);

    a->e++;
    return;
}

void fixheadup(head* a, int pos){
    int tmp;
    int t;
    while(pos > 0 && (a->pr[(pos -1)/2] > a->pr[pos])){
        tmp = a->heads[pos];
        a->heads[pos] = a->heads[(pos-1)/2];
        a->heads[(pos-1)/2] = tmp;

        t = a->pr[pos];
        a->pr[pos] = a->pr[(pos-1)/2];
        a->pr[(pos-1)/2] = t;

        a->pos[a->heads[pos]] = pos;
        a->pos[a->heads[(pos - 1)/2]] = (pos - 1)/ 2;

        pos = (pos - 1)/2;
    }
}

int gethead(head * a){
    int ret = a->heads[0];
    a->pr[0] = a->wt +1;
    a->pos[ret] = -1;
    fixheadown(a, 0);
    a->e--;
    return ret;
}

void fixheadown(head *a, int pos){
    int tmp;
    int child;
    while (2*pos < a-> nv -1){
        child = (2*pos) + 1;
        if (child < a->nv - 1){
            if (a->pr[child] >a->pr[child+1])
                child++;
        }
        if (a->pr[pos] < a->pr[child]) break;

        else{
            tmp = a->heads[pos];
            a->heads[pos] = a->heads[child];
            a->heads[child] = tmp;

            tmp = a->pr[pos];
            a->pr[pos] = a->pr[child];
            a->pr[child] = tmp;

            a->pos[a->heads[pos]] = pos;
            a->pos[a->heads[child]] = child;

            pos = child;
        }
    }

}

void pullout(head *a){

    free(a->heads);
    free(a->pr);
    /*free(a->pos);*/
    free(a);
    

}

int headnotempty(head *a){
    if (a->e == 0)
        return 0;
    return 1;
}

int getprius(head *a, int v){
    return a->pr[a->pos[v]];
}

void chgprius(head *a, int v, int pr){
    if ( a->pr[a->pos[v]] < pr){
        a->pr[a->pos[v]] = pr;
        fixheadup(a, a->pos[v]);
    }
    else if (a->pr[a->pos[v]] > pr){
        a->pr[a->pos[v]] = pr;
        fixheadown(a, a->pos[v]);
    }

    return;

} 

int smolprius(head *a){
    return a->pr[0];
}