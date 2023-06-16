#include "aircraftdb.h"

AircraftDB::AircraftDB(QObject *parent)
    : QObject{parent}
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("aircrafts");
    db.setUserName("aircraft");
    db.setPassword("aircraft");
}


void AircraftDB::create()
{
//    TODO: доделать класс для записи в БД
    if (db.open())
    {
        qDebug() << "Open DB and can create";
        QSqlQuery *query = new QSqlQuery(db);

        query->exec("DROP TABLE IF EXISTS aircraft CASCADE;");
        query->exec("DROP TABLE IF EXISTS flights;");

        query->exec("CREATE TABLE IF NOT EXISTS aircraft("
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
                    "FOREIGN KEY (aircraft_id) REFERENCES aircraft (id)"
                    ");");
        delete query;
    }
    db.close();
    if (!db.isOpen())
    {
        qDebug() << "Close DB";
    }
}


void AircraftDB::insert(QList<Aircraft>* allAircraft)
{
    if (db.open())
    {
        qDebug() << "Open DB and write";
        QSqlQuery* query = new QSqlQuery(db);

        foreach (Aircraft aircraft, *allAircraft)
        {
            query->prepare("INSERT INTO aircraft ("
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

            int aircraft_id = query->lastInsertId().toInt();

            foreach (FlightHistory oneHistory, aircraft.allFlightsHistory)
            {
                query->prepare("INSERT INTO flights ("
                               "aircraft_id, date, flight_from, flight_to, "
                               "flight, flight_time, std, atd, sta, status) "
                       "VALUES ("
                               ":aircraft_id, :date, :flight_from, :flight_to, "
                               ":flight, :flight_time, :std, :atd, :sta, :status"
                               ")");

                query->bindValue(":aircraft_id", aircraft_id);
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
