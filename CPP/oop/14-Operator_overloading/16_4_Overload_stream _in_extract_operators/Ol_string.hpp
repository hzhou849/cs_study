/* 16.4 stream overloads
 */


#ifndef _OL_STRING_H_
#define _OL_STRING_H_

class Ol_string {
    // Operator overloads
    friend bool operator==(const Ol_string &lhs, const Ol_string &rhs);
    friend Ol_string operator-(const Ol_string &obj);
    friend Ol_string operator+(const Ol_string &lhs, const Ol_string &rhs);

    //  stream overloads
    friend std::ostream &operator << (std::ostream &os, const Ol_string &rhs);
    friend std::istream &operator >>(std::istream &in, Ol_string &rhs);


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