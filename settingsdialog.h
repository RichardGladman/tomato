#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSpinBox>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog {
	Q_OBJECT

public:
	explicit SettingsDialog(int *working, int *resting, int *preResting, QWidget *parent = nullptr);
	~SettingsDialog();

private:
	Ui::SettingsDialog *ui;
	
	QSpinBox *restingMinutes;
	QSpinBox *workingMinutes;
	
	int *working;
	int *resting;
	int *preResting;
	
	void acceptDialog();
	void saveSettings();
};

#endif // SETTINGSDIALOG_H
