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
#define MAX_STR 100

typedef struct dic {
  int  n_total_palavras;	/* total number of words */
  int  n_dist_palavras;		/* number of distinct words*/
  char ***palavras;		/* Table of strings for words "palavras"*/
  int tamanho[MAX_STR]; /*Table of integers with the amont of words for each size i "tamanho"*/
  int bigboi; /*Biggest word "bigboi"*/
} dic;


/******************************************************************************
 * LePalavra()
 *
 * Arguments: f - pointer to file where word will be read
 * Returns: pointer to word just read
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/

char *LePalavra ( FILE * f )
{
  static char palavra[MAX_STR];
  /* It is assumed that the words present in the text files do not exceed
     100 characters in length  */
  /* Note that the variable palavra is declared as "static". */
  if ( fscanf ( f, "%s", palavra ) ==1 )
    return (palavra);
  else
    return ((char *) NULL);
}


/******************************************************************************
 * AbreFicheiro()
 *
 * Arguments: nome - pointer to string holding name of file to open
 *            mode - pointer to string holding mode to use for opening file
 * Returns: pointer to opened file
 * Side-Effects: exits if given file cannot be opened with given mode
 *
 * Description:
 *
 *****************************************************************************/

FILE *AbreFicheiro ( char *nome, char *mode )
{
  FILE *f;
  f = fopen ( nome, mode );
  if ( f == NULL ) {
    fprintf ( stderr, "ERROR: It is not possible to open file %s!\n", nome );
    exit ( 1 );
    /* Error messages are sent to the stderr channel.
       Use an exit number different from 0 (zero) in case of error.*/
  }
  return (f);
}


/******************************************************************************
 * AlocaTabelaPalavras()
 *
 * Arguments: ficheiro - pointer to string holding name of file to open
 *            dic - pointer to structure where information will be saved
 * Returns: (none)
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/

void AlocaTabelaPalavras ( char *ficheiro, dic *t)
{
  FILE *f;
  char *palavra;
  int i, l,j;

  t->n_total_palavras = 0;
  t->n_dist_palavras = 0;
  t->bigboi = 0;
  for (i = 0; i < MAX_STR; i++) 
    t->tamanho[i] = 0;

  f = AbreFicheiro ( ficheiro, "r" );
  while ( ( palavra = LePalavra ( f ) ) != NULL ) {
    t->n_total_palavras++;
    l = strlen( palavra );
    if ( l > t->bigboi )
      t->bigboi = l;
    t->tamanho[l - 1]++;
  }
  fclose ( f );
  printf ( "Words count: %d\n", t->n_total_palavras );
  t->palavras =(char***) malloc(sizeof(char**) * t->bigboi); //alocaçao de nº tabelas para cada tamanho
  if ( t->palavras == NULL ) {
    fprintf ( stderr, "ERROR: not enough memory available!\n" );
    exit ( 2 );
  }
  for(i = 0; i < t->bigboi; i++){
    t->palavras[i] = (char**) malloc(sizeof(char*) * t->tamanho[i]); //alocaçao de nº de palavras para cada tamanho
    if ( t->palavras[i] == NULL ) {
      fprintf ( stderr, "ERROR: not enough memory available!\n" );
      exit ( 2 );
    }
    for(j = 0; j < t->tamanho[i]; j++){ //alocaçao de tamanho para cada palavra
      t->palavras[i][j] = (char*) malloc(sizeof(char)*(i + 2));
      if ( t->palavras[i][j] == NULL ) {
        fprintf ( stderr, "ERROR: not enough memory available!\n" );
        exit ( 2 );
      }
      t->palavras[i][j][0] = '\0';
    }
  }
  return;
}


/******************************************************************************
 * NovaPalavra()
 *
 * Arguments: palavra - pointer to string holding a word
 *            dic - pointer to structure where run information is kept
 * Returns: (none)
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/

int NovaPalavra ( char *palavra, dic *t )
{
  int i = 0, l = strlen(palavra);
  /* This function searches for a word in the table.
     if the word is not found returns -1,
     Otherwise returns the position of the word in the table */
  while ( ( t->palavras[l -1][i][0] != '\0' ) && i < t->n_total_palavras ) {
    if ( strcmp ( t->palavras[l - 1][i], palavra ) == 0 )
      return (i);
    i++;
  }
  return (-1);
}


/******************************************************************************
 * PreencheTabelaPalavras()
 *
 * Arguments: ficheiro - pointer to string holding name of file to open
 *            dic - pointer to structure where information will be saved
 * Returns: (none)
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/

void PreencheTabelaPalavras ( char *ficheiro, dic *t )
{
  FILE *f;
  int n, i, l;
  char *palavra;
  int shmol[t->bigboi];

  f = AbreFicheiro ( ficheiro, "r" );
  for(i = 0; i < t->bigboi; i++){
    shmol[i] = t->tamanho[i];
  }
  while ( ( palavra = LePalavra ( f ) ) != NULL ) {
    if ( ( n = NovaPalavra ( palavra, t) ) == -1 )	{
      l = strlen(palavra);
      strcpy ( t->palavras[l-1][shmol[l-1]-1], palavra );
      shmol[l-1]--;
    }
  }
  fclose ( f );
  return;
}


/******************************************************************************
 * EscreveFicheiro()
 *
 * Arguments: ficheiro - pointer to string holding name of file to save
 *            dic - pointer to structure where information is kept
 * Returns: (none)
 * Side-Effects: none
 *
 * Description:
 *
 *****************************************************************************/

void EscreveFicheiro ( char *ficheiro, dic *t )
{
  FILE *f;
  char *nome;
  int i = 0;

  nome = (char *) malloc(sizeof(char) * (strlen(ficheiro) + strlen(".palavras") +1));
  if ( nome == NULL ) {
    fprintf ( stderr, "ERROr: not enough memory available!\n" );
    exit ( 5 );
  }
  strcpy ( nome, ficheiro );
  strcat ( nome, ".palavras" );
  f = AbreFicheiro ( nome, "w" );
  for ( i = 0; i < t->n_dist_palavras; i++ ) {
    //fprintf ( f, "%d: %s\n", t->ocorrencias[i], t->palavras[i] );
  }
  printf ( "Count of distinct words: %d\n", t->n_dist_palavras );
  fclose ( f );
  return;
}

/******************************************************************************
 * main()
 *
 * Arguments:  argv - pointer to array of strings holding the arguments
 *           
 * Returns: (none)
 * Side-Effects: none
 *
 * Description:reads the file .pals in argv[2] and determines what to do with that information
 *
 *****************************************************************************/
void sub_1(char*ficheiro, dic *t){
  FILE *p;
  char word_1[t->bigboi], word_2[t->bigboi];
  int n=0,grower=0;
  
  p = AbreFicheiro(ficheiro, "r");//abertura de .pals

  while (fscanf(p,"%s %s %d",word_1,word_2,&n)!= EOF){;
  
    if (strlen(word_1)!=strlen(word_2)){
      printf("palavras duvidosas\n");
    }
    if(n==1){
      grower=strlen(word_1)+2;
    
      printf("Numero de palavras do mesmo tamanho:%d",t->tamanho[(grower-1)]);
    }
  } 

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
  int i;
  dic st_palavras;

  if ( argc < 2 ) {
    fprintf ( stderr, "ERROR: missing filename in argument!\n" );
    exit ( 6 );
  }

  AlocaTabelaPalavras ( argv[1], &st_palavras );
  PreencheTabelaPalavras ( argv[1],&st_palavras );
  EscreveFicheiro ( argv[1], &st_palavras );
  sub_1 (argv[2],&st_palavras);
  return (0);
}






/* 
  Nunca abrir ficheiros 2 vezes
  Alocação de memória excessíva
  Sem frees, mas não é relevante no ambito da aula
  Optimizar procura 
*/
