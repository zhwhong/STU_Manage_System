# Makefile for STU

SHELL = /bin/bash

CXX = g++
CXXFLAGS = -g -Wno-deprecated --std=c++11
BIN = main

OBJECTS = main.o operation.o

all: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(BIN) $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $^

.PHONY: clean
clean:
	-rm -f $(BIN) *.o
