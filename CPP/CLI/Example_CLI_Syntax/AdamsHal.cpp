#include "pch.h"
#include "AdamsHal.h"

// Initialize Static variables
//int AdamsHal::instanceCounter = 0;
using namespace System;

AdamsHal::AdamsHal()
{
	instanceCounter++;
	System::Console::WriteLine("ADAMS constructor called! - {0}", instanceCounter);
    System::Diagnostics::Debug::WriteLine("\n\nADAMS constructor called! - {0}", instanceCounter);
}

AdamsHal::~AdamsHal()
{
    instanceCounter--;
	System::Console::WriteLine("ADAMS - Destructor Called! -{0}", instanceCounter);
    System::Diagnostics::Debug::WriteLine("\n\nADAMS DESTRUCTOR called! - {0}", instanceCounter);
}

AdamsHal::!AdamsHal()
{
    instanceCounter--;
	System::Console::WriteLine("ADAMS - FINALIZER CALLED! -{0}", instanceCounter);
    System::Diagnostics::Debug::WriteLine("\n\nADAMS FINALIZER called! - {0}", instanceCounter);
}

void AdamsHal::testSleep(double^ inTime)
{   
    System::Console::WriteLine("Sleeping for {0} time", inTime);
    System::Threading::Thread::Sleep(System::TimeSpan::FromMilliseconds(safe_cast<double>(inTime) ) );
}


int AdamsHal::getChannelData(std::vector<double> *inputVec)
{
    System::String ^test = "";
    double d_response = 0;
    bool b_check = false;

    System::Console::WriteLine("Acquiring data from ADAMS unit.....");
    System::Threading::Thread::Sleep(System::TimeSpan::FromMilliseconds(1200));


    for (int i = 0; System::Convert::ToInt16(i) < 2; i++)
    {
        if (i == 0)
        {
            test = L"0-10.00";
        }

        else // modify to if contains this error
        {
            test = L"-10.00";
        }

        // Attempt to conver the value to a double
        try
        {
            //b_check = Double::TryParse(test, d_response);
            d_response = Convert::ToDouble(test);   // Throw error
            
            
            System::Console::WriteLine("bcheck: {0}", b_check);

        }
        catch (System::FormatException ^err_msg) // With Double::TryParse ,it no longer throws the exception
        {
            //Console::WriteLine("error message: {}", *err_msg);
            //Console::WriteLine("Error invalid input{} {}", test, err_msg);
            System::Console::WriteLine(err_msg->GetType()->Name + ": error thrown!!!\n\n");
            System::Console::WriteLine("\n\n fixing data...{0}", test);

            int length = System::Convert::ToInt32(test->Length);


            test = test->Substring(1, 5);
            System::Console::WriteLine("\nNew converted string: {0}", test);

            if (Double::TryParse(test, d_response)) {
                System::Console::WriteLine("{0} -Converted to double: {1}", i, d_response);
            }
            else {
                System::Console::WriteLine("{0} - Failed conversion: {1}", i, test);
            }
        }


    }
    return -1;
}

int AdamsHal::getChannelDataFixed(std::vector<double> *inputVec)
{
    System::String^ voltage_readings = L"0-10.00";
    double d_response = Convert::ToDouble(0);
    bool^   b_check = false;

    System::Console::WriteLine("Acquiring data from ADAMS unit.....");
    System::Threading::Thread::Sleep(System::TimeSpan::FromMilliseconds(1200));


    for (int i = 0; i < 2; i++)
    {
        if (i == 0) {
            voltage_readings = L"0-10.00";  // Add a second function to parse inteligently for this!
        }
        else if (i == 1 ) {
            voltage_readings = L"-10.00";
        }
        
        double digit = safe_cast<double>(d_response);

        if (Double::TryParse(voltage_readings, d_response)) {
            System::Console::Write("\n{0} - Conversion SUCCESS! {1}\t", i, d_response);
            inputVec->push_back(d_response);
        }
        else {
            String^ temp_str = L"";

            // Note the Substring(x, (string->Length)- x) you have to subtract the string, bc it will be cut in the buffer
            temp_str = voltage_readings->Substring(1, (voltage_readings->Length) -1 );

            System::Console::Write("\n{0} - Conversion FAILED! {1} -RECOVERTED: {2}\t", i, voltage_readings, temp_str);
        }
    }

    return 0;


}




