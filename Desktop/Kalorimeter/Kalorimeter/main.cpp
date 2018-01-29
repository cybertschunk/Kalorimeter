#include "Kalorimeter.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Kalorimeter w;
	w.show();
	return a.exec();
}
