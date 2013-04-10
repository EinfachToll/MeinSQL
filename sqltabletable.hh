#ifndef SQLTABLETABLE_HH
#define SQLTABLETABLE_HH

#include "table.hh"
#include <QSqlQueryModel>
#include <QSqlTableModel>

class SQLtabletable : public Table
{
	Q_OBJECT
public:
	SQLtabletable(QWidget *parent = 0);
	~SQLtabletable();
	void set_table(QString table);
	void draw();
	void clear();
	QSqlQueryModel* infomodel;

private:
	QSqlTableModel* model;
	QString table;
	QString sort_by;
	QString limit;//XXX: für alle Tabellen
	QString sort_asc_or_desc;

private slots:
	virtual void sort(int);
	virtual void filter(QString);

public slots:
	void set_query(QString);
};

#endif // SQLTABLETABLE_HH
