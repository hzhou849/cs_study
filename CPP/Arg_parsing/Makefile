CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -g -fsanitize=address
LDFLAGS =  -fsanitize=address
INCLUDE = -I /opt/boost/1.64/Linux/x86_64/release/include/boost/
LBLIBS =  -lpthread -pthread 
CVER = -std=c++11 
LPATH= -L /opt/boost/1.64/Linux/x86_64/release/lib -lboost_program_options


# SRC = $(wildcard *.cpp)
SRC = boost_prog_option.cpp
OBJ = $(wildcard *.o)
EXEC = main


all:$(EXEC)
	@echo "Compile completed!"
	
$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) $(SRC) -o $@ $(OBJ) $(INCLUDE) $(LPATH) $(LBLIBS) $(CVER)

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