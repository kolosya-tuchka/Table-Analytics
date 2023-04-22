#include "mainwindow.h"
#include <locale>
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "ru");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
