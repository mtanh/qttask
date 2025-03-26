#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "groundwatermodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button1_clicked();
    void on_button2_clicked();

private:
    GroundwaterModel mseModel;
    GroundwaterModel otherWallModel;

    void saveSettings();
    void loadSettings();
};
#endif
