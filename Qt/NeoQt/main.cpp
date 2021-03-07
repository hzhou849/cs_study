#include <QtWidgets>
#include <QtWidgets/QtWidgetsDepends>
#include "mainwidget.h"

int main(int argc, char *argv[])
{
	// Creates an instance of QApplication
	QApplication a(argc, argv);

	// This is our MainWidget class containing our GUI and functionality
	MainWidget w;
	w.show(); // show main window

	// Run the applicaiton and return execs() return value/code
	return a.exec();
}

