#include "tabelle.hh"
#include <iostream>
#include <QScrollBar>
#include <QTimer>
#include <QHeaderView>

Tabelle::Tabelle(QWidget* parent) :
	QTableView(parent)
{
	QObject::connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(spalten_schoen()));
	this->stoppuhr = new QTimer();
	this->stoppuhr->setInterval(1000);
	this->stoppuhr->setSingleShot(true);
	QObject::connect(this->stoppuhr, SIGNAL(timeout()), this, SLOT(spalten_richten()));

	this->setSortingEnabled(true);
	this->horizontalHeader()->setClickable(true);
	QObject::connect(this->horizontalHeader(), SIGNAL(sectionDoubleClicked(int)), this, SLOT(sortieren(int)));
}

void Tabelle::spalten_schoen()
{
	this->stoppuhr->start();
}

void Tabelle::spalten_richten()
{
	this->resizeColumnsToContents();
}