#include <QHBoxLayout>
#include <QPushButton>
#include <QCloseEvent>
#include <QSettings>
#include "mainwindow.h"
#include "dialogcontroller.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle("Groundwater");

    // Set a larger initial size for the MainWindow
    setMinimumSize(400, 200); // Minimum width: 400px, height: 200px
    resize(500, 250);         // Initial size: 500px wide, 250px tall

    // Load the saved settings
    loadSettings();

    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* layout = new QHBoxLayout(centralWidget);

    QPushButton* button1 = new QPushButton("Button 1", this); // Button 1 for MSE dialog
    QPushButton* button2 = new QPushButton("Button 2", this); // Button 2 for Other Walls dialog

    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->setContentsMargins(10, 10, 10, 10);

    setCentralWidget(centralWidget);

    connect(button1, &QPushButton::clicked, this, &MainWindow::on_button1_clicked);
    connect(button2, &QPushButton::clicked, this, &MainWindow::on_button2_clicked);
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_button1_clicked()
{
    DialogController dialog(true, this);
    dialog.setModel(mseModel);
    if (dialog.exec() == QDialog::Accepted)
    {
        mseModel = dialog.getModel();
        saveSettings();
    }
}

void MainWindow::on_button2_clicked()
{
    DialogController dialog(false, this);
    dialog.setModel(otherWallModel);
    if (dialog.exec() == QDialog::Accepted)
    {
        otherWallModel = dialog.getModel();
        saveSettings();
    }
}

void MainWindow::saveSettings()
{
    QSettings settings("QtTask", "Groundwater");
    mseModel.saveToSettings(settings, "MSE");
    otherWallModel.saveToSettings(settings, "OtherWalls");
}

void MainWindow::loadSettings()
{
    QSettings settings("QtTask", "Groundwater");
    mseModel.loadFromSettings(settings, "MSE");
    otherWallModel.loadFromSettings(settings, "OtherWalls");
}
