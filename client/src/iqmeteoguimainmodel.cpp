/**********************************************************************************
 * Copyright © 2016 Pavel A. Puchkov                                              *
 *                                                                                *
 * This file is part of IqMeteo.                                                    *
 *                                                                                *
 * IqMeteo is free software: you can redistribute it and/or modify                  *
 * it under the terms of the GNU Lesser General Public License as published by    *
 * the Free Software Foundation, either version 3 of the License, or              *
 * (at your option) any later version.                                            *
 *                                                                                *
 * IqMeteo is distributed in the hope that it will be useful,                       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                 *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                  *
 * GNU Lesser General Public License for more details.                            *
 *                                                                                *
 * You should have received a copy of the GNU Lesser General Public License       *
 * along with IqMeteo.  If not, see <http://www.gnu.org/licenses/>.                 *
 **********************************************************************************/

#include "iqmeteoguimainmodel.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>

IqMeteoGuiMainModel::IqMeteoGuiMainModel(QObject *parent):
    QAbstractListModel(parent)
{
}

int IqMeteoGuiMainModel::rowCount(const QModelIndex &parent) const
{
    return m_airdromes.count();
}

QVariant IqMeteoGuiMainModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    QSharedPointer<IqMeteoGuiAirdrome> airdrome = m_airdromes[row];

    switch (role) {
        case Qt::DisplayRole: {
            return QString("%0 - %1").arg(airdrome->icaoCode()).arg(airdrome->name());
        }
    }

    return QVariant();
}

void IqMeteoGuiMainModel::setAirdromesFromJson(const QJsonArray &airdromes)
{
    emit beginRemoveRows(QModelIndex(), 0, m_airdromes.count() - 1);
    m_airdromes.clear();
    m_airdromesOnId.clear();
    emit endRemoveRows();

    emit beginInsertRows(QModelIndex(), 0, airdromes.count() - 1);
    for (const QJsonValue &airdrome: airdromes) {
        QJsonObject airdromeJsonObject = airdrome.toObject();

        if (airdromeJsonObject.value("id").toInt(-1) == -1) {
            qWarning() << "Reserve airdrome without id" << airdromeJsonObject;
            continue;
        }

        QSharedPointer<IqMeteoGuiAirdrome> airdromeObject = QSharedPointer<IqMeteoGuiAirdrome>::create();
        airdromeObject->setId(airdromeJsonObject.value("id").toInt());
        airdromeObject->setIcaoCode(airdromeJsonObject.value("icaoCode").toString());
        airdromeObject->setName(airdromeJsonObject.value("name").toString());

        m_airdromes << airdromeObject;
        m_airdromesOnId[airdromeObject->id()] = airdromeObject;
    }
    emit endInsertRows();
}

QSharedPointer<IqMeteoGuiAirdrome> IqMeteoGuiMainModel::airdrome(int id) const
{
    return m_airdromesOnId[id];
}


