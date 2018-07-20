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

#include "iqmeteopreveilingvisibility.h"

IqMeteoPrevailingVisibility::IqMeteoPrevailingVisibility(QObject *parent):
    QObject(parent),
    IqOrmObject(),
    m_average(0),
    m_min(0),
    m_minDirection(""),
    m_max(0),
    m_maxDirection(""),
    m_noDivision(false)
{
    iqOrmExtensionEnable(Extensions::Null);
}

void IqMeteoPrevailingVisibility::initializeOrmMetaModel(IqOrmMetaModel *model) const
{
    model->setTableName("prevailing_visibility");
    model->setDirect("average");
    model->setDirect("min");
    model->setDirect("minDirection", "min_direction");
    model->setDirect("max");
    model->setDirect("maxDirection", "max_direction");
    model->setDirect("noDivision", "no_division");
}

int IqMeteoPrevailingVisibility::average() const
{
    return m_average;
}

int IqMeteoPrevailingVisibility::min() const
{
    return m_min;
}

QString IqMeteoPrevailingVisibility::minDirection() const
{
    return m_minDirection;
}

int IqMeteoPrevailingVisibility::max() const
{
    return m_max;
}

QString IqMeteoPrevailingVisibility::maxDirection() const
{
    return m_maxDirection;
}

bool IqMeteoPrevailingVisibility::noDivision() const
{
    return m_noDivision;
}

void IqMeteoPrevailingVisibility::setAverage(int average)
{
    if (m_average != average) {
        m_average = average;
        emit averageChanged();
    }
}

void IqMeteoPrevailingVisibility::setMin(int min)
{
    if (m_min != min) {
        m_min = min;
        emit minChanged();
    }
}

void IqMeteoPrevailingVisibility::setMinDirection(const QString &minDirection)
{
    if (m_minDirection != minDirection) {
        m_minDirection = minDirection;
        emit minDirectionChanged();
    }
}

void IqMeteoPrevailingVisibility::setMax(int max)
{
    if (m_max != max) {
        m_max = max;
        emit maxChanged();
    }
}

void IqMeteoPrevailingVisibility::setMaxDirection(const QString &maxDirection)
{
    if (m_maxDirection != maxDirection) {
        m_maxDirection = maxDirection;
        emit maxDirectionChanged();
    }
}

void IqMeteoPrevailingVisibility::setNoDivision(bool noDivision)
{
    if (m_noDivision != noDivision) {
        m_noDivision = noDivision;
        emit noDivisionChanged();
    }
}

IqOrmSharedLazyPointerSet<IqMeteoRunwayVisibility> IqMeteoPrevailingVisibility::runwayVisibilities() const
{
    return m_runwayVisibilities;
}

void IqMeteoPrevailingVisibility::setRunwayVisibilities(const IqOrmSharedLazyPointerSet<IqMeteoRunwayVisibility> &runwayVisibilities)
{
    if (m_runwayVisibilities != runwayVisibilities) {
        m_runwayVisibilities = runwayVisibilities;
        emit runwayVisibilitiesChanged();
    }
}
