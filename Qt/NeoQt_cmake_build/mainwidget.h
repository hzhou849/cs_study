#ifndef _MAINWIDGET_H
#define _MAINWIDGET_H

#include <QWidget>


/*Now you may be wondering "Why didn't we #include the header files for QPushButton and QTextBrowser?".
 * The answer to that question is:
 * Because our class only stores pointers to a QPushButton and a QTextBrowser.
 * Pointers always have the same size - regardless of the size of the object they point to. 
 * So we can forward-declare the objects that they point to - which means that we will have to #include 
 * their headers in our implementation (.cpp) file.
 * 
 * So at this point, because we've used forward declarations - the compiler knows that our class contains 
 * two pointers to two different classes that will be fully defined later on. And the compiler already knows 
 * the size of a pointer - it already knows how much memory will be used by each of the pointers, even though 
 * it doesn't know anything about the classes themselves. So it will look for the complete definition of 
 * those classes in our implementation (.cpp) file.
 */ 

 class QPushButton;
 class QTextBrowser;

 // This is the declaration of our MainWidget class
 // The definition/implementation is in mainwidget.cpp
 class MainWidget : public QWidget
 {
	// This is a pre-processor macro used by QT build tools
	Q_OBJECT

	public:
		explicit MainWidget(QWidget *parent = 0); //Constructor
		~MainWidget();							  // Destructor
	
	private:
		QPushButton * button_;
		QTextBrowser* textBrowser_;
 };

 #endif //_MAINWIDGET_H