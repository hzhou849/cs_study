/* Dynamic memory allocation */

#include <iostream>

// using namespace std;    // Use the entire std namespace


int main() {
   

    int *int_ptr {nullptr};
    int_ptr = new int;          // Dynamically allocated on the heap
    *int_ptr = 88;

    std::cout << "int_ptr: " << int_ptr << std::endl; 
    std::cout << "int_ptr: " << &int_ptr << std::endl;
    std::cout << "int_ptr: " << *int_ptr << std::endl;
     

    delete int_ptr;
    // int_ptr =nullptr;
     std::cout << "int_ptr: " << int_ptr << std::endl; 
    std::cout << "int_ptr: " << &int_ptr << std::endl;
    std::cout << "int_ptr: " << *int_ptr << std::endl;



    // allocate multiple block of memory
    double *temp_ptr {nullptr};
    temp_ptr = new double[5 * (sizeof(double))]; // allocate array size of double

   *(temp_ptr+2) = 999; //pointer offset notation 
    std::cout << "temp_ptr: " << temp_ptr[2] << std::endl; // pointer subscript notation array syntax 
    std::cout << "temp_ptr: " << (temp_ptr +1)<< std::endl; 
    std::cout << "temp_ptr: " << (temp_ptr +2)<< std::endl; 
    
    delete[] temp_ptr;
    return 0;
}