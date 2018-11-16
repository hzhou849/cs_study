#http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
CC=gcc
CFLAGS=-I. -Wall -pedantic
list_test: list_test.c
	$(CC) $(CFLAGS) -o list_test list_test.c

#phony keeps make from doing something with conflicting name of files
.PHONY: clean
#clean:
	#rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
