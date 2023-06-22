#ifndef AIRCRAFT_H
#define AIRCRAFT_H


#include <QJsonArray>
#include <QJsonObject>


class FlightHistory  // класс истории полёта одного самолёта
{
public:
    FlightHistory(QJsonObject jObj);  // Создаёт поля класса из JSON
    QString get_m_flight(){return m_flight;}
    QString get_m_date(){return m_date;}
    QString get_m_flightTime(){return m_flightTime;}
    QString get_m_status(){return m_status;}
    QString get_m_std(){return m_std;}
    QString get_m_atd(){return m_atd;}
    QString get_m_sta(){return m_sta;}
    QString get_m_flightFrom(){return m_flightFrom;}
    QString get_m_flightTo(){return m_flightTo;}

private:
// Параметры истории одного полёта
    QString m_flight;  // номер рейса
    QString m_date;  // дата вылета
    QString m_flightTime;  // время в пути
    QString m_status;  // статус (в пути, приземлился, запланирован и т.д.)
    QString m_std;  // запланированное время отправления
    QString m_atd;  // фактическое время отправления
    QString m_sta;  // запланированное время прибытия
    QString m_flightFrom;  // откуда вылет
    QString m_flightTo;  // куда прилёт
};


class Aircraft  // класс самолёта
{
public:
    Aircraft();
    ~Aircraft();
    Aircraft(QJsonObject jObj);  // Создаёт поля класса из JSON

    QString get_m_aircraft(){return m_aircraft;}
    QString get_m_regNumber(){return m_regNumber;}
    QString get_m_urlAircraft(){return m_urlAircraft;}
    QString get_m_airline(){return m_airline;}
    QString get_m_nameOperator(){return m_nameOperator;}
    QString get_m_typeCode(){return m_typeCode;}
    QString get_m_codeAirlane(){return m_codeAirlane;}
    QString get_m_codeOperator(){return m_codeOperator;}
    QString get_m_modeS(){return m_modeS;}
    QString get_m_msn(){return m_msn;}
    QString get_m_age(){return m_age;}
    QList<FlightHistory> get_m_allFlightsHistory(){return m_allFlightsHistory;}

private:
// Параметры самолёта
    QString m_aircraft;  // Модель самолёта
    QString m_regNumber;  // Регистрационный номер
    QString m_urlAircraft;  // ссылка на сайте flightradar24.com на самолёт
    QString m_airline;  // Название авиакомпании
    QString m_nameOperator;  // Имя оператора
    QString m_typeCode;  // Тип самолёта
    QString m_codeAirlane;  // Код авиакомпании
    QString m_codeOperator;  // Код ооператора
    QString m_modeS; // Mode-S
    QString m_msn;  // Серийный номер
    QString m_age;  // Возраст самолёта
    QList<FlightHistory> m_allFlightsHistory;  // список объектов FlightHistory - история полётов самолёта
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
    QList<Aircraft> m_allAircrafts;  // список всех объектов класса "Самолёт"
};
#endif // AIRCRAFT_H
