#ifndef INFOTABLE_HH
#define INFOTABLE_HH

#include "table.hh"
#include <QSqlQueryModel>

class Infotable : public Table
{
    Q_OBJECT
public:
	explicit Infotable(QWidget *parent = 0);
	QSqlQueryModel* infomodel;

signals:

public slots:

private slots:
	virtual void sort(int);
	virtual void filter(QString);

};

#endif // INFOTABLE_HH
