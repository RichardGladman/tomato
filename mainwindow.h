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

private:
	QSoundEffect alarmSound;
	QTimer *timer;
	
	int *working;
	int *resting;
	
	void showSettingsDialog();
	void loadSettings();
};
#endif // MAINWINDOW_H
