#ifndef SETTINGSWINDOW_HH
#define SETTINGSWINDOW_HH

#include <QDialog>

namespace Ui {
    class Settingswindow;
}

class Settingswindow : public QDialog {
    Q_OBJECT
public:
    Settingswindow(QWidget *parent = 0);
    ~Settingswindow();
	QString host;
	QString username;
	int port;
	QString password;
	int max_num_of_records_in_tables;
	QString initial_db_name;
	Ui::Settingswindow *ui;

protected:
    void changeEvent(QEvent *e);

private:
	void initialize();

private slots:
	void on_buttonBox_accepted();
};

#endif // SETTINGSWINDOW_HH
