#include "sqltabelle.hh"
#include <QHeaderView>
#include <QDebug>
#include <QSqlRecord>

SQLTabelle::SQLTabelle(QWidget* parent) :
	Tabelle(parent)
{
	this->tabelle = "";
	this->setSortingEnabled(false);
	//this->model = new QSqlQueryModel();
	//this->setModel(this->model);
	this->setSelectionBehavior(QAbstractItemView::SelectItems);
}

SQLTabelle::~SQLTabelle()
{
}

void SQLTabelle::malen()
{
	qDebug() << tabelle << sortierennach;
	//model->setSort(0, Qt::DescendingOrder); //frag mich ma, warum das nich funktioniert!!!
	model->setTable(tabelle);
	QString filterstring = "true";
	if(sortierennach != "")
		filterstring += " ORDER BY " + sortierennach + sortierenrichtung;
	filterstring += " LIMIT " + limit;
	qDebug() << filterstring;
	model->setFilter(filterstring);		//mieser Hack
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model->select();

	this->setModel(model);
	this->spalten_richten();
	this->show();

	/*
	QString query = "SELECT * FROM " + this->tabelle;
	if(this->sortierennach != "")
		query += " ORDER BY " + sortierennach + sortierenrichtung;
	query += " LIMIT " + limit;
	set_query(query);
	*/

	/*
	this->ui->tableWidget_Tabelle->setRowCount(model->rowCount() + 1);
	this->ui->tableWidget_Tabelle->setColumnCount(model->columnCount());
	//this->ui->tableWidget_Tabelle->resizeColumnsToContents();		//funktioniert nicht recht

	this->ui->tableWidget_Tabelle->blockSignals(true);		//damit beim Füllen nicht ständig ein Signal kommt

	for(int j=0; j<model->columnCount(); ++j) {
		for (int i = 0; i < model->rowCount(); ++i)
			this->ui->tableWidget_Tabelle->setItem(i, j, new QTableWidgetItem(QString::fromUtf8(model->record(i).value(j).toString().toAscii())));
		this->ui->tableWidget_Tabelle->setHorizontalHeaderItem(j, new QTableWidgetItem(model->headerData(j, Qt::Horizontal).toString()));
		this->ui->tableWidget_Tabelle->setItem(this->ui->tableWidget_Tabelle->rowCount()-1, j, new QTableWidgetItem(""));
	}
	this->ui->tableWidget_Tabelle->blockSignals(false);
	*/

	//sortieren(0);
}

void SQLTabelle::set_query(QString qu) //was soll das?
{
	qDebug() << qu;
	//this->sortierennach = "";
	//sortierenrichtung = " DESC";
	//this->model->setQuery(qu);
	this->spalten_richten();
	this->show();
}

void SQLTabelle::leeren()
{
	this->tabelle = "";
	this->malen();
}

void SQLTabelle::setTabelle(QString tabelle)
{
	model = new QSqlTableModel;
	this->limit = "1000";
	sortierenrichtung = " DESC";
	sortierennach = "";
	this->tabelle = tabelle;
}

void SQLTabelle::sortieren(int spalte)
{
	QString geklickt = infomodel->record(spalte).value("FIELD").toString();
	if(geklickt==sortierennach)
		sortierenrichtung = sortierenrichtung==" DESC" ? " ASC" : " DESC";
	else
	{
		sortierennach = geklickt;
		sortierenrichtung = " ASC";
	}

	/*if(sortierennach == spalte)
		sortierenrichtung = sortierenrichtung==Qt::DescendingOrder ? Qt::AscendingOrder : Qt::DescendingOrder;
	else
	{
		sortierennach = spalte;
		sortierenrichtung = Qt::AscendingOrder;
	}*/
	//model->setSort(sortierennach, sortierenrichtung);
	//model->select();
	//sortierennach = -1;
	malen();
	qDebug() << "asdfasdfasfd" << spalte << sortierenrichtung;
	/*malen();
	this->show();
	*/
}

void SQLTabelle::filtern(QString)
{
}

/*
void Hauptfenster::on_pushButton_3_clicked()
{
	//qDebug() << "Also ich versuch mal, unter Zeile " << this->ui->tableWidget_Tabelle->selectedIndexes().row();
}

void Hauptfenster::on_tableWidget_Tabelle_itemChanged(QTableWidgetItem* item)
{
   qDebug() << item->text()+" sf";
}

void Hauptfenster::on_pushButton_5_clicked()
{
	if(!this->neue_Zeilen.isEmpty())
	{
		QSqlRecord rec = this->model->record();
		for(int z=0; z<this->neue_Zeilen.count(); ++z)
		{
			for(int i=0; i<ui->tableWidget_Tabelle->columnCount(); ++i)
				rec.setValue(i, ui->tableWidget_Tabelle->item(this->neue_Zeilen.at(z), i)->text());
				//rec.field(i).setValue(ui->tableWidget_Tabelle->item(this->neue_Zeilen.at(z), i)->text());

			if(!this->model->insertRecord(-1, rec))
				qDebug() << "Eiweh!";

			ui->tableWidget_Tabelle->setVerticalHeaderItem(this->neue_Zeilen.at(z), new QTableWidgetItem(QString::number(
					this->neue_Zeilen.at(z))));
		}
	}

	this->model->submitAll();
	this->ui->pushButton_5->setDisabled(true);
	this->neue_Zeilen.clear();
	this->bearbeitete_Zeilen.clear();
}

void Hauptfenster::on_tableWidget_Tabelle_cellChanged(int row, int column)
{
	qDebug() << "Auweia! In Zelle " << row << " " << column << " hat sich was getan!";
	this->ui->pushButton_5->setEnabled(true);
	this->ui->tableWidget_Tabelle->setVerticalHeaderItem(row, new QTableWidgetItem("*"));
	if(row==ui->tableWidget_Tabelle->rowCount()-1)		//neue Zeile
	{
		ui->tableWidget_Tabelle->setRowCount(ui->tableWidget_Tabelle->rowCount()+1);
		this->neue_Zeilen.append(row);
	}
	else		//Zeile wurde bearbeitet
	{
		this->bearbeitete_Zeilen.append(row);
	}
}

void Hauptfenster::on_tabWidget_currentChanged(int index)
{
	if(index==1 && this->andere_Tab)
		tabelle_malen();
}

void Hauptfenster::on_tableWidget_Tabelle_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	qDebug() << "Nu aber:" << currentColumn;
}

void Hauptfenster::on_pushButton_6_clicked()
{
	this->tabel_beschr->sortByColumn(1);
	this->ui->tableWidget_Tabelle->setSortingEnabled(true);
	this->ui->tableWidget_Tabelle->sortByColumn(2);
}
*/
