#include "infotabelle.hh"

InfoTabelle::InfoTabelle(QWidget *parent) :
    Tabelle(parent)
{
	infomodel = new QSqlQueryModel();
}