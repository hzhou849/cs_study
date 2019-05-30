// Copyright 2017 Covidien LP.
// All Rights Reserved. The information contained herein is confidential
// property of Covidien. The use, copying, transfer or disclosure of such
// information is prohibited except by written agreement with Covidien.

#ifndef EINSTEIN_KONTRON_DRIVER_EXCEPTIONS_KONTRONDEVICEEXCEPTION_H
#define EINSTEIN_KONTRON_DRIVER_EXCEPTIONS_KONTRONDEVICEEXCEPTION_H

#include <stdexcept>

namespace einstein
{
namespace kontron_driver
{
namespace exceptions
{

/// \addtogroup library_kontron_driver
/// @{

/// \file KontronDeviceException.h

/// \brief Exception to report IO memory region and register status exceptions from the kontron driver
class KontronDeviceException : public std::runtime_error
{
public:

    /// \brief Constructor
    /// \param[in] message - error message of the exception
    explicit KontronDeviceException(const std::string & message);

    /// \brief Default destructor
    ~KontronDeviceException() = default;

};

///@}

}
}
}

#endif
