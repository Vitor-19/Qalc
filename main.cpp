#include "mainwindow.h"

#include <QApplication>
#include <QGuiApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setWindowIcon(QIcon(":/assets/icon/logo.png"));
    QGuiApplication::setDesktopFileName("Qalc");

    MainWindow window;
    window.show();

    return app.exec();
}