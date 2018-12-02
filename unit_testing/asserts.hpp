#include <iostream>
#include <string>

#include "AssertExceptions.hpp"

namespace Asserts {
    void run_test (void (*test_function)(), const std::string &test_name){
        try {
            std::cout << "Starting "<< test_name << std::endl;
            test_function();
            std::cout << test_name << " passed..." << std::endl;
        } 
        catch (std::exception &e) {
            std::cout << test_name << " Caught: "<<e.what() << std::endl;
        }
        std::cout<<std::endl;
    }

    template <class T>
    void Equals(T actualValue, T expectedValue){
        if (actualValue != expectedValue) {
            throw AssertionException();
        }    
    }

    template <class T>
    void not_equals(T actual_value, T expected_value) {
        if (actual_value == expected_value) {
            throw AssertionException();
        }
    }

    template <class T>
    void throws(void (*test_function)()){
        bool did_throw_T = false;

        try{
            test_function();
        }
        catch (T &e) {
            did_throw_T = true;
        }

        if (!did_throw_T) {
            throw AssertionException();
        }
    }
}
// class Assert  {
//     private:

//     public:
//         template <class T>
//         void Equals(T actualValue, T expectedValue){
//             if (actualValue != expectedValue) {
//                 throw AssertionException();
//             }    
//         }


// };