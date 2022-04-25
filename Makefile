CC = gcc
CFLAGS = -Wall -pedantic -ansi -g -Og

all: htable
	make htable

htable: htable.o htree.o list.o
	$(CC) $(CFLAGS) -o htable htable.o htree.o list.o

htable.o: htable.c
	$(CC) $(CFLAGS) -c -o htable.o htable.c

htree.o: htree.c
	$(CC) $(CFLAGS) -c -o htree.o htree.c

list.o: list.c
	$(CC) $(CFLAGS) -c -o list.o list.c

tests: htreeTests.o htree.o
	$(CC) $(CFLAGS) -o htreeTests htreeTests.o htree.o
	./htreeTests

htreeTests.o: htreeTests.c
	$(CC) $(CFLAGS) -c -o htreeTests.o htreeTests.c

clean:
	rm -f *.o

server:
	ssh acheun29@unix1.csc.calpoly.edu

upload:
	scp -r ../csc357-lab03 acheun29@unix1.csc.calpoly.edu:csc357

download:
	scp -r acheun29@unix1.csc.calpoly.edu:csc357/csc357-lab03 /Users/andrewcheung/Documents/Cal\ Poly\ Stuff/csc357

