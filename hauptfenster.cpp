#include "hauptfenster.hh"
#include "ui_hauptfenster.h"

#include <QSqlTableModel>
#include <QMenu>

Hauptfenster::Hauptfenster(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Hauptfenster)
{
    ui->setupUi(this);
	Label_verbunden.setText(tr("Nicht verbunden"));
	ui->statusBar->addWidget(&Label_verbunden);
	this->abfrage.setForwardOnly(true);
	this->andere_Tab=false;


	tabel_beschr = new ATabelle();
	this->tab_beschr_layout = new QHBoxLayout(this->ui->tab_4);
	this->tab_beschr_layout->addWidget(this->tabel_beschr);
	tabel_abfrage = new ATabelle();
	this->tab_abfr_layout = new QHBoxLayout(this->ui->tab_2);
	this->tab_abfr_layout->addWidget(this->tabel_abfrage);
	this->sqltabelle = new SQLTabelle();
	ui->verticalLayout_SQLTab->addWidget(this->sqltabelle);
	this->abfrageTE = new AbfrageTextEdit(this);
	ui->horizontalLayout->addWidget(this->abfrageTE);

	this->ui->toolButton->setMenu(hist_einst_menue);
	connect(this->abfrageTE, SIGNAL(neueAbfrage(QString)), this->tabel_abfrage, SLOT(setzAbfr(QString)));
	connect(this->tabel_abfrage, SIGNAL(errors(bool)), this, SLOT(neueAbfr(bool)));
	connect(this->tabel_abfrage, SIGNAL(errors(bool)), this->abfrageTE, SLOT(errors_occured(bool)));
}

Hauptfenster::~Hauptfenster()
{
    delete ui;
}

void Hauptfenster::changeEvent(QEvent *e)
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

void Hauptfenster::on_pushButton_Verbinden_clicked()
{
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName(dialog_verbinden.host);
	db.setPort(dialog_verbinden.port);
	db.setDatabaseName(dialog_verbinden.datenbank);
	db.setUserName(dialog_verbinden.benutzer);
	db.setPassword(dialog_verbinden.passwort);
	if(!db.open())
	{
		qDebug() << tr("Fehler");
		this->ui->statusBar->showMessage(tr("Fehler beim Verbinden"), 10000);
		return;
	}
	Label_verbunden.setText(tr("Verbunden"));
	qDebug() << tr("Verbunden");
	this->ui->pushButton_Verbinden->setDisabled(true);
	this->ui->pushButton_Trennen->setEnabled(true);

	QSqlQuery query;
	query.exec("SHOW DATABASES;");
	qDebug() << query.lastError().text();
	//sqlabfrage("SHOW DATABASES", false);
	while (/*this->abfrage*/query.next()) {
		  QString dbname = /*this->abfrage*/query.value(0).toString();
		  this->ui->listWidget_DBs->addItem(dbname);
	}
}

void Hauptfenster::on_pushButton_clicked()
{
	dialog_verbinden.show();
}

void Hauptfenster::sqlabfrage(QString abfrage/*, bool erganzeigen*/)
{
	this->abfrage.exec(abfrage);
	this->ui->plainTextEdit_Log->appendPlainText(abfrage);
	this->ui->plainTextEdit_Log->appendPlainText(this->abfrage.lastError().text());
	this->ui->statusBar->showMessage(abfrage, 5000);
}

void Hauptfenster::on_pushButton_Trennen_clicked()
{
	db.close();
	Label_verbunden.setText(tr("Nicht verbunden"));
	qDebug() << tr("Verbindung getrennt");
	this->ui->pushButton_Verbinden->setEnabled(true);
	this->ui->pushButton_Trennen->setDisabled(true);
	this->ui->listWidget_DBs->clear();
	this->ui->listWidget_Tabellen->clear();
	this->sqltabelle->leeren();
}


void Hauptfenster::on_listWidget_DBs_itemActivated(QListWidgetItem* item)
{
	qDebug() << "Datenbank " << item->text() << " ausgewählt";
	this->ui->listWidget_Tabellen->clear();
	QSqlQuery query;
	query.exec("USE " + item->text() + ";");
	query.exec("SHOW TABLES;");
	while (query.next()) {
		  QString tabname = query.value(0).toString();
		  this->ui->listWidget_Tabellen->addItem(tabname);
	}
}

void Hauptfenster::on_listWidget_Tabellen_itemActivated(QListWidgetItem* item)
{
	qDebug() << "Tabelle " << item->text() << " ausgewählt";
	QSqlQueryModel* tabbeschmodel = new QSqlQueryModel();
	tabbeschmodel->setQuery("DESCRIBE " + item->text() + ";");

	this->tabel_beschr->setModel(tabbeschmodel);
	//this->tabel_beschr->resizeColumnsToContents();
	this->tabel_beschr->show();

	this->sqltabelle->setTabelle(item->text());

	if(ui->tabWidget->currentIndex()==0 || ui->tabWidget->currentIndex()==3)
		ui->tabWidget->setCurrentIndex(1);

	if(ui->tabWidget->currentIndex()==1)
		this->sqltabelle->malen();
	else
		this->andere_Tab = true;
}

void Hauptfenster::on_pushButton_2_clicked()
{
	this->close();
}

void Hauptfenster::neueAbfr(bool errors)
{
	if(errors)
	{
		ui->plainTextEdit_Log->appendPlainText(tabel_abfrage->last_Errors);
		ui->tabWidget->setCurrentIndex(0);
	}
	else
		ui->tabWidget->setCurrentIndex(3);
}
