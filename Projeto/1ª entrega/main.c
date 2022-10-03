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
void sub_1(char *word, dic p, FILE* out){
  int i = strlen(word), j;

  j = p.tamanho[i-1];

  fprintf(out, "%s\t%d", word, j);

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
  dic st_palavras;
  FILE *p = NULL, *d = NULL, *out = NULL;
  char *word1, *word2;

  if ( argc < 2 ) {
    fprintf ( stderr, "ERROR: missing filename in argument!\n" );
    exit ( 6 );
  }


  d = AbreFicheiro(argv[1], "r");
  p = AbreFicheiro(argv[2], "r");
  out = OutputFile(argv[2], ".pals");

  AlocaTabelaPalavras ( d, &st_palavras );
  word1 = (char *) malloc(sizeof(char) * st_palavras.bigboi);
  word2 = (char *) malloc(sizeof(char) * st_palavras.bigboi);
  PreencheTabelaPalavras ( d, &st_palavras );
  while(fscanf(p,"%s %s %d", word1, word2, &modo)== 3){

    if (modo == 1){
      sub_1(word1, st_palavras, out);
    }
    else if (modo == 2){
      //sub_2(word1, word2);
      continue;
    }
    else{
      fprintf(stdout, "Modo invalido \n\
              Skipped %s %s", word1, word2);
      continue;

    }
  }
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
