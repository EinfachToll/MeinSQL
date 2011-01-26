#ifndef DIALOG_VERBINDEN_HH
#define DIALOG_VERBINDEN_HH

#include <QDialog>
//#include <QDebug>

namespace Ui {
    class Dialog_Verbinden;
}

class Dialog_Verbinden : public QDialog {
    Q_OBJECT
public:
    Dialog_Verbinden(QWidget *parent = 0);
    ~Dialog_Verbinden();
	QString host;
	QString benutzer;
	int port;
	QString passwort;
	int begrenzung;
	QString datenbank;
	Ui::Dialog_Verbinden *ui;

protected:
    void changeEvent(QEvent *e);

private:
	void initialisieren();

private slots:
	void on_buttonBox_accepted();
};

#endif // DIALOG_VERBINDEN_HH
