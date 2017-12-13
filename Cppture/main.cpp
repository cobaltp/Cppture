#include "stdafx.h"
#include "Cppture.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Cppture w;

	a.setQuitOnLastWindowClosed(false);

	return a.exec();
}
