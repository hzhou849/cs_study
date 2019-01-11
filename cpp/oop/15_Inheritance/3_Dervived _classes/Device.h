#ifndef _DEVICE_H_
#define _DEVICE_H_

class Device {
public:
    double mem_content;
    std::string name;
    void input (double data);
    void output (double data);
    Device();
    ~Device();
};

#endif //_DEVICE_H_