/*
 * 2
 * Knowing when to use the ^ hat is super-duper important, hard to make progress in C++/CLI when that's still murky. 
 * bool and double are value types, not object types, and variables of those types must therefore 
 * NOT be declared with ^. With the hat, it becomes a boxed copy of the value (System.ValueType under the hood) 
 * and the compiler is liable to lose its marbles badly.
 * 
 * Editlines.extend column
 * 
 * 
 */

#include "pch.h"
#include <iostream>
#include <exception>

#include "AdamsHal.h"


using namespace System;

//TODO get the entire sequence of the voltage readings. or attemp



int main(array<System::String ^> ^args)
{
    std::vector<double> *m_voltageValues = new std::vector<double>();
    //std::vector<double> *vec2;
    String^ test = ""; 
    double d_response = 0;

    AdamsHal^  m_AdamsHalObj = gcnew AdamsHal;
    m_AdamsHalObj->getChannelData(m_voltageValues);
    m_AdamsHalObj->getChannelDataFixed(m_voltageValues);
    /*delete m_AdamsHalObj;*/ //optional call to destructor, but if

    //Uboxing how to convert object back to intrinsic type 
    int^ val = 10;
    int^ valPtr = val;
    int val_int = 0;
    val_int = safe_cast<int>(val);

    std::cout << "print intrinsic type int: " << val_int << std::endl;

    // make sure you acquire the entire string patter

    
    return 0;
}
