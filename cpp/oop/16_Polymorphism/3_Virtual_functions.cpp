/* 18-5
 * Virtual functions
 * 
 * 
 * Declaring virtual fucntions
 *  - allows function calls to be bound at runtime instead of statically bound calling
 *  - The "Virtual" keyword only appears on the function declaration, not the definition
 *  - if you have virtual function, you must have virtual destructors
 *  - Override the funciton in the derived class (dynamically bound at runtime)
 *  - Function signature must be exactly the same
 *  - Virtual keyword not required but is best practie
 *  - If you don't provide an overrideen version it is inherited from its
 *    base class - 
 *     NOTE**dynamically bound only called from base class pointer or reference ie Base *ptr = new Derived();
 *      otherwise they are statically bound.
 * 
 *  Virtual Destructors MAKE SURE YOU HAVE THIS!!
 *  - if you don't have this, the default base destructor is called which can cause potential memory leaks
 *  - if you don't have a virtual destructor, only the base class destructor will be called.
 *  - potenital memory leaks etc...
 *  - once you provide a virtual destructor in the base class, all derived structors are virtual
 *  - when deleting/freeing memory it should free dervied first than base destructor
 */

#ifndef _DEVICE_H_
#define _DEVICE_H_

class Device {
protected: 
    char *name;
    char *mem_content;          // pointer to char[] that holds a c-style strings
public:
    Device();
    Device(const char *bits); 
    virtual ~Device();		// Virtual destructor
    virtual void display() const;     // const for str
    char* get_mem();

};

class Sub_component: public Device{
public:
    Sub_component();
    Sub_component(const char *bits);
    virtual ~Sub_component();		//virtual destructor
    virtual void display() const override;

};
#endif //_DEVICE_H_


/*Device.cpp */
#include <iostream>
#include <cstring>

Device::Device()
    :mem_content {nullptr}  { //set inital value to null
    mem_content = new char[1];   //allocate memory in heap remember cstrings just need the starting address
    *mem_content = '\0';        //set inital  dereferenced valuethe addresss and assign null terminator to that address
}

Device::Device (const char *bits) 
    :mem_content{nullptr} {
    if (bits == nullptr) {
        mem_content = new char [1];
        *mem_content = '\0'; // initialize with null terminator char
    } else {
        mem_content = new char[std::strlen(bits) +1];   // allocate memory for str
        strcpy(mem_content, bits);  //copy over
    }
}

Device::~Device(){}

void Device::display() const{       // const for str
    std::cout << "Device Memory content" << mem_content << std::endl;
}

char* Device::get_mem() {
    return mem_content;
}

/* Sub_component.cpp */
Sub_component::Sub_component(){}
Sub_component::Sub_component(const char *bits) 
    :Device(bits){
}
Sub_component::~Sub_component(){}


void Sub_component::display() const {
    std::cout << "Sub component memory content " << mem_content << std:: endl;
}



/*  main.cpp */
// #include <iostream>
// #include <cstring>
// #include "Device.h"
// #include "Sub_component.h"

int main() {
    Device *ptr_device = new Device("FFFF");
    Device *ptr_sub = new Sub_component("EF09");

    ptr_device->display();
    ptr_sub->display();

    std::cout << ptr_sub->get_mem()<<std::endl;

}

