#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <iostream>
#include <string>

class Device {
    friend std::ostream &operator<<(std::ostream &os, const Device &device);
private:

    /*USE this if you want to have default values in your class
	 *
	 *  to avoid polluting the global namespace, declare and initialize these values here 
     * remember static variables must be initialized in order to be used.
     * otherwise have to delcare the def_name, dev_value in the public space
     */
    static constexpr const char *def_name="unamed device";
    static constexpr double def_value = 0.0;
protected:
    std::string name;
    double value;
public:
    /*another way to setup the constructor with initialization */
    // public: 
    // Point(int i = 0, int j = 0):x(i), y(j) {}  
    // /*  The above use of Initializer list is optional as the  
    //     constructor can also be written as: 
    //     Point(int i = 0, int j = 0) { 
    //         x = i; 
    //         y = j; 
    //     } 
    // */ 
    Device(std::string name = def_name, double value =def_value );
    //Device(std::string name = "unamed device", double value = 0.0); // alt. method if not using constexpr

    bool function1(double a);
    bool function2(double b);
    double get_value() const;


};

#endif //_DEVICE_H_