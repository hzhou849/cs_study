#http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
CC=g++
CFLAGS=-I. -Wall -pedantic
final_list: mem_test.c
	$(CC) $(CFLAGS) -o mem_test mem_test.c

#phony keeps make from doing something with conflicting name of files
.PHONY: clean
#clean:
	#rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
