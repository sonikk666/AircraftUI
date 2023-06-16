#include "tcpserver.h"

Server::Server(){
//    QObject::connect(this, &Server::aircraftsSignal, &window, &MainWindow::aircraftsSlot);
}

Server::~Server(){}

void Server::startServer()
{
    if (this->listen(QHostAddress::Any, 5050))
    {
        qDebug() << "Listening";
        airdb.create();
    }
    else
    {
        qDebug() << "Not listening";
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, this, &Server::sockReady);
    connect(socket, &QTcpSocket::disconnected, this, &Server::sockDisc);

    qDebug() << socketDescriptor << " Client connected";
}

void Server::sockReady()
{
    socket->waitForReadyRead(500);
    if (!complexData)
    {
        data = socket->readAll();
    }
    else
    {
        data.append(socket->readAll());
        complexData = false;
    }
    jDoc = QJsonDocument::fromJson(data, &jDocError);

    // Если есть ошибки, считать, что данные пришли не полностью
    if ((jDocError.errorString() != "ошибки отсутствуют") && (jDocError.errorString() != "no error occurred"))
    {
        complexData = true;
        sockReady();
    }
    else
    {
        if (jDoc.object().value("type").toString()=="select_aircraft")
        {
            qDebug() << "Aircrafts successfully accepted";
            controller.clear();
            QJsonArray docAr = jDoc.object().value("result").toArray();
            for (QJsonValue aircraft : docAr)
            {
                controller.append(aircraft.toObject());
            }
            QList<Aircraft>* allAircraft = new QList(controller.get_list());
            emit aircraftsSignal(allAircraft);

            // Запись в БД
            airdb.insert(allAircraft);
        }
    }
}

void Server::sockDisc()
{
    qDebug() << "Disconnect";
    socket->deleteLater();
}
