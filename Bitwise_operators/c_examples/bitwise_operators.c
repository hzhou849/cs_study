#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 		//CHAR_BIT defined as 8

// #define CHAR_BIT = 8;

/*not working */
// return pointer, in this case an array.
// char *int_binary (unsigned num, char *buffer) {
	
// 	#define  BITS  (sizeof(num) * CHAR_BIT)

// 	static char static_buf[BITS+1];

// 	if (buffer == NULL) {
// 		buffer = static_buf;
// 	}

// 	for (int i = (BITS-1); i >= 0; --i) {
// 		buffer[i] = (num & 1) ? '1' : '0';
// 		num >>=1;
// 	}

// 	for (int i = BITS-1; i >= 0; --i) {
// 		if (num & 1) {
// 			buffer[i] = 1;
// 		} else {
// 			buffer[0] = 0;
// 		}
// 		num >>=1; // shift to left 1
// 	}	

// 	buffer[BITS] = '\0';
	
	
// 	return buffer;


// 	#undef BITS		/// kill the definition
	
// }

// int main() {
// 	char buff_str[33];
// 	char *result;
// 	result=int_binary(0xDEADBEEF, buff_str);
// 	printf("buffer dump: %s\n", *result);
// }

/* version 2  - working*/
char * int_binary (char num) {
	size_t bits =sizeof(char) * CHAR_BIT; // long unsigned int

	char *str = (char*)malloc(bits +1) ;
	
	if (!str) return (char*)-1;
	str[bits] = '\0'; // null terminate the string

	int ibits = (int)bits;
	printf("bits: %lu, %d\n", bits, ibits);
	//type punning becuase signed shift is implemention-defined
	// unsigned u = *(unsigned *) &i;
	for (; bits--; num >>= 1)
		str[bits] = num &1? '1': '0';
	// for (int i=8;)


	return str;

}

int main() {
	char *str;
	str=int_binary(5);
	printf("output: %s\n", str);

	printf("test: %c %c", str[6], str[5]);
	return 0;
}