#include "settingsdialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QSettings>

SettingsDialog::SettingsDialog(int *working, int *resting, QWidget *parent) : QDialog(parent), working {working}, resting {resting} 
{
	setWindowTitle("Tomato: Settings");
	
	QVBoxLayout *mainLayout = new QVBoxLayout(this);

	QHBoxLayout *wmLayout = new QHBoxLayout(this);
	QLabel *wmLabel = new QLabel("Working minutes", this);
	workingMinutes = new QSpinBox(this);
	workingMinutes->setMinimum(1);
	workingMinutes->setMaximum(120);
	workingMinutes->setValue(*working);

	wmLayout->addWidget(wmLabel);
	wmLayout->addWidget(workingMinutes);
	mainLayout->addLayout(wmLayout);

	QHBoxLayout *rmLayout = new QHBoxLayout(this);
	QLabel *rmLabel = new QLabel("Resting minutes", this);
	restingMinutes = new QSpinBox(this);
	restingMinutes->setMinimum(1);
	restingMinutes->setMaximum(30);
	restingMinutes->setValue(*resting);

	rmLayout->addWidget(rmLabel);
	rmLayout->addWidget(restingMinutes);
	mainLayout->addLayout(rmLayout);

	QHBoxLayout *buttonLayout = new QHBoxLayout(this);
	QPushButton *okButton = new QPushButton("OK", this);
	QPushButton *cancelButton = new QPushButton("Cancel", this);

	connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
	connect(okButton, &QPushButton::clicked, this, &SettingsDialog::acceptDialog);

	buttonLayout->addWidget(okButton);
	buttonLayout->addWidget(cancelButton);
	mainLayout->addLayout(buttonLayout);

	
}

SettingsDialog::~SettingsDialog() { }

void SettingsDialog::acceptDialog()
{
	*working = workingMinutes->value();
	*resting = restingMinutes->value();
	
	saveSettings();
	
	accept();
}

void SettingsDialog::saveSettings()
{
	QSettings settings("TheFifthContinent", "tomato");
	settings.beginGroup("values");
	settings.setValue("working", *working);
	settings.setValue("resting", *resting);
	settings.endGroup();
}
