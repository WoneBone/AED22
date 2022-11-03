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
*   putingarfo()
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

                g->graf[i] = insertUnsortedLinkedList(g->graf[i],n1);
                g->graf[j] = insertUnsortedLinkedList(g->graf[j], n2);
                g->ne++;
            }
        }
    }
}

/*************************************************************
*   facagarfo()
*   
*   Argumentos: g - garfo a libertar
*
*   Returns:
*
*   Side effects: none
*
*   Descrição: liberta o grafo dado
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
garfo * colhergarfo(garfo* g, int nmax_wt){
    LinkedList *del, *aux;
    node *curr;

    for (int i = 0; i< g->nv; i++){
        aux = g->graf[i];
        if(aux == NULL)
            continue;

        del = getNextNodeLinkedList(aux);
        curr = (node *) getItemLinkedList(aux);
        while(curr->wt > nmax_wt){ //caso de ter que remover cabeça
            free(curr);
            free(aux);
            g->graf[i] = del;
            aux = g->graf[i];
            if(aux == NULL)
                break;
            del = getNextNodeLinkedList(aux);
            curr = (node *) getItemLinkedList(aux);
        }
        while (del != NULL){
            curr = (node *) getItemLinkedList(del);
            if(curr->wt > nmax_wt){
                revoveFromList(aux, del, free);
                del = getNextNodeLinkedList(aux);
            }
            else{
                aux = del;
                del = getNextNodeLinkedList(aux);
            }
            
        }
    }
    
    return g;
}
/*************************************************************
*   djigja()
*   
*   Argumentos: g- garfo onde encontrar o caminho , o - palavra de origem, a- palavra de destino
*   inhead[]- vetor para o caminho encontrado, wt- array com os pesos de mutações,
*   max_wt- variavel poara determinar o weight dos caminhos nao percorridos
*
*   Returns:
*
*   Side effects: none
*
*   Descrição: implementa o algoritmo dikstra num garfo dado para encontrar o melhor caminho entre o e a
* 
*
**************************************************************/

void djigja(garfo *g, int o, int d, int inhead[], int wt[], int max_wt){
    int v, w;
    head *a= headinit(g->nv, max_wt);
    node *t, *i;
    LinkedList *n;

    for (v = 0; v < a->nv; v++){
        inhead[v] = -1;
        wt[v] = max_wt;
    }
    
    t = (node *) malloc(sizeof(node));
    if (t == NULL)
        exit(-1);
    inhead[o] = o;
    puthead(a, o, 0);

    while(headnotempty(a) == 1){
        t->wt = smolprius(a);
        t->n2 = gethead(a);
        wt[t->n2] = t->wt;

        if (t->n2 == d)
            break;
        n = g->graf[t->n2];
        while(n != NULL){
            i = getItemLinkedList(n);
            if (inhead[i->n2] == -1){
                puthead(a, i->n2, i->wt + t->wt);
                inhead[i->n2] = t -> n2;
            }
            else if ( getpos(a, i->n2) != -1 && (w = i->wt + t->wt) < getprius(a, i->n2)){
                chgprius(a, i->n2, w);
                inhead[i->n2] = t -> n2;
            }
            n = getNextNodeLinkedList(n);
        }
    }
    free(t);
    pullout(a);

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
        h->pr[i] = max_wt;
        h->pos[i] = -1;
        h -> heads[i] = -1;
    }
    
    h->nv = nv;
    h->wt = max_wt;
    h->e = 0;
    return h;
}

void puthead(head* a, int b, int pr){
    if (pr > a->wt)       
        return;   

    a->heads[a->e] = b;
    a->pr[a->e] = pr;
    a->pos[b] = a->e; 
    
    fixheadup(a, a->e);

    a->e++;
    return;
}
/*************************************************************
*   fixheadup()
*   
*   Argumentos: head* a - pointer para o principio do acervo , pos-
*               
*
*   Returns: 
*
*   Side effects: none
*
*   Descrição: acerta o acervo para quando o filho tem uma maior prioridade que o pai
* 
*
**************************************************************/

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
    int ret = a->heads[0], t;

    a->heads[0] = -1;
    a->pr[0] = a->wt;
    a->pos[ret] = -1;

    a->heads[0] = a->heads[--a->e];
    a->heads[a->e] = -1;

    t = a->pr[0];
    a->pr[0] = a->pr[a->e];
    a->pr[a->e] = t;
    if(headnotempty(a)){
        a->pos[a->heads[0]] = 0;
        fixheadown(a, 0);
    }
    a->pos[ret] = -1;
    return ret;
}
/*************************************************************
*   fixheadup()
*   
*   Argumentos: head* a - pointer para o principio do acervo , pos-
*               
*
*   Returns: 
*
*   Side effects: none
*
*   Descrição: acerta o acervo para quando o pai tem uma menor prioridade que o filho
* 
*
**************************************************************/

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
/*************************************************************
*   pullout()
*   
*   Argumentos: head* a - pointer para o principio do acervo
*               
*
*   Returns: 
*
*   Side effects: none
*
*   Descrição: dá free ao acervo 
* 
*
**************************************************************/

void pullout(head *a){

    free(a->heads);
    free(a->pr);
    free(a->pos);
    free(a);
    

}
/*************************************************************
*   headnotempty()
*   
*   Argumentos: head* a - pointer para o principio do acervo
*               
*
*   Returns: int
*
*   Side effects: none
*
*   Descrição: verifica se a cabeça do acervo nãoi esta vazia
* 
*
**************************************************************/


int headnotempty(head *a){
    if (a->e == 0)
        return 0;
    return 1;
}
/*************************************************************
*   getprius()
*   
*   Argumentos: head* a - pointer para o principio do acervo, v-
*               
*
*   Returns: prioridade
*
*   Side effects: none
*
*   Descrição: vai buscar a prioridade de um membro do acervo
* 
*
**************************************************************/

int getprius(head *a, int v){
    return a->pr[a->pos[v]];
}
/*************************************************************
*   chgprius()
*   
*   Argumentos: head* a - pointer para o principio do acervo, v-, pr- prioridade de um membro
*               
*
*   Returns: 
*
*   Side effects: none
*
*   Descrição: muda a priporoidade de um membro do acervo
* 
*
**************************************************************/

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
/*************************************************************
*   pullout()
*   
*   Argumentos: head* a - pointer para o principio do acervo
*               
*
*   Returns: 
*
*   Side effects: none
*
*   Descrição: dá free ao acervo 
* 
*
**************************************************************/

int getpos(head *a, int v){
    return a->pos[v];
}

int smolprius(head *a){
    return a->pr[0];
}

