VPATH = ./libed/
objects = main.o BD.o BST.o FILEMANAGER.o ITEM.o LL.o RPN.o STACKLL.o extra.o WORD.o
CC = gcc
CFLAGS = -Wall -pedantic -ansi -std=c99 -g


ep2 : $(objects)
	$(CC) $(CFLAGS) $(objects) -o $@

main.o :        main.c extra.h BD.h LL.h RPN.h STACK.h
BD.o :          BD.c extra.h BD.h LL.h BST.h ITEM.h FILEMANAGER.h
BST.o :         BST.c extra.h BST.h
FILEMANAGER.o : FILEMANAGER.c extra.h FILEMANAGER.h BD.h LL.h BST.h ITEM.h
ITEM.o :        ITEM.c extra.h ITEM.h
LL.o :          LL.c extra.h LL.h
RPN.o :         RPN.c extra.h RPN.h STACK.h LL.h ITEM.h
STACKLL.o :     STACKLL.c STACK.h LL.h extra.h
extra.o :       extra.c extra.h ITEM.h LL.h
WORD.o:         WORD.c extra.h WORD.h LL.h ITEM.h

.PHONY : clean
clean : 
	rm -f $(objects) ep2 ep2.exe

.PHONY : moreclean
moreclean : clean
	rm -f \#*\# *~
