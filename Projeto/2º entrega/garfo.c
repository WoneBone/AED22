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

void djigja(garfo *g, int s, int inhead[], int max_wt, int prio(Item *)){
    int v, w;
    head *a;
    node *t, *i1, *12;
    LinkedList *n,

    a = headinit(g->nv, max_wt, prio);

    for (v = 0; v < f->nv; v++){
        inhead[v] = -1;
    }
    
    t = (node *) malloc(sizeof(node));
    t->n2 = s;
    t->wt = 0;
    puthead(a, t);

    do{
        t = gethead(a);
        n = g->graf[t->n2];
        while(n != NULL){
            i1 = getItemLinkedList(n);
            if (inhead[i1->n2] == -1){
                i2 = (node *) malloc(sizeof(node));
                i2->n2 = i1->n2;
                i2 ->wt = i1->wt + t->wt;
                inhead[i2->n2] = t -> n2;
                puthead(a, i2); 
            }
            else if ((w = i1->wt + t->wt) < getprio(a, i1->n2)){}
                chgprio(a, i1->n2, w);
                inhead[i2->n2] = t -> n2;    
            }
        }
    }while(!headempty(a))

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
head *headinit(int nv, int max_wt, int prio(Item *)){
    head *h = (head *) malloc(sizeof(head));
    int i = 0;
    if( h == NULL)
        exit(-1);

    h->heads = (Item **) calloc(nv,sizeof(Item *));
    h -> pr = (int *) malloc(nv * sizeof(int));
    h -> pos = (int *) malloc(nv * sizeof(int));

    if( (int) h->heads && (int) h->pr && (int) h->pos)
        exit(-1);
    for (; i < nv; i++)
        h->pr[i] = max_wt + 1;
        h->pos[i] = -1;
    
    h->nv = nv;
    h->wt = max_wt;
    h->e = 0;
    h->prio = prio;
    return h;
}

void puthead(head* a,Item *b){
    if (a->prio(b) > a->wt){        /* Este if serve para garantir que uma má utilização do código não leva a um crash por double free.*/
        free(b);                    /* Tem o efeito secundário de se b não for libertado por apenas um free os restantes blocos são perdidos*/
        return;                     /*  No entanto como se trata de um edge case por uma má implementação por parte do cliente that's a price we are willing to pay*/
        
    }
    a->heads[a->e] = b;
    a->pr[a->e] = a->prio(b);
    a->pos[b] = a->e;
    
    fixheadup(a, a->e);

    a->e++;
    return;
}

void fixheadup(head* a, int pos){
    Item *tmp;
    int t;
    while(pos > 0 && (a->pr[(pos -1)/2] > a->pr[pos])){
        tmp = a->heads[pos];
        a->heads[pos] = a->heads[(pos-1)/2];
        a->heads[(pos-1)/2] = tmp;

        t = a->pr[pos];
        a->pr[pos] = a->pr[(pos-1)/2];
        a->pr[(pos-1)/2] = t;

        a->pos[(a->heads[pos])->n2] = pos;
        a->pos[(a->heads[(pos - 1)/2])->n2] = (pos - 1)/ 2;

        pos = (pos - 1)/2;
    }
}

Item *gethead(head * a){
    Item *ret = a->heads[0];
    a->pr[0] = a->wt +1;
    a->pos[(a->heads[0])->n2] = -1;
    fixheadown(a, 0);
    a->e--;
    return ret;
}

void fixheadown(head *a, int pos){
    Item *tmp;
    int child, t;
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

            t = a->pr[pos];
            a->pr[pos] = a->pr[child];
            a->pr[child] = t;

            a->pos[(a->heads[pos])->n2] = pos;
            a->pos[(a->heads[child])->n2] = child;

            pos = child;
        }
    }

}

void pullout(head *a, void freeI(Item )){
    int i = 0;

    for(; i< a->e; a++)
        freeI(a->heads[i]);

    free(a->heads);
    free(a->pr);
    free(a->pos);
    free(a);
    

}