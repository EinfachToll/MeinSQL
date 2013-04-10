#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

#include "settingswindow.hh"
#include "infotable.hh"
#include "querytable.hh"
#include "sqltabletable.hh"
#include "querytextedit.hh"
#include <QtDebug>
#include <QLabel>
#include <QSqlDatabase>
#include <QListWidgetItem>
#include <QtSql>
#include <QTableWidgetItem>
#include <QHBoxLayout>
#include <QMenu>

namespace Ui {
    class Mainwindow;
}

class Mainwindow : public QMainWindow {
    Q_OBJECT
public:
    Mainwindow(QWidget *parent = 0);
    ~Mainwindow();
	Settingswindow settingswindow;
	Ui::Mainwindow *ui;
	QMenu* hist_menu;

protected:
    void changeEvent(QEvent *e);

private:
	QLabel show_if_connected;
	QSqlDatabase db;
	void perform_sql_query(QString query/*, bool*/);
	QSqlQuery query;
	QHBoxLayout* infotable_layout;
	Infotable* infotable;
	Querytable* querytable;
	QHBoxLayout* querytable_layout;
	SQLtabletable* sqltabletable;
	Querytextedit* querytextedit;
	bool changed_tab;


private slots:
	void on_pushButton_2_clicked();
	void on_listWidget_Tables_itemActivated(QListWidgetItem* item);
	void on_listWidget_DBs_itemActivated(QListWidgetItem* item);
	void on_pushButton_Trennen_clicked();
	void on_pushButton_clicked();
	void on_pushButton_Connect_clicked();
	void new_query(bool);
};

#endif // MAINWINDOW_HH
