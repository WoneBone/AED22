/******************************************************************************
 *
 * File Name: main.c
 *	
 * Authors:   Yo moma
 * Last modified: 420/69
 * Revision:  check git
 *
 *
 *****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dichandl.h"
#include "LinkedList.h"
#include "garfo.h"
#include "defs.h"

/******************************************************************************
 * OutputFile()
 *
 * Arguments: nome - contant string with input file name to be changed
 *        
 * Returns: Output file in write mode as a FILE *
 * Side-Effects: none
 *
 * Description: Função para abrir ficheiro com terminação term assumindo que term começa com .
 *
 *****************************************************************************/

FILE *OutputFile(const char *nome, const char *term){
  char *file, *aux;
  FILE *out = NULL;

  file = (char *) malloc(sizeof(char) * (strlen(nome) + strlen(".paths") + 1));
  if (file == NULL){
    exit(-1);
  }

  strcpy(file, nome);
  aux = strrchr(file, '.');
  if(aux == NULL){   
    exit(-420);
  }
  if(strcmp(aux, term) != 0){
    exit(-420);
  }

  strcpy(aux, ".paths");

  out = AbreFicheiro(file, "w");
  free(file);
  return out;
}



/******************************************************************************
 * sub_1
 *
 * Arguments:  word - Palavra para referência de tamanho
 *             p - Struct de dicionário
 *             out - ficheiro onde dar print do output
 *           
 * Returns: (none)
 * Side-Effects: none
 *
 * Description: Modo 1 de primeira entrega de projeto
 *
 *****************************************************************************/
void sub_1(char *word, dic *p, FILE* out){
  int i = strlen(word), j;

  j = p->tamanho[i-1];

  fprintf(out, "%s %d\n", word, j);

  return;  
}
/******************************************************************************
 * bis
 *
 * Arguments:  key - palavra que se procura
 *             arr - array de procura
 *             nmemb - número de membros do arr
 *           
 * Returns: apontador para a posição da palavra no arr 
 * Side-Effects: none
 *
 * Description: Binary search 
 *
 *****************************************************************************/
char **bis (char *key, char **arr, int nmemb){
  char *word = (char *) malloc((strlen(key) + 1) * sizeof(char));
  int i, l = 0, u = nmemb -1, j = (u + l)/2;
  
  if (word == NULL)
    exit(-69);
  while ((i = strcmp(key, arr[j])) != 0){
    if (l>= u){
      free(word);
      return NULL;
    }
    if (i > 0){
      l = j + 1;
      j = (u + l)/2;
      continue;
    }
    else{
      u = j - 1;
      j = (u + l)/2;
      continue;
    }

  }
  free(word);
  return &arr[j];
}

int compar(const void * a, const void *b){  
  return strcmp(* (char * const *) a, * (char * const *) b);
}
/******************************************************************************
 * sub_2
 *
 * Arguments:  word - Palavra para referência de tamanho
 *             p - Struct de dicionário
 *             out - ficheiro onde dar print do output
 *           
 * Returns: (none)
 * Side-Effects: none
 *
 * Description: Modo 1 de primeira entrega de projeto
 *
 *****************************************************************************/
void sub_2(char *word, dic *p, FILE* out){
  int i = strlen(word) -1, j;
  char **found;

  found = bis(word, p->palavras[i], p->tamanho[i]);
  if (found == NULL)
    exit(-1);

  j = (found - p->palavras[i]);

  fprintf(out, "%s %d\n", word, j);

  return;  
}
/******************************************************************************
 * sort
 *
 * Arguments:  pp - dicionario a ser ordenado
 *             size - tamanho a ser ordenado
 *             
 *           
 * Returns: apontador para a posição da palavra no arr 
 * Side-Effects: none
 *
 * Description: Binary search 
 *
 *****************************************************************************/
void sort (dic *pp, int size){
    static int j = 0;
    static int messi[MAX_STR];
    while(j < MAX_STR){
      messi[j] = 0;
      j++;
    } 
  if(messi[size - 1] == 0){

    qsort(pp->palavras[size -1], (pp->tamanho[size -1]), sizeof(char*), compar);
    messi[size -1] = 1;
    
  }
}
/******************************************************************************
 *checkpp
 *
 * Arguments: word1 - primeira palavra do problema
 *            word2 - segunda palavra do problema
 *            modo - modo de jogo do problema
 *            pp - ponteiro para dic de referncia
 * 
 * Returns: -1 if wrong 0 if right
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/
int checkpp(char *word1, char *word2, int modo, dic *pp){
  
  if (modo <=0) return -1;

  else if (strlen(word1) > pp->bigboi) return -1;
  
  else if (strlen(word1) != strlen(word2)) return -1;

  else if(pp->tamanho[strlen(word1)-1] <= 0) return -1;

  else if ((bis(word1, pp->palavras[strlen(word1) -1], pp->tamanho[strlen(word1) -1]) == NULL) || (bis(word2, pp->palavras[strlen(word1) -1], pp->tamanho[strlen(word1) -1]) == NULL)) return -1;

  return 0;
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
int test(Item w1, Item w2){
    int i=0, count=0;
    for (i=0;i<=strlen((char*) w1);i++){
        if(((char*) w1)[i]!=((char*)w2)[i]){
            count++;
        }
    }
    count= count * count;
    return count;
}
/******************************************************************************
 * main()
 *
 * Arguments: argc - counter of number of arguments in call
 *            argv - pointer to array of strings holding the arguments
 * Returns: (none)
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/

int main ( int argc, char **argv )
{
  int modo = 0,modo2=0,size=0, fr = 0, dj = 0;
  int o = 0, a = 0,*tw = NULL, *wt = NULL, j = 0;
  dic *st_palavras = (dic *) malloc(sizeof(dic));
  FILE *p = NULL, *d = NULL, *out = NULL;
  char *word1, *word2;
  garfo *faca = NULL;
  if (st_palavras == NULL){
    exit(-1);
  }
  if ( argc < 2 ) {
    exit ( -69 );
  }

  
  d = AbreFicheiro(argv[1], "r");
  p = AbreFicheiro(argv[2], "r");
  out = OutputFile(argv[2], ".pals");

  AlocaTabelaPalavras ( d, st_palavras );
  word1 = (char *) malloc(sizeof(char) * (MAX_STR + 1));
  word2 = (char *) malloc(sizeof(char) * (MAX_STR+ 1));
  PreencheTabelaPalavras ( d, st_palavras );
  while(fscanf(p,"%s %s %d", word1, word2, &modo) == 3){
    sort(st_palavras, strlen(word1));
    if (checkpp(word1, word2, modo, st_palavras) == -1){  /* verificação de validade de problema */
      fprintf(out, "%s %d\n%s \n\n", word1, -1, word2);
      continue;
    }

    if ((j = test((Item) word1, (Item ) word2)) <= 1){    /* Caso de palavras iguais ou a apenas uma permutação de distância */
      fprintf(out, "%s %d\n%s \n\n", word1, j, word2);
      continue;
    }
    fr = 1;
    if(modo2==0 || size==0){  /* Caso seja o primeiro problema*/
      faca=garfointit(st_palavras->tamanho[strlen(word1)-1]);
      putingarfo(faca,(Item*) st_palavras->palavras[strlen(word1)-1], modo * modo,test);
      o = bis(word1, st_palavras->palavras[strlen(word1) -1], st_palavras->tamanho[strlen(word1) -1]) - st_palavras->palavras[strlen(word1) -1];
      a = bis(word2, st_palavras->palavras[strlen(word1) -1], st_palavras->tamanho[strlen(word1) -1]) - st_palavras->palavras[strlen(word1) -1];
      tw = (int *) malloc(sizeof(int)*(faca->nv));
      wt = (int *) malloc(sizeof(int)*(faca->nv));

      if(tw==NULL || wt==NULL){
        exit(-1);
      }
      modo2=modo;
      size=strlen(word1);

    }
    else if (strlen(word1)!= size){ /* Tamanho diferente => grafo novo sempre */
      facagarfo(faca);
      free(tw);
      free(wt);
      faca=garfointit(st_palavras->tamanho[strlen(word1)-1]);
      putingarfo(faca,(Item*) st_palavras->palavras[strlen(word1)-1], modo * modo,test);
      o = bis(word1, st_palavras->palavras[strlen(word1) -1], st_palavras->tamanho[strlen(word1) -1]) - st_palavras->palavras[strlen(word1) -1];
      a = bis(word2, st_palavras->palavras[strlen(word1) -1], st_palavras->tamanho[strlen(word1) -1]) - st_palavras->palavras[strlen(word1) -1];
      tw = (int *) malloc(sizeof(int)*(faca->nv));
      wt = (int *) malloc(sizeof(int)*(faca->nv));

      if(tw==NULL || wt==NULL){
        exit(-1);
      }
      modo2=modo;
      size=strlen(word1);
    }
    else if (modo == modo2 ){ /* Pode se manter o grafo. Temos que fazer dikstra? */
      if ((strcmp(word1, st_palavras->palavras[strlen(word1) - 1][o]) == 0) && (strcmp(word2, st_palavras->palavras[strlen(word1) - 1][a]) == 0))
        dj =1;
      else if (strcmp(word2, st_palavras->palavras[strlen(word1) - 1][a]) == 0 ){
        o = bis(word1, st_palavras->palavras[strlen(word1) -1], st_palavras->tamanho[strlen(word1) -1]) - st_palavras->palavras[strlen(word1) -1];
        if (tw[o] != -1 && wt[o] < modo * modo)
          dj = 1;
      }
      else if (strcmp(word1, st_palavras->palavras[strlen(word1) - 1][a]) == 0 ){
        o = bis(word2, st_palavras->palavras[strlen(word1) -1], st_palavras->tamanho[strlen(word1) -1]) - st_palavras->palavras[strlen(word1) -1];
        if (tw[o] != -1 && wt[o] < modo * modo)
          dj = 1;
        j = a;
        a = o;
        o = j;
      }
      else{
      o = bis(word1, st_palavras->palavras[strlen(word1) -1], st_palavras->tamanho[strlen(word1) -1]) - st_palavras->palavras[strlen(word1) -1];
      a = bis(word2, st_palavras->palavras[strlen(word1) -1], st_palavras->tamanho[strlen(word1) -1]) - st_palavras->palavras[strlen(word1) -1];
      }
    } /* Caso seja um problema com palavras de novo tamanho (=> novo grafo) */
    else if(modo < modo2){ /* Trim do grafo */
      faca = colhergarfo(faca, modo * modo);
      a = bis(word1, st_palavras->palavras[strlen(word1) -1], st_palavras->tamanho[strlen(word1) -1]) - st_palavras->palavras[strlen(word1) -1];
      o = bis(word2, st_palavras->palavras[strlen(word1) -1], st_palavras->tamanho[strlen(word1) -1]) - st_palavras->palavras[strlen(word1) -1];
    }

    else{ /* Novo grafo */
      facagarfo(faca);
      free(tw);
      free(wt);
      faca = garfointit(st_palavras->tamanho[strlen(word1)-1]);
      putingarfo(faca,(Item*) st_palavras->palavras[strlen(word1)-1], modo * modo,test);
      o = bis(word1, st_palavras->palavras[strlen(word1) -1], st_palavras->tamanho[strlen(word1) -1]) - st_palavras->palavras[strlen(word1) -1];
      a = bis(word2, st_palavras->palavras[strlen(word1) -1], st_palavras->tamanho[strlen(word1) -1]) - st_palavras->palavras[strlen(word1) -1];
      tw = (int *) malloc(sizeof(int)*(faca->nv));
      wt = (int *) malloc(sizeof(int)*(faca->nv));

      if(tw==NULL || wt==NULL){
        exit(-1);
      }
      modo2=modo;
      size=strlen(word1);
    }
    
  

    if (dj == 0)  /* aplica dijkstra se necessário */
      djigja(faca, a, o, tw, wt, 1000000000);

    else /* reset da flag de dikstra se este não é necessário */
      dj = 0;
    /* for (o = 0; 0 < faca->nv - 1; o++){ */
      if(tw[o]!=-1){ /* Se há solução */
        fprintf(out, "%s %d\n", st_palavras->palavras[strlen(word1) - 1][o], wt[o]);
        for (j = tw[o]; j != tw[j] && tw[j] !=-1; j = tw[j]){
          fprintf(out,"%s\n", st_palavras->palavras[strlen(word1) -1][j]);
        }
      }
      else /* Se não há */
        fprintf(out, "%s %d\n", st_palavras->palavras[strlen(word1) - 1][o], tw[o]);
      fprintf(out, "%s\n\n", st_palavras->palavras[strlen(word1) -1][a]);
   /*  } */
    /* if (modo == 1){
      sub_1(word1, st_palavras, out);
      fprintf(out,"\n");
    }
    else if (modo == 2){
      
      sub_2(word1, st_palavras, out);
      sub_2(word2, st_palavras, out);
      fprintf(out, "\n");
      
      continue;
    } */
    
  }
  if(fr == 1){ /* Se não há problemas que impliquem alocação, não se faz free */
    free(tw);
    free(wt);
    facagarfo(faca);
  }
  FreeTabelaPalavras(st_palavras);
  free(st_palavras);
  free(word1);
  free(word2);
  fclose(d);
  fclose(p);
  fclose(out);
  
  return (0);
}

