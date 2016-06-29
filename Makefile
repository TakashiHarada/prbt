# rbtrie をつくる Makefile
#
VPATH = src include
CPPFLAGS = -I include
#CC = gcc -O3 -Wall -Wextra -lm
CC = gcc -g3 -Wall -Wextra -lm

#rbtrie: rbtrie.o openfile.o trie.o family.o decision_tree.o classify.o
rbtrie: main.o io.o
	gcc main.o io.o -o main

clean:
	rm *.o
