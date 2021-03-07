/* Static class members
 *
 * 
 *  NOTE: static functions only have access to static variables
 * 
 * Class data members can be delcalred as static
 *  - A single data member that belongds to the class not the object instances
 *  - Useful to store class-wide information
 * 	 ie: say you want to keep track of how many instances of class objects you have created 
 * 
 *  Class functions can be declared as static
 *  - independent of any objects
 *  - can be called using the class name.
 */

#include <iostream>
#include <string>

class Device {
private:
    static int num_devices; // static memory this will count the number of class instances
    std::string dev_name;
    int reg_number;
public:
    // setters
    void set_dev_name(std::string dev_name_val) {
        this->dev_name = dev_name_val;
    }
    void set_reg_number(int reg_number_val);
    
    // getters
    static int get_number_devices() { return num_devices; }; // ^^static functions only have access to static variables.
    std::string get_dev_name() { return dev_name; }
    int get_reg_number() { return reg_number;}


    //Constructor prototypes
    Device();
    Device(std::string dev_name_val, int reg_number);
    Device(const Device &source);
    //Destructor
    ~Device();
};

//Initialization happends here in .cpp file.
// Static variable needs to be initialized in order to be used.
int Device::num_devices {0};

Device::Device()
    :Device {"None", 0} {
}

Device::Device(const Device &source)    // const to make sure no changes happen during copy.
    :Device{source.dev_name,source.reg_number} {
}

Device::Device (std::string dev_name_val, int reg_number_val)
    :dev_name{dev_name_val}, reg_number{reg_number_val} {
    ++num_devices;
}

Device::~Device() {
    num_devices--;
}

void display_obj_count(){
    std::cout<<"objects created: " << Device::get_number_devices() << std::endl;
}

int main() {
    Device dev1("Device1", 1);
    display_obj_count();
    {
        Device dev2("Device2", 88);
        Device dev3("Device2", 88);
        display_obj_count();
    }
    
    display_obj_count();

    return 0;
}