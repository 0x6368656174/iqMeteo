/**********************************************************************************
 * Copyright © 2016 Pavel A. Puchkov                                              *
 *                                                                                *
 * This file is part of IqMeteo.                                                  *
 *                                                                                *
 * IqMeteo is free software: you can redistribute it and/or modify                *
 * it under the terms of the GNU Lesser General Public License as published by    *
 * the Free Software Foundation, either version 3 of the License, or              *
 * (at your option) any later version.                                            *
 *                                                                                *
 * IqMeteo is distributed in the hope that it will be useful,                     *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                 *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                  *
 * GNU Lesser General Public License for more details.                            *
 *                                                                                *
 * You should have received a copy of the GNU Lesser General Public License       *
 * along with IqMeteo.  If not, see <http://www.gnu.org/licenses/>.               *
 **********************************************************************************/

#define SETTINGS_DB_GROUP "db"
#define SETTINGS_DB_TYPE "type"
#define SETTINGS_DB_HOST "host"
#define SETTINGS_DB_NAME "name"
#define SETTINGS_DB_USER "user"
#define SETTINGS_DB_PASSWORD "user"

#define SETTINGS_WAMP_GROUP "wamp"
#define SETTINGS_WAMP_REALM "realm"
#define SETTINGS_WAMP_PORT "port"

#define SETTINGS_WAMP_METAR_TOPIC "metarTopic"
#define SETTINGS_WAMP_METAR_LIST_URI "metarListUri"
#define SETTINGS_WAMP_AIRDROME_LIST_URI "airdromeListUri"

#include "iqmeteoapplication.h"
#include <QSettings>
#include <IqOrmSqlDataSource>
#include <IqOrmCore>
#include <IqOrmModel>
#include <QJsonDocument>

IqMeteoApplication::IqMeteoApplication(QObject *parent) :
    QObject(parent),
    m_listener(new IqMeteoUdpListener(this)),
    m_mainRealm(Q_NULLPTR),
    m_wampServer(new IqWampRouter(this))
{
    QSettings settings;
    settings.beginGroup(SETTINGS_DB_GROUP);
    if (!settings.contains(SETTINGS_DB_TYPE))
        settings.setValue(SETTINGS_DB_TYPE, "QMYSQL");
    if (!settings.contains(SETTINGS_DB_HOST))
        settings.setValue(SETTINGS_DB_HOST, "localhost");
    if (!settings.contains(SETTINGS_DB_NAME))
        settings.setValue(SETTINGS_DB_NAME, "iq_meteo");
    if (!settings.contains(SETTINGS_DB_USER))
        settings.setValue(SETTINGS_DB_USER, "user");
    if (!settings.contains(SETTINGS_DB_PASSWORD))
        settings.setValue(SETTINGS_DB_PASSWORD, "password");

    QSqlDatabase db = QSqlDatabase::addDatabase(settings.value(SETTINGS_DB_TYPE).toString());
    db.setHostName(settings.value(SETTINGS_DB_HOST).toString());
    db.setDatabaseName(settings.value(SETTINGS_DB_NAME).toString());
    db.setUserName(settings.value(SETTINGS_DB_USER).toString());
    db.setPassword(settings.value(SETTINGS_DB_PASSWORD).toString());

    settings.endGroup();

    IqOrmSqlDataSource *dataSource = new IqOrmSqlDataSource();
    dataSource->setDatabase(db);

    IqOrmCore::setDataSource(dataSource);

    IqOrmModel<IqMeteoColor> colorsModel;
    colorsModel.load();
    for (IqMeteoColor *color : colorsModel.takeAll()) {
        color->setParent(this);
        m_colors[color->name()] = color;
    }

    settings.beginGroup(SETTINGS_WAMP_GROUP);
    if (!settings.contains(SETTINGS_WAMP_REALM))
        settings.setValue(SETTINGS_WAMP_REALM, "main");
    if (!settings.contains(SETTINGS_WAMP_PORT))
        settings.setValue(SETTINGS_WAMP_PORT, 12000);
    if (!settings.contains(SETTINGS_WAMP_METAR_TOPIC))
        settings.setValue(SETTINGS_WAMP_METAR_TOPIC, "ru.itquasar.meteo.metar");
    if (!settings.contains(SETTINGS_WAMP_METAR_LIST_URI))
        settings.setValue(SETTINGS_WAMP_METAR_LIST_URI, "ru.itquasar.meteo.metar.list");
    if (!settings.contains(SETTINGS_WAMP_AIRDROME_LIST_URI))
        settings.setValue(SETTINGS_WAMP_AIRDROME_LIST_URI, "ru.itquasar.meteo.airdrome.list");

    m_mainRealm = new IqWampRealm(settings.value(SETTINGS_WAMP_REALM).toString(), this);

    m_wampServer->addRealm(m_mainRealm);

    m_metarTopic = settings.value(SETTINGS_WAMP_METAR_TOPIC).toString();

    connect(m_listener, &IqMeteoUdpListener::metarReserved, this, &IqMeteoApplication::onNewMetar);

    m_mainRealm->localClient()->registerProcedure(settings.value(SETTINGS_WAMP_METAR_LIST_URI).toString(), this, &IqMeteoApplication::getMetars);
    m_mainRealm->localClient()->registerProcedure(settings.value(SETTINGS_WAMP_AIRDROME_LIST_URI).toString(), this, &IqMeteoApplication::getAirdromes);

    m_wampServer->listen(static_cast<quint16>(settings.value(SETTINGS_WAMP_PORT).toInt()));

    settings.endGroup();
}

void IqMeteoApplication::onNewMetar(const QSharedPointer<IqMeteoMetar> &metar)
{
    QJsonObject message = createMetarMessage(metar.data());

    m_mainRealm->localClient()->publish(m_metarTopic, message);
}

IqWampYieldResult IqMeteoApplication::getMetars() const
{
    QDateTime lastDay = QDateTime::currentDateTime();
    constexpr int daySecs = -3600*24;
    lastDay = lastDay.addSecs(daySecs);

    IqOrmModel<IqMeteoMetar> metars;
    metars.find("observationDateTime", IqOrmFilter::GreaterOrEquals, lastDay);

    QJsonArray metarsResult;

    for(const IqMeteoMetar *metar: metars.toList()) {
        metarsResult.append(createMetarMessage(metar));
    }

    return IqWampYieldResult(metarsResult);
}

QJsonObject IqMeteoApplication::createMetarMessage(const IqMeteoMetar *metar) const
{
//    QJsonObject message;

    QJsonObject metarMessage;
    if (metar->airdrome())
        metarMessage.insert("airdromeId", metar->airdrome()->objectId());

    if (!metar->isPropertyNull("sourceText"))
        metarMessage.insert("sourceText", metar->sourceText());
    if (!metar->isPropertyNull("observationDateTime"))
        metarMessage.insert("observationDateTime", metar->observationDateTime().toString("d.MM.yyyy hh:mm"));
    if (!metar->isPropertyNull("temperature"))
        metarMessage.insert("temperature", metar->temperature());
    if (!metar->isPropertyNull("dewPoint"))
        metarMessage.insert("dewPoint", metar->dewPoint());
    if (!metar->isPropertyNull("qnh"))
        metarMessage.insert("qnh", metar->qnh());

    QJsonArray textDecorations;
    for (const IqMeteoTextDecoration &textDecoration : metar->textDecorations()) {
        IqMeteoColor *color = m_colors[textDecoration.color];
        if (color) {
            QJsonObject decoration;
            decoration.insert("start", textDecoration.start);
            decoration.insert("length", textDecoration.length);
            decoration.insert("color", color->color());
            textDecorations.append(decoration);
        }
    }
    metarMessage.insert("textDecoration", textDecorations);

    QJsonObject metarWindMessage;
    if (!metar->wind()->isPropertyNull("variableDirection"))
        metarWindMessage.insert("variableDirection", metar->wind()->variableDirection());
    if (!metar->wind()->isPropertyNull("direction"))
        metarWindMessage.insert("direction", metar->wind()->direction());
    if (!metar->wind()->isPropertyNull("speed"))
        metarWindMessage.insert("speed", metar->wind()->speed());
    if (!metar->wind()->isPropertyNull("measurements"))
        metarWindMessage.insert("measurements", metar->wind()->measurements());
    if (!metar->wind()->isPropertyNull("gust"))
        metarWindMessage.insert("gust", metar->wind()->gust());
    if (!metar->wind()->isPropertyNull("variableDirectionMin"))
        metarWindMessage.insert("variableDirectionMin", metar->wind()->variableDirectionMin());
    if (!metar->wind()->isPropertyNull("variableDirectionMax"))
        metarWindMessage.insert("variableDirectionMax", metar->wind()->variableDirectionMax());
    metarMessage.insert("wind", metarWindMessage);
//
//    message.insert("metar", metarMessage);
//
//    QJsonObject airdrome;
//    if (!metar->airdrome()->isPropertyNull("name"))
//        airdrome.insert("name", metar->airdrome()->name());
//    if (!metar->airdrome()->isPropertyNull("icaoCode"))
//        airdrome.insert("icaoCode", metar->airdrome()->icaoCode());
//    message.insert("airdrome", airdrome);

    return metarMessage;
}

IqWampYieldResult IqMeteoApplication::getAirdromes() const
{
    IqOrmModel<IqMeteoAirdrome> airdromes;
    airdromes.findAll();

    QJsonArray metarsResult;

    for(const IqMeteoAirdrome *airdrome: airdromes.toList()) {
        QJsonObject airdromeObject;
        airdromeObject.insert("id", airdrome->objectId());
        airdromeObject.insert("name", airdrome->name());
        airdromeObject.insert("icaoCode", airdrome->icaoCode());

        metarsResult.append(airdromeObject);
    }

    return IqWampYieldResult(metarsResult);
}



