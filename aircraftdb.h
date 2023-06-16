#ifndef AIRCRAFTDB_H
#define AIRCRAFTDB_H

#include "aircraft.h"

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>

class AircraftDB : public QObject
{
    Q_OBJECT
public:
    explicit AircraftDB(QObject *parent = nullptr);
    QSqlDatabase db;
    bool ok;
    void create();  // создаёт таблицы в БД
    void insert(QList<Aircraft>* allAircraft);  // записывает в БД
};

#endif // AIRCRAFTDB_H
