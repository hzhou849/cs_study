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


int main (int argc, char **argv) {
	
	int num1, num2;

	printf("Prefix and Postfix operators...(num = 10)\n");
	num1 = 10;
	/* POSTFIX operators Notice num2 is 10, the assignment is done first, then incremented*/
	num2 = num1++; // num2 = 10, num1 = 11

	printf("num2 = num1++; so num2=%d and num = %d\n", num2, num1);

	num1 = 10;

	/*PREFIX operators, in this case the variable num1 is updated first, then assigned to num2*/
	num2 = ++num1; // num2 = 11, num1 =11
	printf("num2 = ++num1; so num2 = %d and num1 = %d\n", num2, num1);


}