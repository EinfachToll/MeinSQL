#include <QtGui/QApplication>
#include "hauptfenster.hh"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Hauptfenster w;
    w.show();
    return a.exec();
}
