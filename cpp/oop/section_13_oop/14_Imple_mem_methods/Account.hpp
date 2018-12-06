/* Notice the #ifndef - include guards. If this file is included in multiple files,
 * it prevents the preprocessor from making multiple declarations 
 * some #pragma once. some compilers support this compiler directive, but some don't.
 * check compiler documentation to be sure.
 * 
 * Methods will be implemented outside this class declarations
 * 
 */

// include guards for compiler directives
#ifndef _ACCOUNT_HPP_
#define _ACCOUNT_HPP_

class Account {
private:
    // Attributes
    double balance;
public:
    // Function prototypes
    void set_balance(double bal);
    double get_balance();
};


#endif