#include "querytable.hh"
#include <iostream>
#include <QStringList>
#include <QDebug>

Querytable::Querytable(QWidget *parent) :
    Table(parent)
{
	//this->abfrmodell = new QSqlQueryModel();
}

void Querytable::set_query(QString query)
{
	QStringList queries = query.split(QRegExp(";\\s*\n"), QString::SkipEmptyParts);

	foreach(QString q, queries)
	{
		QSqlQueryModel* tempmodel = new QSqlQueryModel();//die muss man natürlich auch mal wieder löschen


		tempmodel->setQuery(q);
		list_of_models << tempmodel;

		if(tempmodel->lastError().type() != 0)
		{
			last_error = tempmodel->lastError().text();
			emit error_occurred(true);
			return;
		}
	}

	for(int i=list_of_models.count()-1; i>=0; --i)
	{
		//das mit rowcount funktioniert möglicherweise nicht für alle DBSe
		if(list_of_models.at(i)->rowCount() > 0)
		{
			this->setModel(list_of_models.at(i));
			this->resizeColumnsToContents();
			this->show();
			emit error_occurred(false);
			break;
		}
	}
}

void Querytable::filter(QString)
{
}

void Querytable::sort(int)
{

}
