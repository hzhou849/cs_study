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

*4 -Given two pointers str1 and str2 to null-terminating strings, find the first 
	differing character. If the differing character is smaller in str1 than str2 
	then return -1. Otherwise return 1. If the strings are equal then return 0. 
	Smaller in this context literally means less than.

*5 -Given two pointers dest and src where src is a null-terminating string, copy the contents of src into dest.
*
 6-Given two pointers dest and src to null-terminating strings, append the contents of src to the end of dest.
* You won't need malloc to write these functions, though it would be useful to test them. Let me know if you have any questions.

strings can be stored either
char str1[] = "Hello"
char *str2 = "Goodbye"
*/



#include <stdio.h>
#include <stdlib.h>


/*
* -Given a pointer to a null-terminating string, find the length of the string. - DONE
*/
//Const pointer will not hcange what is pointed to)
int str_len(const char* s) {
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



/*
*-Given a pointer to a null-terminating string and a character, find the index 
* of the first occurrence of that character in the string. Return -1 if the 
* string does not contain the character. -- DONE
* 	strings can be stored either
* * stores &
* ex: 
* char * str - pointer variables 
* str=&str1
* char str1[] = "Hello"
* char *str2 = "Goodbye"
*/
int str_find(const char* c, const char* s) {



	int index_pos=-1;
	int i =0;
	printf("comparision char: %c\n", *c);

	do {
		printf("s[%d] = %c\n", i, s[i]);
		// printf("%c\n", *s+i); //why won't work?
		i++;

		if (s[i] == '\0'){
			i=-1;
		}
	
	} while( s[i] != *c && s[i] !='\0');
	
	printf("s[%d] --> %c\n", i, s[i]);
	index_pos = i;

	return index_pos ;
}




/*
* Given a pointer to a null-terminating string and a character, find the index 
* of the last occurrence of that character in the string. Return -1 if the string 
* does not contain the character.
*/
int last_occur(const char* c, const char* s) {
	//iterati
	int index_pos = -1;
	int loop_on = 1;
	int i=0;

	do {
		printf("s[%d] = %c\n", i, s[i]);

		if (s[i] == *c) {
			index_pos = i;
		}
		else if (s[i] == '\0'){
			loop_on = 0;
		}
		i++;
	} while (loop_on == 1);

	return index_pos;
}

/**4 -Given two pointers str1 and str2 to null-terminating strings, find the first 
	differing character. If the differing character is smaller in str1 than str2 
	then return -1. Otherwise return 1. If the strings are equal then return 0. 
	Smaller in this context literally means less than.
	insane inssanity
*/

int diff_str(const char* s1, const char* s2 )
{
	//algorithm is good. use do while to fix.
	if (s1 == s2) {
		return 0;
	}
	for (int i=0; s1[i] != '\0' || s2[i] != '\0'; i++ ){
	
		printf("s1[%d]=%c  s2[%d]=%c\n", i, s1[i], i,s2[i]);
		// if first diff char found
		if (s1[i] != s2[i]){
			printf("Diff char detected--->s1[%d]=%c  s2[%d]=%c\n", i, s1[i], i,s2[i]);
			return s1[i] < s2[i] ? -1 : 1;
		}
		
	} 

	return 0; //nothing else found
	
}

/* 5 -Given two pointers dest and src where src is a null-terminating string, 
	copy the contents of src into dest.
*/
	des_str pointer 
// int stringCopy(char* dest_str, const char* src_str) {
// 	int i=0;
// 	do{
// 		dest_str[i] = src_str[i];
// 		if (src_str[i+1] == '/0') {

// 		}

// 	} while (src_str[i] != '/0')
// }

/* Main driver class */
int main (int argc, char**argv) {
	// int l = str_len("Barad"); // goes to literal memory
	// printf ("l = %d\n", l);

	// int sf=str_find("a", "insanaf");
	// printf("str_find index pos: %d\n", sf);

	// int loccur=last_occur("a", "insanafas");
	// printf("last occur pos: %d\n", loccur);

	// int diff=diff_str("bounce", "bounce");

	// printf("different str test: %d\n", diff );

	return 0;
}

