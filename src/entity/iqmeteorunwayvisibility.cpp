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

#include "iqmeteorunwayvisibility.h"

IqMeteoRunwayVisibility::IqMeteoRunwayVisibility(QObject *parent):
    QObject(parent),
    IqOrmObject(),
    m_runwayName(""),
    m_average(0),
    m_tendency(""),
    m_max(0),
    m_min(0)
{
}

void IqMeteoRunwayVisibility::initializeOrmMetaModel(IqOrmMetaModel *model) const
{
    model->setTableName("runway_visibility");
    model->setDirect("runwayName", "runway_name");
    model->setDirect("average");
    model->setDirect("tendency");
    model->setDirect("min");
    model->setDirect("max");
}

QString IqMeteoRunwayVisibility::runwayName() const
{
    return m_runwayName;
}

void IqMeteoRunwayVisibility::setRunwayName(const QString &runwayName)
{
    if (m_runwayName != runwayName) {
        m_runwayName = runwayName;
        emit runwayNameChanged();
    }
}

int IqMeteoRunwayVisibility::average() const
{
    return m_average;
}

void IqMeteoRunwayVisibility::setAverage(int average)
{
    if (m_average != average) {
        m_average = average;
        emit averageChanged();
    }
}

QString IqMeteoRunwayVisibility::tendency() const
{
    return m_tendency;
}

void IqMeteoRunwayVisibility::setTendency(QString tendency)
{
    if (m_tendency != tendency) {
        m_tendency = tendency;
        emit tendencyChanged();
    }
}

int IqMeteoRunwayVisibility::min() const
{
    return m_min;
}

void IqMeteoRunwayVisibility::setMin(int min)
{
    if (m_min != min) {
        m_min = min;
        emit minChanged();
    }
}

int IqMeteoRunwayVisibility::max() const
{
    return m_max;
}

void IqMeteoRunwayVisibility::setMax(int max)
{
    if (m_max != max) {
        m_max = max;
        emit maxChanged();
    }
}
