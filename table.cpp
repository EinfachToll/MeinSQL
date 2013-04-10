#include "table.hh"
#include <iostream>
#include <QScrollBar>
#include <QTimer>
#include <QHeaderView>

Table::Table(QWidget* parent) :
	QTableView(parent)
{
	QObject::connect(this->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(start_stopwatch()));
	this->stopwatch = new QTimer();
	this->stopwatch->setInterval(1000);
	this->stopwatch->setSingleShot(true);
	QObject::connect(this->stopwatch, SIGNAL(timeout()), this, SLOT(resize_columns()));

	this->setSortingEnabled(true);
	this->horizontalHeader()->setClickable(true);
	QObject::connect(this->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sort(int)));
}

void Table::start_stopwatch()
{
	this->stopwatch->start();
}

void Table::resize_columns()
{
	this->resizeColumnsToContents();
}
