CC = gcc
CFLAGS = -Wall -pedantic -ansi -g -O3

all: fw
	make fw

fw: fw.o hashtable.o
	$(CC) $(CFLAGS) -o fw fw.o hashtable.o

fw.o: fw.c
	$(CC) $(CFLAGS) -c -o fw.o fw.c

hashtable.o: hashtable.c
	$(CC) $(CFLAGS) -c -o hashtable.o hashtable.c

clean:
	rm -f *.o

