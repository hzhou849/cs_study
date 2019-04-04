// Copyright 2016 Covidien LP.
// All Rights Reserved. The information contained herein is confidential
// property of Covidien. The use, copying, transfer or disclosure of such
// information is prohibited except by written agreement with Covidien.

#ifndef EINSTEIN_OS_IO_DEVICEACCESS_H
#define EINSTEIN_OS_IO_DEVICEACCESS_H

namespace einstein
{
namespace os
{
namespace io
{

enum class DeviceAccess
{
    NONE,
    READ,
    WRITE,
    READ_WRITE
};

}
}
}

#endif //EINSTEIN_OS_IO_DEVICEACCESS_H
