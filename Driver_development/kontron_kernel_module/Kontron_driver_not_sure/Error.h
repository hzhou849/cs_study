// Copyright 2016 Covidien LP.
// All Rights Reserved. The information contained herein is confidential
// property of Covidien. The use, copying, transfer or disclosure of such
// information is prohibited except by written agreement with Covidien.

#ifndef EINSTEIN_OS_INFO_ERROR_H
#define EINSTEIN_OS_INFO_ERROR_H

#include <system_error>
#include <string>

namespace einstein
{
namespace os
{
namespace info
{

/// Wraps error codes set by system calls into exceptions.
/// This includes POSIX "errno" codes as well as OS specific ones.
/// The exception can be augmented with information about the context it is thrown from.
/// \author Jan Tully
class Error :
    public std::system_error
{
public:
    Error(const std::string & function, const int error_number);
    Error(const std::string & function, const int error_number, const char * file, const int line);
};

}
}
}

#endif //EINSTEIN_OS_INFO_ERROR_H
