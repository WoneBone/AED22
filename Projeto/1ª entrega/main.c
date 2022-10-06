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
    fprintf(stderr, "ERRO DE ALOCAÇÃO DE MEMÓRIA");
    exit(-1);
  }

  strcpy(file, nome);
  aux = strrchr(file, '.');

  if(strcmp(aux, term) != 0){
    fprintf(stderr, "Formato de ficheiro incorreto");
    exit(-69);
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

  fprintf(out, "%s\t%d", word, j);

  return;  
}

char **bis (char *key, char **arr, int nmemb){
  char *word = (char *) malloc((strlen(key) + 1) * sizeof(char));
  int i,k = 2, j = nmemb/k;
  
  if (word == NULL)
    exit(-69);
  while (i = strcmp(key, arr[j]) != 0){
    k=k*2;
    printf("%d\n",j);
    if (i > 0)
      j = (j + nmemb/k)+1 ;
    else
      j = (j - nmemb/k)+1 ;
  }
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
  static int messi[MAX_STR + 1];
  char **found;

  if (messi[MAX_STR] != 1){
    for (j = 0; j < MAX_STR; j ++){
      messi[j] = 0;
    }
    messi[MAX_STR] = 1;
  } 
  if(messi[i] == 0){
    qsort(p->palavras[i], (p->tamanho[i]), sizeof(char*), compar);
    puts(p->palavras[i][0]);
    puts(p->palavras[i][3000]);
    messi[i] = 1;
  }

  found = bis(word, p->palavras[i], p->tamanho[i]);
  j = (found - p->palavras[i]);

  fprintf(out, "%s\t%d\n", word, j);

  return;  
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
    fprintf(stderr, "MEMORY ALOCATION ERROR");
    exit(-420);
  }
  if ( argc < 2 ) {
    fprintf ( stderr, "ERROR: missing filename in argument!\n" );
    exit ( 6 );
  }


  d = AbreFicheiro(argv[1], "r");
  p = AbreFicheiro(argv[2], "r");
  out = OutputFile(argv[2], ".pals");

  AlocaTabelaPalavras ( d, st_palavras );
  word1 = (char *) malloc(sizeof(char) * (st_palavras->bigboi + 1));
  word2 = (char *) malloc(sizeof(char) * (st_palavras->bigboi + 1));
  PreencheTabelaPalavras ( d, st_palavras );
  while(fscanf(p,"%s %s %d", word1, word2, &modo)== 3){

    if (modo == 1){
      sub_1(word1, st_palavras, out);
    }
    else if (modo == 2){
      sub_2(word1, st_palavras, out);
      sub_2(word2, st_palavras, out);
      
      continue;
    }
    else{
      fprintf(stdout, "Modo invalido \n\
              Skipped %s %s", word1, word2);
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
