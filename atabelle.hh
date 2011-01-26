#ifndef ATABELLE_HH
#define ATABELLE_HH

#include "tabelle.hh"
#include <QSqlQueryModel>

class ATabelle : public Tabelle
{
    Q_OBJECT
public:
    explicit ATabelle(QWidget *parent = 0);

private:
	QSqlQueryModel* abfrmodell;

signals:

public slots:
	void setzAbfr(QString);

};

#endif // ATABELLE_HH
