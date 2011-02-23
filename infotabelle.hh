#ifndef INFOTABELLE_HH
#define INFOTABELLE_HH

#include "tabelle.hh"
#include <QSqlQueryModel>

class InfoTabelle : public Tabelle
{
    Q_OBJECT
public:
	explicit InfoTabelle(QWidget *parent = 0);
	QSqlQueryModel* infomodel;

signals:

public slots:

};

#endif // INFOTABELLE_HH
