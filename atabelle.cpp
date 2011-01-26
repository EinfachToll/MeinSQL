#include "atabelle.hh"

ATabelle::ATabelle(QWidget *parent) :
    Tabelle(parent)
{
	this->abfrmodell = new QSqlQueryModel();
}
#include <iostream>
void ATabelle::setzAbfr(QString abfr)
{
	std::cout << abfr.toStdString() << "\n";
	this->abfrmodell->setQuery(abfr);

	if(this->abfrmodell->lastError().type() != 0)
	{
		//this->ui->plainTextEdit_Log->appendPlainText(tablemodel->lastError().text());
		//this->ui->tabWidget->setCurrentIndex(0);
	}
	else
	{
		this->setModel(this->abfrmodell);
		this->resizeColumnsToContents();
		this->show();
		//this->ui->tabWidget->setCurrentIndex(3);
	}
}

/*void Hauptfenster::on_lineEdit_Abfrage_returnPressed()
{
	QSqlQueryModel* tablemodel = new QSqlQueryModel();
	tablemodel->setQuery(this->query_history->text());
}*/
