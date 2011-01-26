#ifndef ABFRAGETEXTEDIT_HH
#define ABFRAGETEXTEDIT_HH

#include <QTextEdit>
#include <QAction>
#include "mysqlhighlighter.h"

class Hauptfenster;

class AbfrageTextEdit : public QTextEdit
{
	Q_OBJECT
public:
	explicit AbfrageTextEdit(QWidget *parent = 0);

protected:
	void keyPressEvent(QKeyEvent*);

private:
	MySQLHighlighter* highlighter;
	Hauptfenster* hauptfenster;
	QAction* drinlassen;
	QAction* einzeln;
	QAction* speichern;
	QAction* laden;
	QActionGroup* verhalten;

	QStringList wasbishergeschah;
	int waspos;
	void washinzu(QString);
	void washoch();
	void wasrunter();
	void wasspeichern();
	void wasladen();
signals:
	void neueAbfrage(QString);

public slots:
	void abfragemachen(QString);

};

#endif // ABFRAGETEXTEDIT_HH
