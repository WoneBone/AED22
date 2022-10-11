/******************************************************************************
 *
 * File Name: palavras.c
 *	      (c) 2012 AED
 * Authors:    AED Team
 * Last modified:
 * Revision:  v2.0
 *
 * COMMENTS:    Version with no globals variables
 *		Passing structure for functions
 *		More compact test for EOF
 *
 *****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dichandl.h"

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

  file = (char *) malloc(sizeof(char) * (strlen(nome) + strlen(".stats") + 1));
  if (file == NULL){
    exit(-1);
  }

  strcpy(file, nome);
  aux = strrchr(file, '.');

  if(strcmp(aux, term) != 0){
    exit(-420);
  }

  strcpy(aux, ".stats");

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
  int i, l = 0, u = nmemb, j = (u + l)/2;
  
  if (word == NULL)
    exit(-69);
  while ((i = strcmp(key, arr[j])) != 0){
    if (l== u){
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
int sub_2(char *word, dic *p, FILE* out){
  int i = strlen(word) -1, j;
  char **found;

  found = bis(word, p->palavras[i], p->tamanho[i]);
  if (found == NULL)
    return -1;

  j = (found - p->palavras[i]);

  fprintf(out, "%s %d\n", word, j);

  return 0;  
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
  
  if (modo != 1 && modo != 2 && strlen(word1) > pp->bigboi) return -1;
  
  else if (strlen(word1) != strlen(word2)) return -1;

  else if ((bis(word1, pp->palavras[strlen(word1) -1], pp->tamanho[strlen(word1) -1]) == NULL) || (bis(word2, pp->palavras[strlen(word1) -1], pp->tamanho[strlen(word1) -1]) == NULL)) return -1;
  return 0;
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
  int modo = 0;
  dic *st_palavras = (dic *) malloc(sizeof(dic));
  FILE *p = NULL, *d = NULL, *out = NULL;
  char *word1, *word2;

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
  word1 = (char *) malloc(sizeof(char) * (st_palavras->bigboi + 1));
  word2 = (char *) malloc(sizeof(char) * (st_palavras->bigboi + 1));
  PreencheTabelaPalavras ( d, st_palavras );
  while(fscanf(p,"%s %s %d", word1, word2, &modo)== 3){
    sort(st_palavras, strlen(word1));
    if (checkpp(word1, word2, modo, st_palavras) == -1){
      fprintf(out, "%s %s %d \n \n", word1, word2, modo);
      continue;
    }
    if (modo == 1){
      sub_1(word1, st_palavras, out);
      fprintf(out,"\n");
    }
    else if (modo == 2){
      
      sub_2(word1, st_palavras, out);
      sub_2(word2, st_palavras, out);
      fprintf(out, "\n");
      
      continue;
    }
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






/* 
  Nunca abrir ficheiros 2 vezes
  Alocação de memória excessíva
  Sem frees, mas não é relevante no ambito da aula
  Optimizar procura 
*/
