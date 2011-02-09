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

private:
	QSqlQueryModel* abfrmodell;

signals:
	void errors(bool);

public slots:
	void setzAbfr(QString);

};

#endif // ATABELLE_HH
