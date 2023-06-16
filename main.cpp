#include "mainwindow.h"
#include "tcpserver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server Server;
    Server.startServer();

    MainWindow window;
    QObject::connect(&Server, &Server::aircraftsSignal, &window, &MainWindow::aircraftsSlot);
    window.show();

    return a.exec();
}
