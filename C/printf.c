printf:
printf function is used to print character stream of data on stdout console.
Syntax :
 int printf(const char* str, ...); 

Example :
// simple print on stdout  
#include<stdio.h> 
int main() 
{ 
   printf("hello geeksquiz"); 
   return 0; 
}
// Output :
//  hello geeksquiz

//===================================================================
sprintf:
Syntax:

int sprintf(char *str, const char *string,...); 
// String print function instead of printing on console store it on char buffer which are specified in sprintf

Example :
// Example program to demonstrate sprintf() 
#include<stdio.h> 
int main() 
{ 
    char buffer[50]; 
    int a = 10, b = 20, c; 
    c = a + b; 
    sprintf(buffer, "Sum of %d and %d is %d", a, b, c); 
  
    // The string "sum of 10 and 20 is 30" is stored  
    // into buffer instead of printing on stdout 
    printf("%s", buffer); 
  
    return 0; 
} 
// Output :
// Sum of 10 and 20 is 30
//==================================================================


// fprintf:
// fprintf is used to print the string content in file but not on stdout console.

int fprintf(FILE *fptr, const char *str, ...);
Example :

filter_none
edit
play_arrow

brightness_4
#include<stdio.h> 
int main() 
{ 
    int i, n=2; 
    char str[50]; 
  
    //open file sample.txt in write mode 
    FILE *fptr = fopen("sample.txt", "w"); 
    if (fptr == NULL) 
    { 
        printf("Could not open file"); 
        return 0; 
    } 
  
    for (i=0; i<n; i++) 
    { 
        puts("Enter a name"); 
        gets(str); 
        fprintf(fptr,"%d.%s\n", i, str); 
    } 
    fclose(fptr); 
  
    return 0; 
} 
// Input: GeeksforGeeks
//        GeeksQuiz
// Output :  sample.txt file now having output as 
// 0. GeeksforGeeks
// 1. GeeksQuiz