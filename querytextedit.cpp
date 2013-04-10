#include "querytextedit.hh"
#include <QKeyEvent>

#include "mainwindow.hh"


#include <iostream>

Querytextedit::Querytextedit(QWidget *parent) :
    QTextEdit(parent)
{
	this->mainwindow = (Mainwindow*) parent;
	this->highlighter = new MySQLHighlighter(this->document());

	this->mainwindow->hist_menu = new QMenu();

	this->drinlassen = new QAction(tr("So lassen"), this);
	this->drinlassen->setCheckable(true);
	this->einzeln = new QAction(tr("nur eins"), this);
	this->einzeln->setCheckable(true);

	this->behavior = new QActionGroup(this);
	this->behavior->addAction(this->drinlassen);
	this->behavior->addAction(this->einzeln);
	this->einzeln->setChecked(true);

	this->save = new QAction(tr("Save"), this);
	this->save->setShortcut(QKeySequence::Save);
	this->load = new QAction(tr("Load"), this);
	this->load->setShortcut(QKeySequence::Open);

	this->mainwindow->hist_menu->addAction(this->drinlassen);
	this->mainwindow->hist_menu->addAction(this->einzeln);
	this->mainwindow->hist_menu->addSeparator();
	this->mainwindow->hist_menu->addAction(this->save);
	this->mainwindow->hist_menu->addAction(this->load);

	connect(this->save, SIGNAL(triggered()), this, SLOT(save_query()));
	connect(this->load, SIGNAL(triggered()), this, SLOT(load_query()));
	connect(this, SIGNAL(textChanged()), this, SLOT(something_changed()));

	this->hist_position = 0;
	hist_something_changed = false;
}

void Querytextedit::keyPressEvent(QKeyEvent* e) {
			 //(e->modifiers()==Qt::ShiftModifier) &&
	if(e->key()==Qt::Key_F9)
		//if(this->einzeln->isChecked())
			make_query(this->toPlainText());

	if(e->key()==Qt::Key_PageUp)
		hist_up();
	if(e->key()==Qt::Key_PageDown)
		hist_down();
	 QTextEdit::keyPressEvent(e);
}


void Querytextedit::make_query(QString query)
{
	emit new_query(query);
}

void Querytextedit::hist_add(QString query)
{
	if(hist_position==query_history.count() || this->hist_something_changed)
	{
		this->query_history << query;
		this->clear();
		this->hist_position = query_history.count();
		this->hist_something_changed = false;
	}
}

void Querytextedit::hist_up()
{
	//qDebug() << query_history << waspos;
	if(hist_position==0)
		return;
	if(hist_something_changed && hist_position!=query_history.count())
	{
		this->query_history[this->hist_position] = this->toPlainText();
	}
	if(hist_position==query_history.count() && hist_something_changed)
		query_history << this->toPlainText();

	this->hist_position--;
	this->setText(this->query_history.at(this->hist_position));
	hist_something_changed = false;
	//qDebug() << query_history << waspos;
}

void Querytextedit::hist_down()
{
	//qDebug() << query_history << waspos;
	if(hist_position==query_history.count())
		return;
	if(hist_something_changed)
	{
		this->query_history[hist_position] = this->toPlainText();
	}
	this->hist_position++;
	if(this->hist_position < query_history.count())
		this->setText(this->query_history.at(this->hist_position));
	else
		this->clear();
	hist_something_changed = false;
	//qDebug() << query_history << waspos;
}

void Querytextedit::save_query()
{
	QFile file("query.txt");
	if (!file.open(QIODevice::WriteOnly))
		return;

	QDataStream output(&file);
	QVariant v(this->query_history);
	output << v;
	file.close();
}

void Querytextedit::load_query()
{
	QFile file("query.txt");
	if(!file.open(QIODevice::ReadOnly))
		return;

	QDataStream input(&file);
	QVariant v;
	input >> v;
	this->query_history = v.toStringList();
	file.close();
	this->hist_position = query_history.count();
	this->clear();
}

void Querytextedit::something_changed()
{
	hist_something_changed = true;
	//std::cout << "jupp\n";
}

void Querytextedit::errors_occured(bool errors)
{
	if(!errors)
		hist_add(this->toPlainText());
}

/*Zutun:
Gibt n Fehler -> auf ab geht nicht
*/
