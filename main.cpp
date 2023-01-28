#include "mainwindow.h"

#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication qtApp(argc, argv);
    MainWindow w;

    w.show();
    return qtApp.exec();
}
