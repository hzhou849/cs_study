# Copyright 2017 Covidien LP
# All Rights Reserved. The information contained herein is confidential
# property of Covidien LP. The use, copying, transfer or disclosure of such
# information is prohibited except by express written agreement with Covidien LP.

project(library_kontron_driver)

set(HEADER_FILES
    public/einstein/kontron_driver/DeviceDriver.h
    public/einstein/kontron_driver/Device.h
    public/einstein/kontron_driver/exceptions/KontronDeviceException.h
)

set(SOURCE_FILES
    private/DeviceDriver.cpp
    private/Device.cpp
    private/exceptions/KontronDeviceException.cpp
)

add_library(${PROJECT_NAME}
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC public
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC library_os_wrapper
)

