#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // HDPI support fuck yeah
    QApplication a(argc, argv);
    a.setStyleSheet("QMessageBox { messagebox-text-interaction-flags: 5; }");
    MainWindow w;
    w.show();

    return a.exec();
}
