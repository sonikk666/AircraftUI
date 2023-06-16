#ifndef AIRCRAFT_H
#define AIRCRAFT_H


#include <QJsonArray>
#include <QJsonObject>


class FlightHistory  // класс истории полёта одного самолёта
{
public:
    FlightHistory(QJsonObject jObj);  // Создаёт поля класса из JSON

// Параметры истории одного полёта
    QString flight;  // номер рейса
    QString date;  // дата вылета
    QString flight_time;  // время в пути
    QString status;  // статус (в пути, приземлился, запланирован и т.д.)
    QString std;  // запланированное время отправления
    QString atd;  // фактическое время отправления
    QString sta;  // запланированное время прибытия
    QString flight_from;  // откуда вылет
    QString flight_to;  // куда прилёт
};


class Aircraft  // класс самолёта
{
public:
    Aircraft();
    ~Aircraft();

    Aircraft(QJsonObject jObj);  // Создаёт поля класса из JSON

// Параметры самолёта
    QString aircraft;  // Модель самолёта
    QString regNumber;  // Регистрационный номер
    QString urlAircraft;  // ссылка на сайте flightradar24.com на самолёт
    QString airline;  // Название авиакомпании
    QString nameOperator;  // Имя оператора
    QString typeCode;  // Тип самолёта
    QString codeAirlane;  // Код авиакомпании
    QString codeOperator;  // Код ооператора
    QString modeS; // Mode-S
    QString msn;  // Серийный номер
    QString age;  // Возраст самолёта
    QList<FlightHistory> allFlightsHistory;  // список объектов FlightHistory - история полётов самолёта
};

// нужно для передачи данных из одного ListWidget в другой - item->setData(Qt::UserRole, var);
Q_DECLARE_METATYPE(class Aircraft)


// класс для действий над json (создание объекта, добавление в список, возврат, очистка)
class AircraftsJsonController : public QObject
{
    Q_OBJECT

public:
    explicit AircraftsJsonController(QObject *parent = nullptr);
    void append(QJsonObject json);  // вызывает создание объекта "Самолёт" и добавляет в список _allAircrafts
    QList<Aircraft> get_list();  // возвращает список всех объектов
    void clear();  // очищает список _allAircrafts

private:
    QList<Aircraft> _allAircrafts;  // список всех объектов класса "Самолёт"
};
#endif // AIRCRAFT_H
