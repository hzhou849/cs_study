
/* Device.hpp */
#ifndef _DEVICE_H_
#define _DEVICE_H_

//Interface Class
class I_interfaceDriver{
protected:
	// common shared values.
	int value1;
	int value2;
public:  // pure virtual function providing interface framework
	virtual int readData() = 0;
	void setValue1(int v) {value1 = v;}
	void setValue2(int v2) {value2 = v2;}

};

class Device {
protected: // allows in class access to inherited objects
	char *name;
	char *mem_content;		// pointer to char [] that holds a c-style string
public:
	Device();
	Device(const char *bits);
	virtual ~Device();
	virtual void display() const; // const for string protection
	char* get_mem();

	virtual int readData(); 

};

class Sub_device: public Device{
public:
	Sub_device();
	Sub_device(const char *bits);
	virtual ~Sub_device();		// virtual destructor
	virtual void display() const override;

	virtual int readData();
};
#endif //_DEVICE_H_



/* Device.cpp */
#include <iostream>
#include <cstring>

Device::Device() :mem_content{nullptr} {
	mem_content= new char[1]; // allocate memory in heap. remember cstring just need the starting address
	*mem_content='\0';        // set initial deref. value the address and assign null terminator to that address
}

Device::Device(const char *bits) : mem_content{nullptr} {
	if (bits == nullptr) {
		mem_content = new char [1];
		*mem_content = '\0';
	} else {
		mem_content = new char[std::strlen(bits) +1]; // allocate memory for str
		strcpy(mem_content,bits); 					  //copy over
	}
} 

Device::~Device() {
	delete[] mem_content;
}


void Device::display() const  {		//const for str
	std::cout << "Device memory content" << mem_content << std::endl;
}

char *Device::get_mem() {
	return mem_content;
}



/* Sub_Device.cpp */
Sub_device::Sub_device() {}
Sub_device::Sub_device(const char *bits)
	:Device(bits) { // call the base class construction. reusing code

}
Sub_device::~Sub_device() {
	delete[] mem_content;
}

void Sub_device::display() const {
	std::cout << "Sub component memory content " << mem_content << std::endl;
}

/*Driver class */
// #include <iostream>
// #include <cstring>
// #include "Device.h"
// #include "Sub_device.h"

int main() {
	Device *ptr_device = new Device ("FFFF");
	Device *ptr_sub = new Sub_device("EF089");

	ptr_device->display();
	ptr_sub->display();

	std::cout << ptr_sub->get_mem() << std::endl;
}
