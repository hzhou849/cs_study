/* 16.3 Overloading operatos as global functions
 * unlike 16.2 which are exclusive to that class only,
 * if you want to have friends of class, you can declare the
 * overloaded operators so they work with friends of classes
 */


#ifndef _OL_STRING_H_
#define _OL_STRING_H_

class Ol_string {
    friend bool operator==(const Ol_string &lhs, const Ol_string &rhs);
    friend Ol_string operator-(const Ol_string &obj);
    friend Ol_string operator+(const Ol_string &lhs, const Ol_string &rhs);
private:
    char *str;    // pointer to a char[] that holds a c-style string

public:
    Ol_string();
    Ol_string(const char *s);
    Ol_string(const Ol_string &source);   // copy constructor
    Ol_string (Ol_string &&source);       // Move constructor
    ~Ol_string();                         // Destructor

    //operator overloads assignment
    Ol_string &operator = (const Ol_string &rhs);
    Ol_string &operator = (Ol_string &&rhs);

    void display() const;
    int get_length() const;
    const char *get_str() const;
};
#endif  // _OL_STRING_H_