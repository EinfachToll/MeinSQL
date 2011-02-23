#ifndef ATABELLE_HH
#define ATABELLE_HH

#include "tabelle.hh"
#include <QSqlQueryModel>

class ATabelle : public Tabelle
{
    Q_OBJECT
public:
	explicit ATabelle(QWidget *parent = 0);
	QString last_Errors;
	QList<QSqlQueryModel*> modellist;

private:

signals:
	void errors(bool);

public slots:
	void set_query(QString);

};

#endif // ATABELLE_HH
