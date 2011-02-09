#include "abfragetextedit.hh"
#include <QKeyEvent>

#include "hauptfenster.hh"


#include <iostream>

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

	this->speichern = new QAction(tr("Speichern"), this);
	this->speichern->setShortcut(QKeySequence::Save);
	this->laden = new QAction(tr("Laden"), this);
	this->laden->setShortcut(QKeySequence::Open);

	this->hauptfenster->hist_einst_menue->addAction(this->drinlassen);
	this->hauptfenster->hist_einst_menue->addAction(this->einzeln);
	this->hauptfenster->hist_einst_menue->addSeparator();
	this->hauptfenster->hist_einst_menue->addAction(this->speichern);
	this->hauptfenster->hist_einst_menue->addAction(this->laden);

	connect(this->speichern, SIGNAL(triggered()), this, SLOT(abfragespeichern()));
	connect(this->laden, SIGNAL(triggered()), this, SLOT(abfrageladen()));
	connect(this, SIGNAL(neueAbfrage(QString)), this, SLOT(abfragemachen(QString)));
	connect(this, SIGNAL(textChanged()), this, SLOT(hatsichwasgetan()));

	this->waspos = 0;
	wasgeaendert = false;
}

void AbfrageTextEdit::keyPressEvent(QKeyEvent* e) {
			 //(e->modifiers()==Qt::ShiftModifier) &&
	if(e->key()==Qt::Key_F9)
		//if(this->einzeln->isChecked())
			emit neueAbfrage(this->toPlainText());

	if(e->key()==Qt::Key_PageUp)
		washoch();
	if(e->key()==Qt::Key_PageDown)
		wasrunter();
	 QTextEdit::keyPressEvent(e);
}


void AbfrageTextEdit::abfragemachen(QString abfrage)
{
	washinzu(abfrage);
}

void AbfrageTextEdit::washinzu(QString abfrage)
{
	if(waspos==wasbishergeschah.count() || wasgeaendert)
	{
		this->wasbishergeschah << abfrage;
		this->clear();
		this->waspos = wasbishergeschah.count();
		wasgeaendert = false;
	}
}

void AbfrageTextEdit::washoch()
{
	qDebug() << wasbishergeschah << waspos;
	if(waspos==0)
		return;
	if(wasgeaendert && waspos!=wasbishergeschah.count())
	{
		this->wasbishergeschah[this->waspos] = this->toPlainText();
	}
	if(waspos==wasbishergeschah.count() && wasgeaendert)
		wasbishergeschah << this->toPlainText();

	this->waspos--;
	this->setText(this->wasbishergeschah.at(this->waspos));
	wasgeaendert = false;
	qDebug() << wasbishergeschah << waspos;
}

void AbfrageTextEdit::wasrunter()
{
	qDebug() << wasbishergeschah << waspos;
	if(waspos==wasbishergeschah.count())
		return;
	if(wasgeaendert)
	{
		this->wasbishergeschah[waspos] = this->toPlainText();
	}
	this->waspos++;
	if(this->waspos < wasbishergeschah.count())
		this->setText(this->wasbishergeschah.at(this->waspos));
	else
		this->clear();
	wasgeaendert = false;
	qDebug() << wasbishergeschah << waspos;
}

void AbfrageTextEdit::abfragespeichern()
{
	QFile dat("abfr.txt");
	if (!dat.open(QIODevice::WriteOnly))
		return;

	QDataStream ausgabe(&dat);
	QVariant v(this->wasbishergeschah);
	ausgabe << v;
	dat.close();
}

void AbfrageTextEdit::abfrageladen()
{
	QFile dat("abfr.txt");
	if(!dat.open(QIODevice::ReadOnly))
		return;

	QDataStream eingabe(&dat);
	QVariant v;
	eingabe >> v;
	this->wasbishergeschah = v.toStringList();
	dat.close();
	this->waspos = wasbishergeschah.count();
	this->clear();
}

void AbfrageTextEdit::hatsichwasgetan()
{
	wasgeaendert = true;
	std::cout << "jupp\n";
}
