#ifndef TABELLE_HH
#define TABELLE_HH

#include <QTableView>
#include <QSqlError>

class Tabelle : public QTableView
{
    Q_OBJECT
public:
	explicit Tabelle(QWidget *parent = 0);

private:
	QTimer* stoppuhr;

signals:

protected slots:
	void spalten_richten();

private slots:
	void spalten_schoen();

};

#endif // TABELLE_HH