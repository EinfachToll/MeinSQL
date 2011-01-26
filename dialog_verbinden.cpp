#include "dialog_verbinden.hh"
#include "ui_dialog_verbinden.h"

Dialog_Verbinden::Dialog_Verbinden(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Verbinden)
{
    ui->setupUi(this);
	initialisieren();
}

Dialog_Verbinden::~Dialog_Verbinden()
{
    delete ui;
}

void Dialog_Verbinden::changeEvent(QEvent *e)
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

void Dialog_Verbinden::initialisieren()
{
	this->host = ui->lineEdit_Host->text();
	this->port = ui->spinBox_Port->value();
	this->benutzer = ui->lineEdit_Benutzer->text();
	this->passwort = ui->lineEdit_Passwort->text();
	this->begrenzung = ui->spinBox->value();
	this->datenbank = ui->lineEdit_Datenbank->text();
}

void Dialog_Verbinden::on_buttonBox_accepted()
{
	initialisieren();
}
