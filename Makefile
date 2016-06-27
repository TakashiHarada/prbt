# Makefile for Pointed Run-Based Trie 
# for Mac
#g++-4.9 -g3 -Wall -Wextra -lm -I include -c -o rbtrie.o src/rbtrie.cpp
#g++-4.9 -g3 -Wall -Wextra -lm -I include -c -o trie.o src/trie.cpp
#g++-4.9 -g3 -Wall -Wextra -lm -I include -c -o openfile.o src/openfile.cpp
#g++-4.9 -g3 -Wall -Wextra -lm rbtrie.o trie.o openfile.o -o rbtrie
#
# CC を CXX へ変更
# #
VPATH = src include
CPPFLAGS = -I include
#INCLUDE = -I include

#CXX = g++ -O3 -Wall -Wextra -pedantic -std=c++0x -lm  # O は最適化用 
#CXX = g++-4.9 -O3 -Wall -Wextra -pedantic -std=c++0x -lm  # for mac

CXX = g++ -g3 -Wall -Wextra -pedantic -std=c++0x -lm 
#CXX = g++-4.9 -g3 -Wall -Wextra -pedantic -std=c++0x -lm  # g はデバッグ用

rbtrie: rbt.o main.o openfile.o classify.o
#rbtrie: rbtrie.o openfile.o trie.o classify.o check.o measure.o
	g++ rbt.o main.o openfile.o classify.o -o main
#g++ main.o openfile.o trie.o ptrie.o family.o dtree.o classify.o check.o measure.o -o main

clean:
	rm *.o
