#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);//代码请看mainwindow.cpp
    MainWindow w;
    w.show();

    return a.exec();
}
