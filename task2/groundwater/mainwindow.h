#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "groundwatermodel.h"

class QPushButton;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openMSEDialog();
    void openOtherWallsDialog();

private:
    //Ui::MainWindow *ui;

    QPushButton* m_button1;
    QPushButton* m_button2;
    GroundwaterModel* m_mseModel;
    GroundwaterModel* m_otherWallsModel;
};
#endif // MAINWINDOW_H
