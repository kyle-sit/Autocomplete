# A simple makefile for CSE 100 P3

CC=g++
CXXFLAGS= -std=c++11 -g -Wall -gdwarf-3
LDFLAGS=-g

all: benchtrie util.o Tester TimsTester benchdict

benchdict: util.o DictionaryTrie.o DictionaryBST.o DictionaryHashtable.o

Tester: DictionaryHashtable.o DictionaryBST.o DictionaryTrie.o util.o

TimsTester: DictionaryTrie.o util.o DictionaryBST.o DictionaryHashtable.o

benchtrie: util.o DictionaryTrie.o DictionaryBST.o DictionaryHashtable.o 

DictionaryTrie.o: DictionaryTrie.hpp 

DictionaryBST.o: DictionaryBST.hpp

DictionaryHashtable.o: DictionaryHashtable.hpp

util.o: util.hpp

clean:
	rm -f Tester benchtrie *.o core* *~

