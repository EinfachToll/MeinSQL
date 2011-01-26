#include "abfragetextedit.hh"
#include <QKeyEvent>

#include "hauptfenster.hh"

AbfrageTextEdit::AbfrageTextEdit(QWidget *parent) :
    QTextEdit(parent)
{
	this->hauptfenster = (Hauptfenster*) parent;
	this->highlighter = new MySQLHighlighter(this->document());

	this->hauptfenster->hist_einst_menue = new QMenu();

	this->drinlassen = new QAction(tr("So lassen"), this);
	this->drinlassen->setCheckable(true);
	this->einzeln = new QAction(tr("nur eins"), this);
	this->einzeln->setCheckable(true);

	this->verhalten = new QActionGroup(this);
	this->verhalten->addAction(this->drinlassen);
	this->verhalten->addAction(this->einzeln);
	this->einzeln->setChecked(true);

	this->speichern = new QAction

	this->hauptfenster->hist_einst_menue->addAction(this->drinlassen);
	this->hauptfenster->hist_einst_menue->addAction(this->einzeln);

	connect(this, SIGNAL(neueAbfrage(QString)), this, SLOT(abfragemachen(QString)));

	this->waspos = 0;
}

void AbfrageTextEdit::keyPressEvent(QKeyEvent* e) {
			 //(e->modifiers()==Qt::ShiftModifier) &&
	if(e->key()==Qt::Key_F9)
		if(this->einzeln->isChecked())
			emit neueAbfrage(this->toPlainText());

	 QTextEdit::keyPressEvent(e);
}


void AbfrageTextEdit::abfragemachen(QString abfrage)
{
	if(this->einzeln->isChecked())
	{

	}
}

void AbfrageTextEdit::washinzu(QString abfrage)
{
	this->wasbishergeschah << abfrage;
	this->clear();
	this->waspos=0;
}

void AbfrageTextEdit::washoch()
{
	this->waspos++;
	this->setText(this->wasbishergeschah.at(this->wasbishergeschah.count() - this->waspos));
}

void AbfrageTextEdit::wasrunter()
{
	if(this->waspos > 0)
		this->waspos--;
	if(this->waspos > 0)
		this->setText(this->wasbishergeschah.at(this->wasbishergeschah.count() - this->waspos));
}
