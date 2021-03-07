/* QCORE tutorial 1
 *
 * Tutorial on how to compile first QCore project
 * This is a sample tested version of of my cmake file that builds with Qt

 *1) copy this into a CMakeLists.txt file
 *2) run 'cmake .' for current directory
 *3) run 'make' to build the project
 *================================================
 *cmake_minimum_required(VERSION 3.1.0)
 *
 *project(project_name)
 *
 *set(CMAKE_AUTOMOC ON)
 *set(CMAKE_AUTORCC ON)
 *set(CMAKE_AUTOUIC ON)
 *
 *#include current folder for header .h files
 *if (CMAKE_VERSION VERSION_LESS "3.7.0")
 *	set(CMAKE_INCLUDE_CURRENT_DIR ON)
 *endif()
 *
 *# find_package(Qt5Widgets)
 *find_package(Qt5 COMPONENTS Widgets REQUIRED)
 *
 *set(Qt5_DIR "/opt/qt/5.8.0/5.8/gcc_64/lib/cmake/Qt5Core")
 *set(Qt5Core_DIR "/opt/qt/5.8.0/5.8/gcc_64/lib/cmake/Qt5Core")
 *set(Qt5widgets_DIR "/opt/qt/5.8.0/5.8/gcc_64/lib/cmake/Qt5Widgets")
 *set(QT_QMAKE_EXECUTABLE "/opt/qt/5.8.0/5.8/gcc_64/bin/qmake")
 *
 *
 *add_executable(project_name main.cpp mainwidget.cpp)
 *qt5_use_modules(project_name Core Gui Widgets)


 * 
*/

#include <QCoreApplication>
#include <QDebug>


int main(int argc, char *argv[])
{
	QCoreApplication a (argc, argv);
	qDebug() << "Hello World";

	return a.exec(); // this will return the exit code 
}