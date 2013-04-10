#include "settingswindow.hh"
#include "ui_settingswindow.h"

Settingswindow::Settingswindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settingswindow)
{
    ui->setupUi(this);
	initialize();
}

Settingswindow::~Settingswindow()
{
    delete ui;
}

void Settingswindow::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Settingswindow::initialize()
{
	this->host = ui->lineEdit_Host->text();
	this->port = ui->spinBox_Port->value();
	this->username = ui->lineEdit_Benutzer->text();
	this->password = ui->lineEdit_Passwort->text();
	this->max_num_of_records_in_tables = ui->spinBox->value();
	this->initial_db_name = ui->lineEdit_Datenbank->text();
}

void Settingswindow::on_buttonBox_accepted()
{
	initialize();
}
