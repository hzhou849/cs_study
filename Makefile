#http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
CC=gcc
CFLAGS=-I. -Wall -pedantic
list_test: list_test.c
	$(CC) $(CFLAGS) -o list_test list_test.c