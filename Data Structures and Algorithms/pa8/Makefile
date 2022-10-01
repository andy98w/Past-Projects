#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 8
#
#  make                     makes WordFrequency
#  make DictionaryClient    makes DictionaryClient
#  make clean               removes all binaries
#  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg.txt
#  make DictionaryCheck     runs DictionaryClient under valgrind
#------------------------------------------------------------------------------

CC = g++
CFLAGS = -std=c++17 -Wall

all: WordFrequency Order DictionaryTest

WordFrequencyCheck: WordFrequency
	valgrind ./WordFrequency

DictionaryCheck: Dictionary
	valgrind ./Dictionary

WordFrequency: WordFrequency.o Dictionary.o
	$(CC) $(CFLAGS) -o WordFrequency WordFrequency.o Dictionary.o

Order: Order.o Dictionary.o
	$(CC) $(CFLAGS) -o Order Order.o Dictionary.o

DictionaryTest: DictionaryTest.o Dictionary.o
	$(CC) $(CFLAGS) -o DictionaryTest DictionaryTest.o Dictionary.o

DictionaryTest.o: DictionaryTest.cpp
	$(CC) $(CFLAGS) -c DictionaryTest.cpp

WordFrequency.o: WordFrequency.cpp
	$(CC) $(CFLAGS) -c WordFrequency.cpp

Order.o: Order.cpp
	$(CC) $(CFLAGS) -c Order.cpp

Dictionary.o: Dictionary.h Dictionary.cpp
	$(CC) $(CFLAGS) -c Dictionary.cpp

clean:
	rm -f *.o WordFrequency Order DictionaryTest
