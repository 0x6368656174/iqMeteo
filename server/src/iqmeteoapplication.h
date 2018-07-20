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

#ifndef IQMETEOAPPLICATION_H
#define IQMETEOAPPLICATION_H

#include <QObject>
#include "iqmeteoudplistener.h"
#include "src/entity/iqmeteocolor.h"
#include <IqWampRouter>
#include <IqWampYieldResult>

class IqMeteoApplication: public QObject
{
    Q_OBJECT
public:
    explicit IqMeteoApplication(QObject *parent = 0);

private:
    void onNewMetar(const QSharedPointer<IqMeteoMetar> &metar);

    IqWampYieldResult getMetars() const;
    IqWampYieldResult getAirdromes() const;

    QJsonObject createMetarMessage(const IqMeteoMetar *metar) const;

private:
    IqMeteoUdpListener *m_listener;
    IqWampRealm *m_mainRealm;
    IqWampRouter *m_wampServer;

    QString m_metarTopic;

    QHash<QString, IqMeteoColor *> m_colors;
};


#endif //IQMETEOAPPLICATION_H
