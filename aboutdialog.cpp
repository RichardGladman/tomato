#include "aboutdialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <qpushbutton.h>

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent) 
{
	setWindowTitle("About tomato");
	
	QHBoxLayout *mainLayout = new QHBoxLayout(this);
	
	QPixmap pixmap = QPixmap(":/assets/tomato.png");
	QLabel *logo = new QLabel(this);
	logo->setPixmap(pixmap);
	
	mainLayout->addWidget(logo);
	
	QVBoxLayout *rightLayout = new QVBoxLayout(this);
	
	QFont font = QFont("Arial", 16);
	QLabel *titleLabel = new QLabel("Tomato", this);
	titleLabel->setFont(font);
	rightLayout->addWidget(titleLabel);
	
	QLabel *copyrightLabel = new QLabel(this);
	copyrightLabel->setText("© 2026 Richard Gladman");
	rightLayout->addWidget(copyrightLabel);
	
	QLabel *licenceLabel = new QLabel("Licensed under the GPLv3", this);
	rightLayout->addWidget(licenceLabel);
	
	QLabel *descriptionLabel = new QLabel(this);
	descriptionLabel->setText("A basic and configurable work / rest balance clock");
	rightLayout->addWidget(descriptionLabel);
	
	rightLayout->addStretch();
	
	QPushButton *button = new QPushButton("Close", this);
	connect(button, &QPushButton::clicked, this, &QDialog::reject);
	rightLayout->addWidget(button);
	
	mainLayout->addLayout(rightLayout);

}

AboutDialog::~AboutDialog() {}
