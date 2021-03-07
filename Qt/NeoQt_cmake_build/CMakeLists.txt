cmake_minimum_required(VERSION 3.1.0)

project(NeoQtcm)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (CMAKE_VERSION VERSION_LESS "3.7.0")
	set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# find_package(Qt5Widgets)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(Qt5_DIR "/opt/qt/5.8.0/5.8/gcc_64/lib/cmake/Qt5Core")
set(Qt5Core_DIR "/opt/qt/5.8.0/5.8/gcc_64/lib/cmake/Qt5Core")
set(Qt5widgets_DIR "/opt/qt/5.8.0/5.8/gcc_64/lib/cmake/Qt5Widgets")
set(QT_QMAKE_EXECUTABLE "/opt/qt/5.8.0/5.8/gcc_64/bin/qmake")

# QT5_WRAP_CPP(Cmake_hdr_moc mainwindow.h)
# QT5_WRAP_UI(Cmake_form_hdr mainwindow.ui)

# add_library(mainwindow ${Cmake_hdr_moc} ${Cmake_form_hdr})
# qt5_use_modules(mainwindow Widgets)

# add_executable(Cmake main.cpp mainwidget.cpp)
add_executable(NeoQtcm main.cpp mainwidget.cpp)

# This line and syntax must be used.
qt5_use_modules(NeoQtcm Core Gui Widgets)




# find_package(Qt4 COMPONENTS QtCore QtGui QtNetwork QtWidgets REQUIRED)
# find_package(Qt5 COMPONENTS Widgets REQUIRED)




# target_link_libararies(NeoQtcm Qt5::widgets)

