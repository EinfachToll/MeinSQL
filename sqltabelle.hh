#ifndef SQLTABELLE_HH
#define SQLTABELLE_HH

#include "tabelle.hh"
#include <QSqlQueryModel>
#include <QSqlTableModel>

class SQLTabelle : public Tabelle
{
	Q_OBJECT
public:
	SQLTabelle(QWidget *parent = 0);
	~SQLTabelle();
	void setTabelle(QString tabelle);
	void malen();
	void leeren();
	QSqlQueryModel* infomodel;

private:
	QSqlTableModel* model;
	QString tabelle;
	QString sortierennach;
	QString limit;
	QString sortierenrichtung;

private slots:
	virtual void sortieren(int);
	virtual void filtern(QString);

public slots:
	void set_query(QString);
};

#endif // SQLTABELLE_HH
