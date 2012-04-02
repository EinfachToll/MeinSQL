#ifndef TABELLE_HH
#define TABELLE_HH

#include <QTableView>
#include <QSqlError>

/**
  Basisklasse für die drei Tabellen, richtet die Spalten nach einer Sekunde richtig aus
  */
class Tabelle : public QTableView
{
    Q_OBJECT
public:
	explicit Tabelle(QWidget *parent = 0);
	virtual ~Tabelle() {};

private:
	QTimer* stoppuhr;
	QString query;

protected slots:
	void spalten_richten();

private slots:
	void stoppuhr_starten();
	virtual void sortieren(int) {};
	virtual void filtern(QString) {};

};

#endif // TABELLE_HH
