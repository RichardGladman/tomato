#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QMediaPlayer>
#include <QTimer>
#include <QPixmap>
#include <qboxlayout.h>
#include <qfont.h>
#include <qpushbutton.h>
#include <qurl.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	alarmSound.setSource(QUrl::fromLocalFile(":/assets/chimes.wav"));

	setWindowTitle("Tomato");
	resize(400, 180);
	
	QWidget *centralWidget = new QWidget(this);
	setCentralWidget(centralWidget);
	
	QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
	QVBoxLayout *rightLayout = new QVBoxLayout(centralWidget);
	
	QPixmap pixmap = QPixmap(":/assets/tomato.png");
	//Q_ASSERT(!pixmap.isNull());
	QLabel *logo = new QLabel(centralWidget);
	logo->setPixmap(pixmap);
	
	QFont font = QFont("Arial", 20);
	QLabel *message = new QLabel("Working...", centralWidget);
	message->setFont(font);
	
	QPushButton *settingsButton = new QPushButton("Settings", centralWidget);
	
	mainLayout->addWidget(logo);
	mainLayout->addLayout(rightLayout);
	rightLayout->addWidget(message);
	rightLayout->addWidget(settingsButton);
//	this->setLayout(mainLayout);
	
	timer = new QTimer(centralWidget);
	timer->setInterval(1'500'000);
	connect(timer, &QTimer::timeout, [this, message](){
		alarmSound.play();
		timer->stop();
		timer->setInterval(timer->interval() == 600'000 ? 1'500'000 : 600'000);
		message->setText(message->text() == "Working..." ? "Resting..." : "Working...");
		timer->start();
	});
	
	timer->start();
	
}

MainWindow::~MainWindow() = default;
