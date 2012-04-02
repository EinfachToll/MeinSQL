#ifndef ATABELLE_HH
#define ATABELLE_HH

#include "tabelle.hh"
#include <QSqlQueryModel>

class ATabelle : public Tabelle
{
    Q_OBJECT
public:
	explicit ATabelle(QWidget *parent = 0);
	QString letzte_Fehler;
	QList<QSqlQueryModel*> modelliste;

private:

signals:
	void fehler(bool);

public slots:
	void setze_Abfrage(QString);

private slots:
	virtual void sortieren(int);
	virtual void filtern(QString);

};

#endif // ATABELLE_HH
