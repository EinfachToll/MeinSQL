#include "infotable.hh"

Infotable::Infotable(QWidget *parent) :
    Table(parent)
{
	infomodel = new QSqlQueryModel();
}

void Infotable::sort(int)
{
}

void Infotable::filter(QString)
{
}
