/* Bitwise operators 
 *
 * https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/
 * 
 * 
    & (bitwise AND) Takes two numbers as operands and does AND on every bit of two numbers. The result of AND is 1 only if both bits are 1.
    | (bitwise OR) Takes two numbers as operands and does OR on every bit of two numbers. The result of OR is 1 any of the two bits is 1.
    ^ (bitwise XOR) Takes two numbers as operands and does XOR on every bit of two numbers. The result of XOR is 1 if the two bits are different.
    << (left shift) Takes two numbers, left shifts the bits of the first operand, the second operand decides the number of places to shift.
    >> (right shift) Takes two numbers, right shifts the bits of the first operand, the second operand decides the number of places to shift.
    ~ (bitwise NOT) Takes one number and inverts all bits of it

 * */

* C Program to demonstrate use of bitwise operators */
#include<stdio.h> 
int main() 
{ 
    unsigned char a = 5, b = 9; // a = 5(00000101), b = 9(00001001) 
    printf("a = %d, b = %d\n", a, b); 
    printf("a&b = %d\n", a&b); // The result is 00000001 
    printf("a|b = %d\n", a|b);  // The result is 00001101 
    printf("a^b = %d\n", a^b); // The result is 00001100 
    printf("~a = %d\n", a = ~a);   // The result is 11111010 
    printf("b<<1 = %d\n", b<<1);  // The result is 00010010  
    printf("b>>1 = %d\n", b>>1);  // The result is 00000100  
    return 0; 
} 