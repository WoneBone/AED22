# Projeto 1ª submissão
#
# To compile prog:
#    make
# To run tests:
#    make t
# NÃO ESQUECER DE MUDAR -G PARA -O3
# NOTE:
# In case of trouble with the shell for loop, GNU Make has 'foreach':
#	$(foreach file,$(FILES),./labconn $(file);)
# https://stackoverflow.com/questions/1490949/how-to-write-loop-in-a-makefile
#----------------------------------------------------------------------

CC=gcc
CFLAGS=-g -Wall -std=c99 


Wordmutations: main.o LinkedList.o dichandl.o garfo.o
	$(CC) $(CFLAGS) -o wrdmttns main.o dichandl.o

main.o: main.c dichandl.h garfo.h LinkedList.h defs.h
	$(CC) -c $(CFLAGS) main.c

LinkedList.o: LinkedList.c LinkedList.h defs.h
	$(CC) -c $(CFLAGS) LinkedList.c

dichandl.o: dichandl.c dichandl.h
	$(CC) -c $(CFLAGS) dichandl.c

garfo.o: garfo.c garfo.h LinkedList.h defs.h
	$(CC) -c $(CFLAGS) garfo.c

clean::
	rm -f *.o core a.out Wordmutations *~

