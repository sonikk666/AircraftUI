#include "aircraft.h"
#include <QVariant>

// Ключи параметров самолёта
#define REG_NUMBER "reg_number"
#define URL_AIRCRAFT "url_aircraft"
#define AIRCRAFT "aircraft"
#define AIRLINE "airline"
#define OPERATOR "operator"
#define TYPE_CODE "type_code"
#define CODE_AIRLINE "code_airline"
#define CODE_OPERATOR "code_operator"
#define MODE_S "mode_s"
#define MSN "serial_number_(msn)"
#define AGE "age"
#define FLIGHTS_HISTORY "flights_history"

// Ключи истории полёта
#define H_FLIGHT "flight"
#define H_DATE "date"
#define H_TIME "time"
#define H_LANDED "landed"
#define H_STD "std"
#define H_ATD "atd"
#define H_STA "sta"
#define H_FROM "from"
#define H_TO "to"

Aircraft::Aircraft(){}

Aircraft::~Aircraft(){}


Aircraft::Aircraft(QJsonObject jObj)
{
    regNumber = jObj.value(REG_NUMBER).toString();
    urlAircraft = jObj.value(URL_AIRCRAFT).toString();
    aircraft = jObj.value(AIRCRAFT).toString();
    airline = jObj.value(AIRLINE).toString();
    nameOperator = jObj.value(OPERATOR).toString();
    typeCode = jObj.value(TYPE_CODE).toString();
    codeAirlane = jObj.value(CODE_AIRLINE).toString();
    codeOperator  = jObj.value(CODE_OPERATOR).toString();
    modeS = jObj.value(MODE_S).toString();
    msn = jObj.value(MSN).toString();
    age = jObj.value(AGE).toString();

    QJsonArray jAllFlightsHistory = jObj.value(FLIGHTS_HISTORY).toArray();
    for (QJsonValue jOne_history : jAllFlightsHistory)
    {
        QJsonObject jHistory = jOne_history.toObject();
        allFlightsHistory.append(FlightHistory(jHistory));
    }
}


FlightHistory::FlightHistory(QJsonObject jObj)
{
    flight = jObj.value(H_FLIGHT).toString();
    date = jObj.value(H_DATE).toVariant().toString();
    flight_time = jObj.value(H_TIME).toString();
    status = jObj.value(H_LANDED).toString();
    std = jObj.value(H_STD).toString();
    atd = jObj.value(H_ATD).toString();
    sta = jObj.value(H_STA).toString();
    flight_from = jObj.value(H_FROM).toString();
    flight_to = jObj.value(H_TO).toString();
}


AircraftsJsonController::AircraftsJsonController(QObject *parent)
    : QObject{parent}
{

}


void AircraftsJsonController::append(QJsonObject jAircraft)
{
    _allAircrafts.append(Aircraft(jAircraft));
}


QList<Aircraft> AircraftsJsonController::get_list()
{
    return _allAircrafts;
}

void AircraftsJsonController::clear()
{
    _allAircrafts.clear();
}
