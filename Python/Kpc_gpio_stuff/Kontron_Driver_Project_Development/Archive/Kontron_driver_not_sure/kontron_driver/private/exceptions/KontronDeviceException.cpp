// Copyright 2017 Covidien LP.
// All Rights Reserved. The information contained herein is confidential
// property of Covidien. The use, copying, transfer or disclosure of such
// information is prohibited except by written agreement with Covidien.

#include "einstein/kontron_driver/exceptions/KontronDeviceException.h"

namespace einstein
{
namespace kontron_driver
{
namespace exceptions
{

KontronDeviceException::KontronDeviceException(const std::string & message) :
    std::runtime_error(message)
{
}

}
}
}
