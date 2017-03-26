#include "mainwindow.h"
#include <QApplication>
#include "imagefiltering.h"
#include <QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
