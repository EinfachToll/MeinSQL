#ifndef QUERYTEXTEDIT_HH
#define QUERYTEXTEDIT_HH

#include <QTextEdit>
#include <QAction>
#include "mysqlhighlighter.h"

class Mainwindow;

class Querytextedit : public QTextEdit
{
	Q_OBJECT
public:
	explicit Querytextedit(QWidget *parent = 0);

protected:
	void keyPressEvent(QKeyEvent*);

private:
	MySQLHighlighter* highlighter;
	Mainwindow* mainwindow;
	QAction* drinlassen;
	QAction* einzeln;
	QAction* save;
	QAction* load;
	QActionGroup* behavior;

	QStringList query_history;
	int hist_position;
	void hist_add(QString);
	void hist_up();
	void hist_down();
	void hist_save();
	void hist_load();
	bool hist_something_changed;

signals:
	void new_query(QString);

public slots:
	void make_query(QString);
	void save_query();
	void load_query();
	void something_changed();
	void errors_occured(bool);

};

#endif // QUERYTEXTEDIT_HH
