# rbtrie をつくる Makefile
#
VPATH = src include
CPPFLAGS = -I include
#CC = gcc -O3 -Wall -Wextra -lm
#CC = cc -g3 -Wall -Wextra -lm
CC = gcc -g3 -Wall -Wextra -lm

#rbtrie: rbtrie.o openfile.o trie.o family.o decision_tree.o classify.o
main: main.o io.o prbt.o rbt.o classify.o
	gcc main.o io.o prbt.o rbt.o classify.o -o main

clean:
	rm *.o
