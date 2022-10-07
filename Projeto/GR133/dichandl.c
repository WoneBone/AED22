#include "dichandl.h"

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

void AlocaTabelaPalavras ( FILE *f, dic *t)
{
  char *palavra;
  int i, l,j;

  t->n_total_palavras = 0;
  t->n_dist_palavras = 0;
  t->bigboi = 0;
  for (i = 0; i < MAX_STR; i++) 
    t->tamanho[i] = 0;

  while ( ( palavra = LePalavra ( f ) ) != NULL ) {
    t->n_total_palavras++;
    l = strlen( palavra );
    if ( l > t->bigboi )
      t->bigboi = l;
    t->tamanho[l - 1]++;
  }
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
  rewind(f);
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

void PreencheTabelaPalavras ( FILE *f, dic *t )
{
  int n, i, l;
  char *palavra;
  int shmol[t->bigboi];

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
  rewind(f);
  return;
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

void FreeTabelaPalavras ( dic *t)
{
    int i, j;
    for(i = 0; i < t->bigboi; i++){
        for(j = 0; j < t->tamanho[i]; j++) 
            free(t->palavras[i][j]);
        free(t->palavras[i]);
    }
    free(t->palavras);
  return;
}