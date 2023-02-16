#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->SliderPaint, &QSlider::sliderMoved, ui->GLRender, &GLRenderWidget::paintGL);
}

MainWindow::~MainWindow()
{
    delete ui;
}

