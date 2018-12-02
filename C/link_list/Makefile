#http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
CC=gcc
CFLAGS=-I. -Wall -pedantic
final_list: final_test2.c
	$(CC) $(CFLAGS) -o final_test2 final_test2.c

#phony keeps make from doing something with conflicting name of files
.PHONY: clean
#clean:
	#rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
