/* QT Tutorial from
 * https://www.linux.org/threads/c-tutorial-create-qt-applications-without-qtcreator.18409/
 */

#include <QtWidgets>
#include "mainwidget.h"

//Constructor for main widget
MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
	button_ = new QPushButton(tr("Push Me!"));
	textBrowser_ = new QTextBrowser();

	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(button_,0,0);
	mainLayout->addWidget(textBrowser_,1,0);
	setLayout(mainLayout);
	setWindowTitle(tr("Connecting buttons to process.."));
}

//Destructor
MainWidget::~MainWidget()
{
	delete button_;
	delete textBrowser_;
}