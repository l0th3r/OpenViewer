#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <iostream>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Rendering event
    m_Timer = new QTimer();
    connect(m_Timer, SIGNAL(timeout()), ui->GLRender, SLOT(Update()));

    m_Timer->start(1);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_Timer;
}

