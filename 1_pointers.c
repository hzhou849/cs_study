/*
*  Alex Quartulli <alex.m.quartulli@gmail.com>
* Sat, Sep 29, 9:03 PM (9 days ago)
* to me
* 
* Hey Howard. Your homework is to write functions for each of the following:
* -Given a pointer to a null-terminating string, find the length of the string. - DONE

* -Given a pointer to a null-terminating string and a character, find the index 
	of the first occurrence of that character in the string. Return -1 if the 
	string does not contain the character. -- DONE

* -Given a pointer to a null-terminating string and a character, find the index 
	of the last occurrence of that character in the string. Return -1 if the string 
	does not contain the character.

* -Given two pointers str1 and str2 to null-terminating strings, find the first differing character. If the differing character is smaller in str1 than str2 then return -1. Otherwise return 1. If the strings are equal then return 0. Smaller in this context literally means less than.
* -Given two pointers dest and src where src is a null-terminating string, copy the contents of src into dest.
* -Given two pointers dest and src to null-terminating strings, append the contents of src to the end of dest.
* You won't need malloc to write these functions, though it would be useful to test them. Let me know if you have any questions.

strings can be stored either
char str1[] = "Hello"
char *str2 = "Goodbye"
*/



#include <stdio.h>
#include <stdlib.h>

//Const pointer will not hcange what is pointed to)
int str_len(const char* s) {
	int string_length;
	char * temp;
	// Array method
	for (int i=0; s[i] != '\0'; i++) {
		printf("s[%d] = %c\n", i,s[i] );
		
		// add 2 to account for i)zero index +1, null terminator element
		string_length = i+2; 
	}

	//pointer methods.
		
	return string_length;
}

int str_find(const char* c, const char* s) {

/*	strings can be stored either
* stores &
ex: 
char * str - pointer variables 
str=&str1
char str1[] = "Hello"
char *str2 = "Goodbye"
*/
int index_pos=-1;
	int i =0;
	printf("comparision char: %c\n", *c);

	do {
		printf("s[%d] = %c\n", i, s[i]);
		// printf("%c\n", *s+i); //why won't work?
		i++;
	
	} while( s[i] != *c);
	printf("s[%d] --> %c\n", i, s[i]);
	index_pos = i;

	return index_pos ;
}


int main (int argc, char**argv) {
	// int l = str_len("Barad"); // goes to literal memory
	// printf ("l = %d\n", l);

	int sf=str_find("a", "insane");
	printf("str_find index pos: %d\n", sf);
	return 0;
}

