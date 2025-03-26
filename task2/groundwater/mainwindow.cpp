#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include <QPushButton>
#include <QHBoxLayout>
#include "groundwaterdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    //, ui(new Ui::MainWindow)
{
    //ui->setupUi(this);

    // Setup models
    m_mseModel = new GroundwaterModel(true);
    m_otherWallsModel = new GroundwaterModel(false);

    // Setup UI
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout* layout = new QHBoxLayout(centralWidget);
    m_button1 = new QPushButton("MSE Dialog", this);
    m_button2 = new QPushButton("Other Walls Dialog", this);
    layout->addWidget(m_button1);
    layout->addWidget(m_button2);
    layout->addStretch();

    // Connections
    connect(m_button1, &QPushButton::clicked, this, &MainWindow::openMSEDialog);
    connect(m_button2, &QPushButton::clicked, this, &MainWindow::openOtherWallsDialog);

    // Margins and size
    layout->setContentsMargins(10, 10, 10, 10);
    resize(300, 100);

}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::openMSEDialog()
{
    GroundwaterDialog dialog(m_mseModel, this);
    dialog.exec();
}

void MainWindow::openOtherWallsDialog()
{
    GroundwaterDialog dialog(m_otherWallsModel, this);
    dialog.exec();
}

