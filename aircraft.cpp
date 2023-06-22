#include "aircraft.h"
#include <QVariant>

// Ключи параметров самолёта
const char* REG_NUMBER = "reg_number";
const char* URL_AIRCRAFT = "url_aircraft";
const char* AIRCRAFT = "aircraft";
const char* AIRLINE = "airline";
const char* OPERATOR = "operator";
const char* TYPE_CODE = "type_code";
const char* CODE_AIRLINE = "code_airline";
const char* CODE_OPERATOR = "code_operator";
const char* MODE_S = "mode_s";
const char* MSN = "serial_number_(msn)";
const char* AGE = "age";
const char* FLIGHTS_HISTORY = "flights_history";

// Ключи истории полёта
const char* H_FLIGHT = "flight";
const char* H_DATE = "date";
const char* H_TIME = "time";
const char* H_LANDED = "landed";
const char* H_STD = "std";
const char* H_ATD = "atd";
const char* H_STA = "sta";
const char* H_FROM = "from";
const char* H_TO = "to";

Aircraft::Aircraft(){}

Aircraft::~Aircraft(){}


Aircraft::Aircraft(QJsonObject jObj)
{
    m_regNumber = jObj.value(REG_NUMBER).toString();
    m_urlAircraft = jObj.value(URL_AIRCRAFT).toString();
    m_aircraft = jObj.value(AIRCRAFT).toString();
    m_airline = jObj.value(AIRLINE).toString();
    m_nameOperator = jObj.value(OPERATOR).toString();
    m_typeCode = jObj.value(TYPE_CODE).toString();
    m_codeAirlane = jObj.value(CODE_AIRLINE).toString();
    m_codeOperator  = jObj.value(CODE_OPERATOR).toString();
    m_modeS = jObj.value(MODE_S).toString();
    m_msn = jObj.value(MSN).toString();
    m_age = jObj.value(AGE).toString();

    QJsonArray jAllFlightsHistory = jObj.value(FLIGHTS_HISTORY).toArray();
    for (QJsonValue jOne_history : jAllFlightsHistory)
    {
        QJsonObject jHistory = jOne_history.toObject();
        m_allFlightsHistory.append(FlightHistory(jHistory));
    }
}


FlightHistory::FlightHistory(QJsonObject jObj)
{
    m_flight = jObj.value(H_FLIGHT).toString();
    m_date = jObj.value(H_DATE).toVariant().toString();
    m_flightTime = jObj.value(H_TIME).toString();
    m_status = jObj.value(H_LANDED).toString();
    m_std = jObj.value(H_STD).toString();
    m_atd = jObj.value(H_ATD).toString();
    m_sta = jObj.value(H_STA).toString();
    m_flightFrom = jObj.value(H_FROM).toString();
    m_flightTo = jObj.value(H_TO).toString();
}


AircraftsJsonController::AircraftsJsonController(QObject *parent)
    : QObject{parent}
{

}


void AircraftsJsonController::append(QJsonObject jAircraft)
{
    m_allAircrafts.append(Aircraft(jAircraft));
}


QList<Aircraft> AircraftsJsonController::get_list()
{
    return m_allAircrafts;
}

void AircraftsJsonController::clear()
{
    m_allAircrafts.clear();
}
