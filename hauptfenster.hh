#ifndef HAUPTFENSTER_HH
#define HAUPTFENSTER_HH

#include <QMainWindow>

#include "dialog_verbinden.hh"
#include "atabelle.hh"
#include "sqltabelle.hh"
#include "abfragetextedit.hh"
#include <QtDebug>
#include <QLabel>
#include <QSqlDatabase>
#include <QListWidgetItem>
#include <QtSql>
#include <QTableWidgetItem>
#include <QHBoxLayout>
#include <QMenu>

namespace Ui {
    class Hauptfenster;
}

class Hauptfenster : public QMainWindow {
    Q_OBJECT
public:
    Hauptfenster(QWidget *parent = 0);
    ~Hauptfenster();
	Dialog_Verbinden dialog_verbinden;
	Ui::Hauptfenster *ui;
	QMenu* hist_einst_menue;

protected:
    void changeEvent(QEvent *e);

private:
	QLabel Label_verbunden;
	QSqlDatabase db;
	void sqlabfrage(QString abfrage/*, bool erganzeigen*/);
	QSqlQuery abfrage;
	ATabelle* tabel_beschr;
	QHBoxLayout* tab_beschr_layout;
	ATabelle* tabel_abfrage;
	QHBoxLayout* tab_abfr_layout;
	SQLTabelle* sqltabelle;
	AbfrageTextEdit* abfrageTE;
	bool andere_Tab;


private slots:
	void on_pushButton_2_clicked();
	void on_listWidget_Tabellen_itemActivated(QListWidgetItem* item);
	void on_listWidget_DBs_itemActivated(QListWidgetItem* item);
	void on_pushButton_Trennen_clicked();
	void on_pushButton_clicked();
	void on_pushButton_Verbinden_clicked();
};

#endif // HAUPTFENSTER_HH
