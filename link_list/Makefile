#http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
CC=gcc
CFLAGS=-I. -Wall -pedantic
list_test: list_test_ver2.c
	$(CC) $(CFLAGS) -o list2 list_test_ver2.c

#phony keeps make from doing something with conflicting name of files
.PHONY: clean
#clean:
	#rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
