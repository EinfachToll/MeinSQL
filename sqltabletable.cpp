#include "sqltabletable.hh"
#include <QHeaderView>
#include <QDebug>
#include <QSqlRecord>

SQLtabletable::SQLtabletable(QWidget* parent) :
	Table(parent)
{
	this->table = "";
	this->setSortingEnabled(false);
	//this->model = new QSqlQueryModel();
	//this->setModel(this->model);
	this->setSelectionBehavior(QAbstractItemView::SelectItems);
}

SQLtabletable::~SQLtabletable()
{
}

void SQLtabletable::draw()
{
	qDebug() << table << sort_by;
	//model->setSort(0, Qt::DescendingOrder); //frag mich ma, warum das nich funktioniert!!!
	model->setTable(table);
	QString filterstring = "true";
	if(sort_by != "")
		filterstring += " ORDER BY " + sort_by + sort_asc_or_desc;
	filterstring += " LIMIT " + limit;
	qDebug() << filterstring;
	model->setFilter(filterstring);		//mieser Hack
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model->select();

	this->setModel(model);
	this->resize_columns();
	this->show();

	/*
	QString query = "SELECT * FROM " + this->table;
	if(this->sort_by != "")
		query += " ORDER BY " + sort_by + sort_asc_or_desc;
	query += " LIMIT " + limit;
	set_query(query);
	*/

	/*
	this->ui->tableWidget_Table->setRowCount(model->rowCount() + 1);
	this->ui->tableWidget_Table->setColumnCount(model->columnCount());
	//this->ui->tableWidget_Table->resizeColumnsToContents();		//funktioniert nicht recht

	this->ui->tableWidget_Table->blockSignals(true);		//damit beim Füllen nicht ständig ein Signal kommt

	for(int j=0; j<model->columnCount(); ++j) {
		for (int i = 0; i < model->rowCount(); ++i)
			this->ui->tableWidget_Table->setItem(i, j, new QTableWidgetItem(QString::fromUtf8(model->record(i).value(j).toString().toAscii())));
		this->ui->tableWidget_Table->setHorizontalHeaderItem(j, new QTableWidgetItem(model->headerData(j, Qt::Horizontal).toString()));
		this->ui->tableWidget_Table->setItem(this->ui->tableWidget_Table->rowCount()-1, j, new QTableWidgetItem(""));
	}
	this->ui->tableWidget_Table->blockSignals(false);
	*/

	//sort(0);
}

void SQLtabletable::set_query(QString qu) //was soll das?
{
	qDebug() << qu;
	//this->sort_by = "";
	//sort_asc_or_desc = " DESC";
	//this->model->setQuery(qu);
	this->resize_columns();
	this->show();
}

void SQLtabletable::clear()
{
	this->table = "";
	this->draw();
}

void SQLtabletable::set_table(QString table)
{
	model = new QSqlTableModel;
	this->limit = "1000";
	sort_asc_or_desc = " DESC";
	sort_by = "";
	this->table = table;
}

void SQLtabletable::sort(int column_nr)
{
	QString clicked = infomodel->record(column_nr).value("FIELD").toString();
	if(clicked==sort_by)
		sort_asc_or_desc = sort_asc_or_desc==" DESC" ? " ASC" : " DESC";
	else
	{
		sort_by = clicked;
		sort_asc_or_desc = " ASC";
	}

	/*if(sort_by == spalte)
		sort_asc_or_desc = sort_asc_or_desc==Qt::DescendingOrder ? Qt::AscendingOrder : Qt::DescendingOrder;
	else
	{
		sort_by = spalte;
		sort_asc_or_desc = Qt::AscendingOrder;
	}*/
	//model->setSort(sort_by, sort_asc_or_desc);
	//model->select();
	//sort_by = -1;
	draw();
	qDebug() << "asdfasdfasfd" << column_nr << sort_asc_or_desc;
	/*malen();
	this->show();
	*/
}

void SQLtabletable::filter(QString)
{
}

/*
void Mainwindow::on_pushButton_3_clicked()
{
	//qDebug() << "Also ich versuch mal, unter Zeile " << this->ui->tableWidget_Table->selectedIndexes().row();
}

void Mainwindow::on_tableWidget_Table_itemChanged(QTableWidgetItem* item)
{
   qDebug() << item->text()+" sf";
}

void Mainwindow::on_pushButton_5_clicked()
{
	if(!this->neue_Zeilen.isEmpty())
	{
		QSqlRecord rec = this->model->record();
		for(int z=0; z<this->neue_Zeilen.count(); ++z)
		{
			for(int i=0; i<ui->tableWidget_Table->columnCount(); ++i)
				rec.setValue(i, ui->tableWidget_Table->item(this->neue_Zeilen.at(z), i)->text());
				//rec.field(i).setValue(ui->tableWidget_Table->item(this->neue_Zeilen.at(z), i)->text());

			if(!this->model->insertRecord(-1, rec))
				qDebug() << "Eiweh!";

			ui->tableWidget_Table->setVerticalHeaderItem(this->neue_Zeilen.at(z), new QTableWidgetItem(QString::number(
					this->neue_Zeilen.at(z))));
		}
	}

	this->model->submitAll();
	this->ui->pushButton_5->setDisabled(true);
	this->neue_Zeilen.clear();
	this->bearbeitete_Zeilen.clear();
}

void Mainwindow::on_tableWidget_Table_cellChanged(int row, int column)
{
	qDebug() << "Auweia! In Zelle " << row << " " << column << " hat sich was getan!";
	this->ui->pushButton_5->setEnabled(true);
	this->ui->tableWidget_Table->setVerticalHeaderItem(row, new QTableWidgetItem("*"));
	if(row==ui->tableWidget_Table->rowCount()-1)		//neue Zeile
	{
		ui->tableWidget_Table->setRowCount(ui->tableWidget_Table->rowCount()+1);
		this->neue_Zeilen.append(row);
	}
	else		//Zeile wurde bearbeitet
	{
		this->bearbeitete_Zeilen.append(row);
	}
}

void Mainwindow::on_tabWidget_currentChanged(int index)
{
	if(index==1 && this->changed_tab)
		draw_table();
}

void Mainwindow::on_tableWidget_Table_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn)
{
	qDebug() << "Nu aber:" << currentColumn;
}

void Mainwindow::on_pushButton_6_clicked()
{
	this->infotable->sortByColumn(1);
	this->ui->tableWidget_Table->setSortingEnabled(true);
	this->ui->tableWidget_Table->sortByColumn(2);
}
*/
