#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_STR 100

typedef struct dic {
  int  n_total_palavras;	/* total number of words */
  int  n_dist_palavras;		/* number of distinct words*/
  char ***palavras;		/* Table of strings for words "palavras"*/
  int tamanho[MAX_STR]; /*Table of integers with the amont of words for each size i "tamanho"*/
  int bigboi; /*Biggest word "bigboi"*/
} dic;

char *LePalavra ( FILE * f );
FILE *AbreFicheiro ( char *nome, char *mode );
void AlocaTabelaPalavras ( FILE *f, dic *t);
int NovaPalavra ( char *palavra, dic *t );
void PreencheTabelaPalavras ( FILE *f, dic *t );