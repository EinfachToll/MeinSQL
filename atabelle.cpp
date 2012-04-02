#include "atabelle.hh"
#include <iostream>
#include <QStringList>
#include <QDebug>

ATabelle::ATabelle(QWidget *parent) :
    Tabelle(parent)
{
	//this->abfrmodell = new QSqlQueryModel();
}

void ATabelle::setze_Abfrage(QString abfr)
{
	QStringList abfragen = abfr.split(QRegExp(";\\s*\n"), QString::SkipEmptyParts);

	foreach(QString abfrage, abfragen)
	{
		QSqlQueryModel* tempmodel = new QSqlQueryModel();//die muss man natürlich auch mal wieder löschen


		tempmodel->setQuery(abfrage);
		modelliste << tempmodel;

		if(tempmodel->lastError().type() != 0)
		{
			letzte_Fehler = tempmodel->lastError().text();
			emit fehler(true);
			return;
		}
	}

	for(int i=modelliste.count()-1; i>=0; --i)
	{
		//das mit rowcount funktioniert möglicherweise nicht für alle DBSe
		if(modelliste.at(i)->rowCount() > 0)
		{
			this->setModel(modelliste.at(i));
			this->resizeColumnsToContents();
			this->show();
			emit fehler(false);
			break;
		}
	}
}

void ATabelle::filtern(QString)
{
}

void ATabelle::sortieren(int)
{

}
