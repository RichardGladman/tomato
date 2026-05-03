#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSoundEffect>
#include <QTimer>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
	
	int *working;
	int *resting;
	int *preResting;

private:
	QSoundEffect alarmSound;
	QTimer *timer;
	
	void showSettingsDialog();
	void loadSettings();
};
#endif // MAINWINDOW_H
