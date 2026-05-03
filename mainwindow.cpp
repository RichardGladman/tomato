#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QMediaPlayer>
#include <QTimer>
#include <QPixmap>
#include <QIcon>
#include <QUrl>
#include <QDialog>
#include <QSpinBox>
#include <QSettings>
#include <QDebug>

#include "settingsdialog.h"
#include "aboutdialog.h"

void showSettingsDialog();

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	working = new int;
	resting = new int;
	preResting = new int;
	
	loadSettings();
	
	alarmSound.setSource(QUrl::fromLocalFile(":/assets/chimes.wav"));

	setWindowTitle("Tomato");
	resize(400, 180);
	
	QWidget *centralWidget = new QWidget(this);
	setCentralWidget(centralWidget);

	QPixmap pixmap = QPixmap(":/assets/tomato.png");
	
	QIcon *icon = new QIcon(pixmap);
	
	setWindowIcon(*icon);
	
	QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
	QVBoxLayout *rightLayout = new QVBoxLayout(centralWidget);
	
	QLabel *logo = new QLabel(centralWidget);
	logo->setPixmap(pixmap);
	
	QFont font = QFont("Arial", 20);
	QLabel *message = new QLabel("Working...", centralWidget);
	message->setFont(font);
	
	QHBoxLayout *buttonLayout = new QHBoxLayout(centralWidget);
	
	QPushButton *settingsButton = new QPushButton("Settings", centralWidget);
	connect(settingsButton, &QPushButton::clicked, this, &MainWindow::showSettingsDialog);

	QPushButton *aboutButton = new QPushButton("About", centralWidget);
	connect(aboutButton, &QPushButton::clicked, this, &MainWindow::showAboutDialog);

		
	mainLayout->addWidget(logo);
	mainLayout->addLayout(rightLayout);
	buttonLayout->addWidget(settingsButton);
	buttonLayout->addWidget(aboutButton);
	rightLayout->addWidget(message);
	rightLayout->addLayout(buttonLayout);
	
	timer = new QTimer(centralWidget);
	timer->setInterval(60000 * *working);
	connect(timer, &QTimer::timeout, [this, message](){
		alarmSound.play();
		timer->stop();
		timer->setInterval(timer->interval() == 60000 * *resting ? 60000 * *working : 60000 * *resting);
		message->setText(message->text() == "Working..." ? "Resting..." : "Working...");
		timer->start();
	});
	
	timer->start();
	
}

MainWindow::~MainWindow() 
{
	delete working;
	delete resting;	
	delete preResting;
}

void MainWindow::showSettingsDialog()
{
	SettingsDialog dialog(working, resting, preResting, this);
	
	if (dialog.exec() == QDialog::Accepted) {
		loadSettings();
		timer->stop();
		timer->setInterval(timer->interval() == 60000 * *preResting ? 60000 * *resting : 60000 * *working);
		timer->start();

	}
}

void MainWindow::showAboutDialog()
{
	AboutDialog dialog(this);
	dialog.exec();
}

void MainWindow::loadSettings()
{
	QSettings settings("TheFifthContinent", "tomato");
	
	settings.beginGroup("values");
	*working = settings.value("working", 25).toInt();
	*resting = settings.value("resting", 10).toInt();
	settings.endGroup();
}
