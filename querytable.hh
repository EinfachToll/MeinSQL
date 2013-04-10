#ifndef QUERYTABLE_HH
#define QUERYTABLE_HH

#include "table.hh"
#include <QSqlQueryModel>

class Querytable : public Table
{
    Q_OBJECT
public:
	explicit Querytable(QWidget *parent = 0);
	QString last_error;
	QList<QSqlQueryModel*> list_of_models;

private:

signals:
	void error_occurred(bool);

public slots:
	void set_query(QString);

private slots:
	virtual void sort(int);
	virtual void filter(QString);

};

#endif // QUERYTABLE_HH
