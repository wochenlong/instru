#include "mainwindow.h"

#include <QApplication>

float g_factor=1;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize((1396+800)*g_factor, 781*g_factor);
    w.setWindowTitle("Instruments");
    w.show();
    return a.exec();
}
