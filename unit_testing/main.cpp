#include<iostream>

// test includes
#include "asserts.hpp"

void test1_pass() {
    Asserts::Equals<int>(1,1);
}

void test1_fail() {
    Asserts::Equals<int>(888,1);
}

void test_throw() {
    throw std::exception();

}

void throws_invalid_argument() {
    throw std::invalid_argument("my argument");
} 

void test_throw_assertion() {
    Asserts::throws<std::invalid_argument>(throws_invalid_argument);
}

void does_nothing() {
    //does nothing
}
void test_nothrow_assertion() {
    Asserts::throws<std::invalid_argument>(does_nothing);
}


int main() {
   Asserts::run_test(test1_fail, "test1_fail");
   Asserts::run_test(test1_pass, "test1_pass");
   Asserts::run_test(test_throw, "test_throw");

   Asserts::run_test(test_throw_assertion, "test_throw_assertion");
   Asserts::run_test(test_nothrow_assertion, "test_nothrow_assertion");

    std::cout << "Test completed successfully." << std::endl;
    return 0;
}