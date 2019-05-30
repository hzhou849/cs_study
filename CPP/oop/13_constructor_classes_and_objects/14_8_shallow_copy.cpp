/* Shallow copy with copy constructor
 *
 * Any class with raw pointers will only copy the pointer, not what it is pointing to,
 * since 
 */ 

#include <iostream>

class Shallow{
private: 
    int *data;
public:
    void set_data_value(int d) {
        *data = d;
    }
    int get_data_value() {
        return *data;
    }

    //Constructor
    Shallow(int d);
    
    //Copy Constructor
    Shallow(const Shallow &source);
      
    //Destructor
    ~Shallow();
};

Shallow::Shallow(int d) {
    data = new int;     // allocate memory in heap
    *data = d;
}

Shallow::Shallow(const Shallow &source) 
    :data(source.data) {
    std::cout << "Copy construction --> shallow copy"<<std::endl;
}

Shallow::~Shallow(){
    delete data;
    std::cout << "Destructor freeing data" << std::endl;
}

/* The problem is since the pointer is copied onto this stack object,
 * once this item loses scope, the destructor will terminate this pointer to heap obj1 
 * This pointer that was copied will get cleaned off the stack making that heap address 
 * invalid. Thus obj1 will loose its data
 */ 
void display_shallow (Shallow s) {
    std::cout << s.get_data_value() << std::endl;
}


int main () {
    Shallow obj1 {100};
    display_shallow (obj1);

    Shallow obj2 {obj1};        //obj1 pointing heap address is invalid bc destructor freed the memory.
    // the heap thinking obj1's address is free, now assigns that "free" memory address to obj2 and they both share the same address     
    obj2.set_data_value(1000);  // now we have inadvertantly changed obj1's data to 1000 bc they both shared the same address

    //at this point when the program closes, the destructor will now try to close obj1, but the address is 
    // supposed to be invalid. and will crash

    return 0;
}