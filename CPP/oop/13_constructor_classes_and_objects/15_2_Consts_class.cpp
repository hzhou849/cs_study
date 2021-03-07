/*
 *Const keyword. the Idea is to protect as much of the passing data as possible.
 * Good practice to use as often as possible.
 * use on any function  you need to pass data through unmodified.
 */


#include <iostream>
#include <string>

class Device {
private:
    std::string dev_name;
    int base_address;
    int cmd_bit;
public:
    void set_dev_name(std::string dev_name_val) {
        this->dev_name = dev_name_val;
    }
    void set_base_address(int base_address_val);
    void set_cmd_bit (int cmd_bit_val);

    //this needs to be const to guarantee that no changes will be made in this method.
    //const in this case makes the function const locked.
    std::string get_dev_name () const {        
        return dev_name;
    }
    int get_base_address();
    int set_cmd_bit();

    //Constructor prototypes
    Device();
    Device(std::string dev_name_val, int base_address_val, int cmd_bit_val);
    // Destructor
    ~Device();
};

Device::Device()
    :Device {"None", 0,0} {

}

Device::Device (std::string dev_name_val, int base_address_val, int cmd_bit_val) 
    : dev_name{dev_name_val} ,base_address{base_address_val}, cmd_bit{cmd_bit_val} {

}

//helper function optional to display get_dev_name
void display_name(const Device &d) {
    std::cout << d.get_dev_name() << std::endl;
}


int main() {
    const Device dev1("device1", 123, 456);
    Device dev2("device2", 111, 222);
    
    //dev1.set_dev_name("newName");
    std::cout << dev1.get_dev_name() << std::endl;
    display_name(dev1);
    
    return 0;
}
