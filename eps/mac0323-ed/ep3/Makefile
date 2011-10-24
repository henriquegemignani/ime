VPATH = ./lib/
objects = main.o compress.o decompress.o trie.o LL.o 
CC = gcc
CFLAGS = -Wall -pedantic -ansi

ep3 : $(objects)
	$(CC) $(CFLAGS) $(objects) -o $@   

.PHONY : clean
clean :
	rm $(objects) ep3



compress.o: compress.c lib/common.h lib/trie.h
decompress.o: decompress.c lib/common.h lib/LL.h
main.o: main.c lib/common.h
LL.o: lib/LL.c lib/LL.h lib/common.h
trie.o: lib/trie.c lib/trie.h lib/common.h
