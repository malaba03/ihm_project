#include "Mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(components);
    QApplication a(argc, argv);
    Mainwindow app;
    app.showMaximized();
    return a.exec(); 
}
