#include <exception>


class AssertionException: public std::exception {
    public:
    const char* what() const throw() {
        return "Assertion failed.";
    }

};