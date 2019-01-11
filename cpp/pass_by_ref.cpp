// #include <stdio.h>
// #include <stdlib.h>

#include <iostream>

// C version
void refPass(const int *a, const int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
   
}

int main() {
    int a = 22;
    int b = 555;

    refPass(&a, &b);
    // printf("A: %d; B: %d\n",a,b);
        std::cout << "A: "<<a << "B:"<<b<<std::endl;
}


//C++
// void refPass (const int &a, const int &b) {  // passing a const will write protect the values if you need to protect them
//     int temp = a;
//     a = b;
//     b = temp;
// }

// int main() {
//     int a, b;
//     a = 22;
//     b = 555;

//     refPass(a,b);

//     std::cout << "A: "<<a << "B:"<<b<<std::endl;
// }