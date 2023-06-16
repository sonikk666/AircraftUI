#include "tcpserver.h"

Server::Server(){}

Server::~Server(){}

void Server::startServer()
{
    if (this->listen(QHostAddress::Any, 5050))
    {
        qDebug() << "Listening";
//        Создает таблицы в БД
//        TODO: создать отдельный класс для БД
//        TODO: добавить запрос на CREATE DATABASE aircraft;
        db = QSqlDatabase::addDatabase("QPSQL");
        db.setHostName("127.0.0.1");
        db.setDatabaseName("aircraft");
        db.setUserName("aircraft");
        db.setPassword("aircraft");
        if (db.open())
        {
            qDebug() << "Open DB and can create";
            QSqlQuery *query = new QSqlQuery(db);

            query->exec("CREATE TABLE IF NOT EXISTS aircrafts("
                        "id SERIAL PRIMARY KEY,"
                        "reg_number VARCHAR(30) UNIQUE, "
                        "url_aircraft TEXT UNIQUE, "
                        "aircraft TEXT, "
                        "airline TEXT, "
                        "operator TEXT, "
                        "type_code TEXT, "
                        "code_airline TEXT, "
                        "code_operator TEXT, "
                        "mode_s TEXT, "
                        "msn TEXT, "
                        "age TEXT"
                        ");");

            query->exec("CREATE TABLE IF NOT EXISTS flights("
                        "id SERIAL PRIMARY KEY,"
                        "aircraft_id INTEGER, "
                        "date TEXT, "
                        "flight_from TEXT, "
                        "flight_to TEXT, "
                        "flight TEXT, "
                        "flight_time TEXT, "
                        "std TEXT, "
                        "atd TEXT, "
                        "sta TEXT, "
                        "status TEXT, "
                        "FOREIGN KEY (aircraft_id) REFERENCES aircrafts (id)"
                        ");");
            delete query;
        }
        db.close();
        if (!db.isOpen())
        {
            qDebug() << "Close DB";
        }
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
            if (db.open())
            {
                qDebug() << "Open DB and write";
                QSqlQuery* query = new QSqlQuery(db);


                foreach (Aircraft aircraft, *allAircraft)
                {                    
                    query->prepare("INSERT INTO aircrafts_test5 ("
                        "reg_number, url_aircraft, aircraft, airline, operator, "
                        "type_code, code_airline, code_operator, mode_s, msn, age) "
                        "VALUES ("
                        ":reg_number, :url_aircraft, :aircraft, :airline, :operator, "
                        ":type_code, :code_airline, :code_operator, :mode_s, :msn, :age"
                    ")");
                    query->bindValue(":reg_number", aircraft.regNumber);
                    query->bindValue(":url_aircraft", aircraft.urlAircraft);
                    query->bindValue(":aircraft", aircraft.aircraft);
                    query->bindValue(":airline", aircraft.airline);
                    query->bindValue(":operator", aircraft.nameOperator);
                    query->bindValue(":type_code", aircraft.typeCode);
                    query->bindValue(":code_airline", aircraft.codeAirlane);
                    query->bindValue(":code_operator", aircraft.codeOperator);
                    query->bindValue(":mode_s", aircraft.modeS);
                    query->bindValue(":msn", aircraft.msn);
                    query->bindValue(":age", aircraft.age);
                    query->exec();

                    foreach (FlightHistory oneHistory, aircraft.allFlightsHistory)
                    {
//                        qDebug() << oneHistory.status;

                        query->prepare("INSERT INTO flights_test5 ("
                                       "aircraft_id, date, flight_from, flight_to, "
                                       "flight, flight_time, std, atd, sta, status) "
                               "VALUES ("
                                       ":aircraft_id, :date, :flight_from, :flight_to, "
                                       ":flight, :flight_time, :std, :atd, :sta, :status"
                                       ")");

                        query->bindValue(":aircraft_id", aircraft.regNumber);
                        query->bindValue(":date", oneHistory.date);
                        query->bindValue(":flight_from", oneHistory.flight_from);
                        query->bindValue(":flight_to", oneHistory.flight_to);
                        query->bindValue(":flight", oneHistory.flight);
                        query->bindValue(":flight_time", oneHistory.flight_time);
                        query->bindValue(":std", oneHistory.std);
                        query->bindValue(":atd", oneHistory.atd);
                        query->bindValue(":sta", oneHistory.sta);
                        query->bindValue(":status", oneHistory.status);
                        query->exec();
                    }
                }
                delete query;
            }
            db.close();
            if (!db.isOpen())
            {
                qDebug() << "Close DB";
            }
        }
    }
}

void Server::sockDisc()
{
    qDebug() << "Disconnect";
    socket->deleteLater();
}
