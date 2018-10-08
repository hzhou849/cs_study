/*
*  Alex Quartulli <alex.m.quartulli@gmail.com>
* Sat, Sep 29, 9:03 PM (9 days ago)
* to me
* 
* Hey Howard. Your homework is to write functions for each of the following:
* -Given a pointer to a null-terminating string, find the length of the string.
* -Given a pointer to a null-terminating string and a character, find the index of the first occurrence of that character in the string. Return -1 if the string does not contain the character.
* -Given a pointer to a null-terminating string and a character, find the index of the last occurrence of that character in the string. Return -1 if the string does not contain the character.
* -Given two pointers str1 and str2 to null-terminating strings, find the first differing character. If the differing character is smaller in str1 than str2 then return -1. Otherwise return 1. If the strings are equal then return 0. Smaller in this context literally means less than.
* -Given two pointers dest and src where src is a null-terminating string, copy the contents of src into dest.
* -Given two pointers dest and src to null-terminating strings, append the contents of src to the end of dest.
* You won't need malloc to write these functions, though it would be useful to test them. Let me know if you have any questions.
*/



#include <stdio.h>
#include <stdlib.h>

//Const pointer will not hcange what is pointed to)
int strlength(const char* s) {
	int string_length;

	// Array method
	for (int i=0; s[i] != '\0'; i++) {
		printf("s[%d] = %c\n", i,s[i] );
		
		// add 2 to account for i)zero index +1, null terminator element
		string_length = i+2; 
	}

	//pointer methods.
		
	return string_length;
}


int main (int argc, char**argv) {
	int l = strlength("Barad"); // goes to literal memory
	printf ("l = %d\n", l);

}

