/******************************************************************************
* (c) 2022 AED Team
* Last modified: lms 2022-10-20
*
* NAME
*   ev2el
*
* DESCRIPTION
*   Main program for lab guide
*   - read edge vector,
*   - write edge lists
*
* COMMENTS
*   Code for internal testing - do not distribute
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"LinkedList.h"
#include"queue.h"


typedef struct _twint {
  int n2;
  int wt;
} twint;


typedef struct _nodeS {
  twint node;

} NodeS;



/******************************************************************************
* usage ()
*
* Arguments: nomeProg - name of executable
* Returns: (void)
* Side-Effects: none
*
* Description: message function when arguments are missing
*****************************************************************************/

void usage(char *nomeProg)
{
  printf("Usage: %s filename\n", nomeProg);
  printf("  reads graph edges vector, writes edge lists\n");
  exit(1);
}


/******************************************************************************
* memoryError ()
*
* Arguments: msg - message to output to stderr
* Returns: (void)
* Side-Effects: none
*
* Description: exit with error message to stderr
*****************************************************************************/

void memoryError(char *msg) {

  fprintf(stderr, "Error during memory reserve attempt.\n");
  fprintf(stderr, "Msg: %s\n",msg);
  fprintf(stderr, "Exit Program due to unmanaged error.\n");

  exit(1);
}



/******************************************************************************
* doBFS ()
*
* Arguments: listv - data structure for graph list of adjacencies
*            sn - starting node
*            nv - number of nodes in graph
* Returns: (void)
* Side-Effects: none
*
* Description: does a BFS on the graph described by the list of adjacencies
*              reachable through listv and prints nodes as it finds them
**********************************  NodeS *next;*******************************************/

void doBFS(LinkedList **listv, int sn, int nv) {
   int numInqueue = 0;
  int *inqueue;
  int *Ns;
  LinkedList *lp;
  twint *pint;
  Queue *BFSqueue;

  inqueue = (int*) calloc(nv , sizeof(int));
  if (inqueue == ((int*)NULL))
    memoryError("Cannot allocate memory for inqueue nodes.");

 /*  fakeNodes = (NodeS*) alloc(nv * sizeof(NodeS));
  if (fakeNodes == ((NodeS*)NULL))
    memoryError("Cannot allocate memory for fake nodes.");
  for (ni = 0; ni < nv; ni++)
    fakeNodes[ni].node = ni;  */

  BFSqueue = newQueue(nv);

  /* put starting node in queue */
  insertQueue(BFSqueue, (Item) &sn);
  inqueue[sn] = 1;
  numInqueue++;
  for ( ; numInqueue < nv; ) {
    /* get first element in queue, tells us node being visited */
    Ns = getfirstQueue(BFSqueue);
    if (Ns == ((int*) NULL))
      break;
    fprintf(stdout, "%d ", *Ns);
    /* process that node's adjacency list */
    lp = listv[*Ns];
    while (lp != NULL) {
      /* for every element in the adjacency list */
      /* check if it has been queued; if not, put it in the queue */
      /* and print it to stdout */

      pint = getItemLinkedList(lp);
      if(!inqueue[pint->n2]){
        insertQueue(BFSqueue, (Item) &(pint->n2));
        numInqueue++;
        inqueue[pint->n2]++;
      }

      lp = getNextNodeLinkedList(lp);
    }

  }
  Ns = getfirstQueue(BFSqueue);
  while (Ns != ((int*) NULL)){
    fprintf(stdout, "%d ", *Ns);
    Ns = getfirstQueue(BFSqueue);
  }
  
  fprintf(stdout, "\n");
  freeQueue(BFSqueue, NULL);
  free(inqueue);
  return;
}


/******************************************************************************
* main ()
*
* Arguments: argc - number of command-line arguments
*            argv - table of pointers for string arguments
* Returns: int status
* Side-Effects: none
*
* Description: main Program
*****************************************************************************/

int main(int argc, char *argv[])
{
  int     i, k;
  int     nv, ne;     /* V and E counts */
  int     n1, n2, wt;
  int     sn;
  char    extIn[] = ".edge";
  char    extOut[] = ".ladj";
  char    *nomeFicheiroIn, *nomeFicheiroOut;
  twint   *pint1, *pint2;
  LinkedList **listv, *lp;
  FILE    *fpIn,*fpOut;

  if(argc < 2)
    usage(argv[0]);

  nomeFicheiroIn = argv[1];

  nomeFicheiroOut =
    (char *) malloc((strlen(nomeFicheiroIn)-strlen(extIn)+strlen(extOut)+1) *
                    sizeof(char));
  if(nomeFicheiroOut == NULL)
    memoryError("Memory allocation for nomeFicheiroOut in main" );

  strcpy(nomeFicheiroOut, nomeFicheiroIn);
  nomeFicheiroOut[strlen(nomeFicheiroIn)-strlen(extIn)] = '\0';
  strcat(nomeFicheiroOut, extOut);

  /* open input file */
  fpIn  = fopen(nomeFicheiroIn,"r");
  if(fpIn == NULL) {
    printf("ERROR cannot read input file %s\n", nomeFicheiroIn);
    exit(2);
  }

  /* read input file, read nv and ne */
  k = fscanf(fpIn, "%d", &nv);
  if(k < 1) {
    printf("ERROR cannot read V number from input file %s\n",
           nomeFicheiroIn);
    exit(2);
  }
  k = fscanf(fpIn, "%d", &ne);
  if(k < 1) {
    printf("ERROR cannot read E number from input file %s\n",
           nomeFicheiroIn);
    exit(2);
  }

  /* create vector for adjacency lists, one per node */
  listv = (LinkedList**) calloc(nv , sizeof (LinkedList*));
  if (listv == ((LinkedList**) NULL))
    memoryError("memory allocation for adjacency lists vector in main");

  /* read ne edges from file, each triple n1, n2, weight */
  for(i = 0; i < ne; i++) {
    k = fscanf(fpIn, "%d %d %d", &n1, &n2, &wt);
    if(k < 3) {
      printf("ERROR cannot read edge triple from input file %s\n",
             nomeFicheiroIn);
      exit(2);
    }
    /*  DEBUG
        printf("%d %d %d\n", n1, n2, wt); */
    pint1 = (twint *) malloc(sizeof(twint));
    if (pint1 == ((twint*) NULL)) {
      memoryError("memory allocation for edge structure in main");
    }
    pint2 = (twint *) malloc(sizeof(twint));
    if (pint2 == ((twint*) NULL)) {
      memoryError("memory allocation for edge structure in main");
    }
    pint1->n2 = n2;
    pint1->wt = wt;
    pint2->n2 = n1;
    pint2->wt = wt;
    if (listv[n1] == NULL){
      listv[n1] = initLinkedList();
    }
    if (listv[n2] == NULL){
      listv[n2] = initLinkedList();
    }

    /*********** INSERT EDGE STRUCTURES IN EACH APPROPRIATE LIST ***********/

    listv[n1] = insertUnsortedLinkedList(listv[n1], pint1);
    listv[n2] = insertUnsortedLinkedList(listv[n2], pint2);
  }


  /* Compute de degree of every node and the average edge density */
  ne = 0;
  for (i = 0; i < nv; i++){
    lp = listv[i];
    k=0;
    while(lp!= NULL){
      ++k;
      lp=getNextNodeLinkedList(lp);
    }
    printf("%d tem degree %d \n", i, k);
    ne +=k;
  }
  printf("%f is avg\n", (float) ne/nv);
  ne /= 2;

  /* open output file */
  fpOut = fopen (nomeFicheiroOut, "w");
  if(fpOut == NULL) {
    printf("ERROR cannot write output file %s\n", nomeFicheiroOut);
    exit(3);
  }

  /*  print out edge vectors (.ldaj file) */
  fprintf(fpOut, "%d\n", nv);
  for(i = 0; i < nv; i++) {
    lp = listv[i];
    while (lp != NULL) {
      pint1 = (twint *) getItemLinkedList(lp);
      lp = getNextNodeLinkedList(lp);
      /* print the node and the respective weight */
      fprintf(fpOut,"%d:%d ", pint1->n2, pint1->wt);
    }
    fprintf(fpOut, " -1\n");
  }

  /* -- close all open files -- */
  fclose(fpIn);
  fclose(fpOut);

  /****************** read path to find ************************************/
  fprintf(stdout,
          "Input node number to do a BFS from that node: ");
  fscanf(stdin, "%d", &sn);
  fprintf(stdout, "\n");
  if (sn >= nv) {
    fprintf(stderr,
            "node number outside of range of nodes in graph. Exiting.\n");
    exit(1);
  }

  /************ add code to do a BFS in graph from node en to node sn *********/
  doBFS(listv, sn, nv);
  for(i =  0; i < nv; i++)
    freeLinkedList(listv[i], free);
  free(listv);
  free(nomeFicheiroOut);
  

  exit(0);
}
