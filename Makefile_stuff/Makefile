CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++11 -g -fsanitize=address
LDFLAGS =  -fsanitize=address
LBLIBS = -I -lpthread -pthread

SRC = $(wildcard *.cpp)
OBJ = $(wildcard *.o)
EXEC = main


all: $(EXEC)
	@echo "Compile completed!"
$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) $(SRC) -o $@ $(OBJ) $(LBLIBS)

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