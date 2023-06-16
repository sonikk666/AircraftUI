#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "aircraft.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QSqlDatabase>
#include <QSqlQuery>


class Server: public QTcpServer
{
    Q_OBJECT
public:
    Server();
    ~Server();

    QTcpSocket* socket;
    QByteArray data;  // Входящие данные по Tcp
    bool complexData = false;  // Флаг, определяющий, что данные пришли не полностью

    QJsonDocument jDoc;  // преобразование пришедших данных в json
    QJsonParseError jDocError;  // отчёт об ошибках при преобразовании в json

    QSqlDatabase db;

public slots:
    void startServer();
    void incomingConnection(qintptr socketDescriptor);
    void sockReady();  // действия над пришедшими данными
    void sockDisc();  // отключение от сервера

signals:
    void aircraftsSignal(QList<Aircraft>*);  // передача данных о списке всех самолётов

private:
    AircraftsJsonController controller;  // объект для работы с json
};

#endif // MYSERVER_H

