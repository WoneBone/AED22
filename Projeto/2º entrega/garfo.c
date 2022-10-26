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

                insertUnsortedLinkedList(g->graf[i],n1);
                insertUnsortedLinkedList(g->graf[j], n2);
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
*   test()
*   
*   Argumentos: item , item 
*
*   Returns: int
*
*   Side effects: none
*
*   Descrição: testa quantas letras sao diferentes em duas palavras
* 
*
**************************************************************/
int test(Item w1[], Item w2[]){
    int i=0, count=0;
    for (i=0;i<=strlen(w1[]);i++){
        if(w1[i]==w2[i]){
            count++;
        }
    }
    return count;
}