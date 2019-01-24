#Makefile 
CC=gcc
CXX=g++
CFLAGS=-I. -lpthread -Wall -std=c++11  -pthread
SRCS: threadpool_v1-2.cpp Queue.cpp
	$(CXX) $(CFLAGS)  -o main threadpool_v1-2.cpp Queue.cpp

.PHONY: clean
