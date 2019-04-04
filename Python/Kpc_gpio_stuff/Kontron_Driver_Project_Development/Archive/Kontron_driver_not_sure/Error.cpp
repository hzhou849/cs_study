// Copyright 2016 Covidien LP.
// All Rights Reserved. The information contained herein is confidential
// property of Covidien. The use, copying, transfer or disclosure of such
// information is prohibited except by written agreement with Covidien.

#include "einstein/os/info/Error.h"
#include <errno.h>
#include <string.h>
#include <sstream>

namespace
{

class os_error_category :
    public std::error_category
{
public:
    virtual const char * name() const override
    {
        return "os_wrapper_error";
    }

    virtual std::string message(int condition) const override
    {
        return strerror(condition);
    }
};


std::string MakeDiagnosisMessage(const std::string & function, const char * file, const int line
                                )
{
    std::stringstream message;
    message << "'" << function;
    if (file)
    {
        message << "' failed at '" << file << ":" << line << "' ";
    }
    return message.str();
}

}

namespace einstein
{
namespace os
{
namespace info
{

Error::Error(const std::string & function, const int error_number) :
    Error(function, error_number, nullptr, 0)
{
}

Error::Error(const std::string & function, const int error_number, const char * file, const int line) :
    std::system_error(error_number, os_error_category(), MakeDiagnosisMessage(function, file, line))
{
}


}
}
}
