
# CC = gcc 
# DEBUG = -g
# CFLAGS =  -Wall -I /usr/src/linux-headers-4.4.0-103/include  -I /usr/lib/gcc/x86_64-linux-gnu/5/include -M /usr/src/linux-headers-4.4.0-103/include/asm-generic/
# SRC = kontron_driver.c
# kontron_driver : 
# 	$(CC) $(CFLAGS) $(SRC) -o kontron_driver 

# clean: 
# 	\rm *.o *~ kontron_driver

obj-m += kontron_driver.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean