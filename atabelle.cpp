#include "atabelle.hh"
#include <iostream>
#include <QStringList>
#include <QDebug>

ATabelle::ATabelle(QWidget *parent) :
    Tabelle(parent)
{
	//this->abfrmodell = new QSqlQueryModel();
}

void ATabelle::setzAbfr(QString abfr)
{
	QStringList queries = abfr.split(QRegExp(";\\s*\n"), QString::SkipEmptyParts);

	for(int i=0; i<queries.count(); ++i)
	{
		QSqlQueryModel* tempmodel = new QSqlQueryModel();
		tempmodel->setQuery(queries.at(i));
		modellist << tempmodel;

		if(tempmodel->lastError().type() != 0)
		{
			last_Errors = tempmodel->lastError().text();
			emit errors(true);
			return;
		}
	}

	for(int i=modellist.count()-1; i>=0; --i)
	{
		//das mit rowcount funktioniert möglicherweise nicht für alle DBSe
		if(modellist.at(i)->rowCount() > 0)
		{
			this->setModel(modellist.at(i));
			this->resizeColumnsToContents();
			this->show();
			emit errors(false);
			break;
		}
	}
}
