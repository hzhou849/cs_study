/* Application to access /Dev/mem - physical address  for read write.

Tested and working */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>

// use <sys/io.h> instead
//#include <asm/io.h>
#include <sys/io.h>
//#include "Device.h"

// '\' allows code to be written to next line 
#define FATAL do {fprintf(stderr, "Error at liine %d, file %s (%d) [%s]\n", \ 
	__LINE__, __FILE__, errno, strerror(errno)); exit(1); } while(0)

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

int main(int argc, char **argv)  
{
	int fd;
	void *map_base, *virt_addr, *map_test;
	unsigned long read_result, writeval;
	off_t target; // POSIX standard refers to size of file , size_t for objects aka {long int}
	int access_type = 'w';

	if (argc < 2) {
		fprintf(stderr, "\nUsage:\t%s { address } [ type [ data ] ]\n"
				"\taddress 	: memory adddress to act upon\n"
				"\ttype		: access operation type : [b]yte, [h]alfword, [w]ord\n"
				"\tdata		: data to be written\n\n",
				argv[0]);
		exit(1);
	}
	target = strtoul(argv[1], 0, 0);
	
	if(argc > 2)
		access_type = tolower(argv[2][0]);
	

	// open file descriptor on /dev/mem
	if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1 ) FATAL;
	printf("/dev/mem opended.\n");
	fflush(stdout);

	/* Map one page */
	map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~MAP_MASK);
	//map_test = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~MAP_MASK);
	if(map_base == (void *) -1) FATAL;
	printf("Memory mapped at address %p.\n", map_base);
	fflush(stdout);

	// Read Physical Address
	virt_addr = map_base + (target & MAP_MASK);
	switch(access_type) {
		case 'b' :
				 read_result = *((unsigned char * ) virt_addr);
				 break;
		case 'h' :
				 read_result = *((unsigned short *) virt_addr);
				 break;
		case 'w' :
				 read_result = *((unsigned long *) virt_addr);
				 break;
		default:
				fprintf(stderr, "Illegal data type '%c'. \n", access_type);
				exit(2);
	}

	printf("Value at address 0x%X (%p): 0x%X\n", target, virt_addr, read_result);
	fflush(stdout);

	//Write values to /dev/mem
	if(argc > 3) {
		writeval = strtoul(argv[3], 0, 0);
		switch(access_type) {
			case 'b' :
					 *((unsigned char *) virt_addr) = writeval;
					 read_result = *((unsigned char *) virt_addr);
					 break;
			case 'h' :
					 *((unsigned short *) virt_addr) = writeval;
					 read_result = *((unsigned short *) virt_addr);
					 break;
			case 'w' :
					 read_result = *((unsigned long *) virt_addr);
					 break;
		}
		printf("Written 0x%X; readback 0x%X\n", writeval, read_result);
		fflush(stdout);
	}

	/* close/unmap all registers and fd */
	if(munmap(map_base, MAP_SIZE) == -1) FATAL;
	close(fd);
	return 0;	
}