#include "infotabelle.hh"

InfoTabelle::InfoTabelle(QWidget *parent) :
    Tabelle(parent)
{
	infomodel = new QSqlQueryModel();
}

void InfoTabelle::sortieren(int)
{
}

void InfoTabelle::filtern(QString)
{
}
