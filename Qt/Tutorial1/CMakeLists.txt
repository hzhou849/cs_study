cmake_minimum_required(VERSION 3.1.0)

project(main)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#include current folder for header .h files
if (CMAKE_VERSION VERSION_LESS "3.7.0")
	set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# find package(Qt5Widgets)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(Qt5_DIR "/opt/qt/5.8.0/5.8/gcc_64/lib/cmake/Qt5Core")
set(Qt5Core_DIR "/opt/qt/5.8.0/5.8/gcc_64/lib/cmake/Qt5Core")
set(Qt5widgets_DIR "/opt/qt/5.8.0/5.8/gcc_64/lib/cmake/Qt5Widgets")
set(QT_QMAKE_EXECUTABLE "/opt/qt/5.8.0/5.8/gcc_64/bin/qmake")

add_executable(main main.cpp)
qt5_use_modules(main Core Gui Widgets)