
CC=gcc
CFLAGS=-I. -Wall -pedantic
final_list: fork_syscall.c
	$(CC) $(CFLAGS) -o fork_syscall fork_syscall.c

#phony keeps make from doing something with conflicting name of files
.PHONY: clean
#clean:
	#rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
