#ifndef TABLE_HH
#define TABLE_HH

#include <QTableView>
#include <QSqlError>

/**
  Basisklasse für die drei Tabellen, richtet die Spalten nach einer Sekunde richtig aus
  */
class Table : public QTableView
{
    Q_OBJECT
public:
	explicit Table(QWidget *parent = 0);
	virtual ~Table() {};

private:
	QTimer* stopwatch;
	QString query;

protected slots:
	void resize_columns();

private slots:
	void start_stopwatch();
	virtual void sort(int) {};
	virtual void filter(QString) {};

};

#endif // TABLE_HH
