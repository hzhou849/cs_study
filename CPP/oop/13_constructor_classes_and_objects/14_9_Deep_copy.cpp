/* Deep copy constructor
 *
 * Create copy of pointed-to data
 * Each copy will have a pointer to unique storage in the heap
 * You awalys want to Deep copy when you have a raw pointer as  class data member
 * 
 */

#include <iostream>


class Deep {
private:
    int *data;
public:
    void set_data_value (int d) {*data = d;}
    int get_data_value() {return *data;}

    //Constructor
    Deep(int d);

    //Copy constructor
    Deep(const Deep &source);

    //Destructor
    ~Deep();
};

Deep::Deep(int d) {
    data = new int;
    *data = d;
}

Deep::Deep(const Deep &source) 
    :Deep(*source.data) {
    std::cout << "Copy constructor -> deep copy" << std::endl;
}

Deep::~Deep() {
    delete data;
    std::cout<< "Destructor called...freeing memory" << std::endl;
}


/* When s goes out of scpe the destructor is called and releases data.
 * No problem since the stroage being released is unique to s.
 */ 
void display_deep (Deep s) {  //a copy seperate copy is created s.data -> 0xffb8[100] this copy will get cleaned up  not 0xff98
    std::cout << s.get_data_value() << std::endl;
}   

int main() {
    Deep obj1 {100}; // data -> 0xff98 [100]
    display_deep(obj1);

    Deep obj2 {obj1};
    obj2.set_data_value(1000);
}
