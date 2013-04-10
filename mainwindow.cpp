#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QSqlTableModel>
#include <QMenu>

Mainwindow::Mainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mainwindow)
{
    ui->setupUi(this);
	show_if_connected.setText(tr("Not connected"));
	ui->statusBar->addWidget(&show_if_connected);
	this->query.setForwardOnly(true);
	this->changed_tab=false;


	infotable = new Infotable();
	this->infotable_layout = new QHBoxLayout(this->ui->tab_4);
	this->infotable_layout->addWidget(this->infotable);

	querytable = new Querytable();
	this->querytable_layout = new QHBoxLayout(this->ui->tab_2);
	this->querytable_layout->addWidget(this->querytable);

	this->sqltabletable = new SQLtabletable();
	this->sqltabletable->infomodel = infotable->infomodel;
	ui->verticalLayout_SQLTab->addWidget(this->sqltabletable);
	this->querytextedit = new Querytextedit(this);
	ui->horizontalLayout->addWidget(this->querytextedit);

	this->ui->toolButton->setMenu(hist_menu);
	connect(this->querytextedit, SIGNAL(new_query(QString)), this->querytable, SLOT(set_query(QString)));
	connect(this->querytable, SIGNAL(error_occurred(bool)), this, SLOT(new_query(bool)));
	connect(this->querytable, SIGNAL(error_occurred(bool)), this->querytextedit, SLOT(errors_occured(bool)));
}

Mainwindow::~Mainwindow()
{
    delete ui;
}

void Mainwindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Mainwindow::on_pushButton_Connect_clicked()
{
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName(settingswindow.host);
	db.setPort(settingswindow.port);
	db.setDatabaseName(settingswindow.initial_db_name);
	db.setUserName(settingswindow.username);
	db.setPassword(settingswindow.password);
	if(!db.open())
	{
		qDebug() << tr("Error");
		this->ui->statusBar->showMessage(tr("Connection error"), 10000);
		return;
	}
	show_if_connected.setText(tr("Connected"));
	qDebug() << "Connected";
	this->ui->pushButton_Connect->setDisabled(true);
	this->ui->pushButton_Trennen->setEnabled(true);

	QSqlQuery query;
	query.exec("SHOW DATABASES;");
	qDebug() << query.lastError().text();
	//perform_sql_query("SHOW DATABASES", false);
	while (/*this->query*/query.next()) {
		  QString dbname = /*this->query*/query.value(0).toString();
		  this->ui->listWidget_DBs->addItem(dbname);
	}
}

void Mainwindow::on_pushButton_clicked()
{
	settingswindow.show();
}

void Mainwindow::perform_sql_query(QString query/*, bool show_result*/)
{
	this->query.exec(query);
	this->ui->plainTextEdit_Log->appendPlainText(query);
	this->ui->plainTextEdit_Log->appendPlainText(this->query.lastError().text());
	this->ui->statusBar->showMessage(query, 5000);
}

void Mainwindow::on_pushButton_Trennen_clicked()
{
	db.close();
	show_if_connected.setText(tr("Not connected"));
	this->ui->pushButton_Connect->setEnabled(true);
	this->ui->pushButton_Trennen->setDisabled(true);
	this->ui->listWidget_DBs->clear();
	this->ui->listWidget_Tables->clear();
	this->sqltabletable->clear();
}


void Mainwindow::on_listWidget_DBs_itemActivated(QListWidgetItem* item)
{
	//qDebug() << "Datenbank " << item->text() << " ausgewählt";
	this->ui->listWidget_Tables->clear();
	QSqlQuery query;
	query.exec("USE " + item->text() + ";");
	query.exec("SHOW TABLES;");
	while (query.next()) {
		  QString table_name = query.value(0).toString();
		  this->ui->listWidget_Tables->addItem(table_name);
	}
}

void Mainwindow::on_listWidget_Tables_itemActivated(QListWidgetItem* item)
{
	//qDebug() << "Tabelle " << item->text() << " ausgewählt";
	infotable->infomodel->setQuery("DESCRIBE " + item->text() + ";");

	this->infotable->setModel(infotable->infomodel);
	//this->infotable->resizeColumnsToContents();
	this->infotable->show();

	this->sqltabletable->set_table(item->text());

	if(ui->tabWidget->currentIndex()==0 || ui->tabWidget->currentIndex()==3)
		ui->tabWidget->setCurrentIndex(1);

	if(ui->tabWidget->currentIndex()==1)
		this->sqltabletable->draw();
	else
		this->changed_tab = true;
}

void Mainwindow::on_pushButton_2_clicked()
{
	this->close();
}

void Mainwindow::new_query(bool errors)
{
	if(errors)
	{
		ui->plainTextEdit_Log->appendPlainText(querytable->last_error);
		ui->tabWidget->setCurrentIndex(0);
	}
	else
		ui->tabWidget->setCurrentIndex(3);
}
