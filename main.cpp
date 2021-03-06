#include <QtGui/QApplication>
#include "mainwindow.hh"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QString locale = QLocale::system().name();
	QTranslator translator;
	translator.load(QString("meinsql_") + locale);
	a.installTranslator(&translator);

    Mainwindow w;
    w.show();
    return a.exec();
}
