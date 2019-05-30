CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -g -fsanitize=address
LDFLAGS =  -fsanitize=address
LBLIBS = -I -lpthread -pthread 
CVER = -std=c++11 

# SRC = $(wildcard *.cpp)
SRC = constexpr.cpp
OBJ = $(wildcard *.o)
EXEC = main


all:$(EXEC)
	@echo "Compile completed!"
	
$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) $(SRC) -o $@ $(OBJ) $(LBLIBS) $(CVER)

clean:
	rm -rf $(OBJ) $(EXEC)
	@echo "Cleanup complete"


#Makefile 
# CC=gcc
# CXX=g++
# CFLAGS=-I. -lpthread -Wall -std=c++11  -pthread
# SRCS: condition_variable2.cpp
# 	$(CXX) $(CFLAGS)  -o main condition_variable2.cpp

# .PHONY: clean