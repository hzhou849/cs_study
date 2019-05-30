/*Tuples in C++
What is a tuple? 
A tuple is an object that can hold a number of elements. The elements can be of different data types. The elements of tuples are initialized as arguments in order in which they will be accessed.

Operations on tuple :-

1. get() :- get() is used to access the tuple values and modify them, it accepts the index and tuple name as arguments to access a particular tuple element.

2. make_tuple() :- make_tuple() is used to assign tuple with values. The values passed should be in order with the values declared in tuple.

filter_none
edit
play_arrow

brightness_4
https://www.geeksforgeeks.org/tuples-in-c/
*/
// C++ code to demonstrate tuple, get() and make_pair() 
#include<iostream> 
#include<tuple> // for tuple 
using namespace std; 
int main() 
{ 
    // Declaring tuple 
    tuple <char, int, float> geek; 
  
    // Assigning values to tuple using make_tuple() 
    geek = make_tuple('a', 10, 15.5); 
  
    // Printing initial tuple values using get() 
    cout << "The initial values of tuple are : "; 
    cout << get<0>(geek) << " " << get<1>(geek); 
    cout << " " << get<2>(geek) << endl; 
  
    // Use of get() to change values of tuple 
    get<0>(geek) = 'b'; 
    get<2>(geek) =  20.5; 
  
     // Printing modified tuple values 
    cout << "The modified values of tuple are : "; 
    cout << get<0>(geek) << " " << get<1>(geek); 
    cout << " " << get<2>(geek) << endl; 
  
    return 0; 
} 
Output:



The initial values of tuple are : a 10 15.5
The modified values of tuple are : b 10 20.5
In the above code, get() modifies the 1st nd 3rd value of tuple.

3. tuple_size :- It returns the number of elements present in the tuple.

filter_none
edit
play_arrow

brightness_4
//C++ code to demonstrate tuple_size 
#include<iostream> 
#include<tuple> // for tuple_size and tuple 
using namespace std; 
int main() 
{ 
  
    // Initializing tuple 
    tuple <char,int,float> geek(20,'g',17.5); 
  
    // Use of size to find tuple_size of tuple 
    cout << "The size of tuple is : "; 
    cout << tuple_size<decltype(geek)>::value << endl; 
  
    return 0; 
  
} 
Output:

The size of tuple is : 3
4. swap() :- The swap(), swaps the elements of the two different tuples.

filter_none
edit
play_arrow

brightness_4
//C++ code to demonstrate swap() 
#include<iostream> 
#include<tuple> // for swap() and tuple 
using namespace std; 
int main() 
{ 
  
    // Initializing 1st tuple 
    tuple <int,char,float> tup1(20,'g',17.5); 
      
    // Initializing 2nd tuple 
    tuple <int,char,float> tup2(10,'f',15.5); 
      
    // Printing 1st and 2nd tuple before swapping 
    cout << "The first tuple elements before swapping are : "; 
    cout <<  get<0>(tup1) << " " << get<1>(tup1) << " "
         << get<2>(tup1) << endl; 
    cout << "The second tuple elements before swapping are : "; 
    cout <<  get<0>(tup2) << " " << get<1>(tup2) << " " 
         << get<2>(tup2) << endl; 
      
    // Swapping tup1 values with tup2 
    tup1.swap(tup2); 
      
    // Printing 1st and 2nd tuple after swapping 
    cout << "The first tuple elements after swapping are : "; 
    cout <<  get<0>(tup1) << " " << get<1>(tup1) << " " 
         << get<2>(tup1) << endl; 
    cout << "The second tuple elements after swapping are : "; 
    cout <<  get<0>(tup2) << " " << get<1>(tup2) << " " 
         << get<2>(tup2) << endl; 
  
    return 0; 
} 
Output:

The first tuple elements before swapping are : 20 g 17.5
The second tuple elements before swapping are : 10 f 15.5
The first tuple elements after swapping are : 10 f 15.5
The second tuple elements after swapping are : 20 g 17.5
5. tie() :- The work of tie() is to unpack the tuple values into seperate variables. There are two variants of tie(), with and without “ignore” , the “ignore” ignores a particular tuple element and stops it from getting unpacked.

filter_none
edit
play_arrow

brightness_4
// C++ code to demonstrate working of tie() 
#include<iostream> 
#include<tuple> // for tie() and tuple 
using namespace std; 
int main() 
{    
    // Initializing variables for unpacking 
    int i_val; 
    char ch_val; 
    float f_val;    
      
    // Initializing tuple 
    tuple <int,char,float> tup1(20,'g',17.5); 
  
    // Use of tie() without ignore 
    tie(i_val,ch_val,f_val) = tup1; 
      
    // Displaying unpacked tuple elements 
    // without ignore 
    cout << "The unpacked tuple values (without ignore) are : "; 
    cout << i_val << " " << ch_val << " " << f_val; 
    cout << endl; 
      
    // Use of tie() with ignore 
    // ignores char value 
    tie(i_val,ignore,f_val) = tup1; 
      
    // Displaying unpacked tuple elements 
    // with ignore 
    cout << "The unpacked tuple values (with ignore) are : "; 
    cout << i_val  << " " << f_val; 
    cout << endl; 
  
    return 0; 
  
} 
Output:

The unpacked tuple values (without ignore) are : 20 g 17.5
The unpacked tuple values (with ignore) are : 20 17.5
6. tuple_cat() :- This function concatenates two tuples and returns a new tuple.

filter_none
edit
play_arrow

brightness_4
// C++ code to demonstrate working of tuple_cat() 
#include<iostream> 
#include<tuple> // for tuple_cat() and tuple 
using namespace std; 
int main() 
{ 
    // Initializing 1st tuple 
    tuple <int,char,float> tup1(20,'g',17.5); 
  
    // Initializing 2nd tuple 
    tuple <int,char,float> tup2(30,'f',10.5); 
      
    // Concatenating 2 tuples to return a new tuple 
    auto tup3 = tuple_cat(tup1,tup2); 
      
    // Displaying new tuple elements 
    cout << "The new tuple elements in order are : "; 
    cout << get<0>(tup3) << " " << get<1>(tup3) << " "; 
    cout << get<2>(tup3) << " " << get<3>(tup3) << " "; 
    cout << get<4>(tup3) << " " << get<5>(tup3) << endl; 
  
    return 0; 
} 
Output:

The new tuple elements in order are : 20 g 17.5 30 f 10.5