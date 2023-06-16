#include "aircraftdb.h"

AircraftDB::AircraftDB(QObject *parent)
    : QObject{parent}
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("yatube");
    db.setUserName("aircraft");
    db.setPassword("aircraft");
    ok = db.open();
}


void AircraftDB::create()
{
//    Создает таблицы в БД
//    TODO: доделать класс для записи в БД
//    TODO: добавить запрос на CREATE DATABASE aircraft;
    if (ok)
    {
        qDebug() << "Open DB and can create";
        QSqlQuery *query = new QSqlQuery(db);

        query->exec("CREATE TABLE IF NOT EXISTS aircrafts777("
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

        query->exec("CREATE TABLE IF NOT EXISTS flights777("
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
                    "FOREIGN KEY (aircraft_id) REFERENCES aircrafts777 (id)"
                    ");");
        delete query;
    }
}


void AircraftDB::insert(QList<Aircraft>* allAircraft)
{
    if (ok)
    {
        qDebug() << "Write in DB";
        QSqlQuery* query = new QSqlQuery(db);

        foreach (Aircraft aircraft, *allAircraft)
        {
            qDebug() << aircraft.regNumber;
//                    airdb.insert(aircraft);
            query->prepare("INSERT INTO aircrafts777 ("
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

                query->prepare("INSERT INTO flights777 ("
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
