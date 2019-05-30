# Copyright 2017 Covidien LP
# All Rights Reserved. The information contained herein is confidential
# property of Covidien LP. The use, copying, transfer or disclosure of such
# information is prohibited except by express written agreement with Covidien LP.

project(Cpu_Monitor)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC library_kontron_driver
    INTERFACE ${Boost_LIBRARIES}
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION ${INSTALL_LIB}
    ARCHIVE DESTINATION ${INSTALL_LIB}
)
