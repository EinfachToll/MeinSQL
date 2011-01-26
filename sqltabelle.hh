#ifndef SQLTABELLE_HH
#define SQLTABELLE_HH

#include "tabelle.hh"
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

private:
	void sortieren(int);
	QSqlTableModel* model;
	QString tabelle;
};

#endif // SQLTABELLE_HH
