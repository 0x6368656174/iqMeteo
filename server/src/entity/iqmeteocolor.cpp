/**********************************************************************************
 * Copyright © 2016 Pavel A. Puchkov                                              *
 *                                                                                *
 * This file is part of IqMeteoServer.                                                    *
 *                                                                                *
 * IqMeteoServer is free software: you can redistribute it and/or modify                  *
 * it under the terms of the GNU Lesser General Public License as published by    *
 * the Free Software Foundation, either version 3 of the License, or              *
 * (at your option) any later version.                                            *
 *                                                                                *
 * IqMeteoServer is distributed in the hope that it will be useful,                       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                 *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                  *
 * GNU Lesser General Public License for more details.                            *
 *                                                                                *
 * You should have received a copy of the GNU Lesser General Public License       *
 * along with IqMeteoServer.  If not, see <http://www.gnu.org/licenses/>.                 *
 **********************************************************************************/

#include "iqmeteocolor.h"

IqMeteoColor::IqMeteoColor(QObject *parent):
    QObject(parent),
    IqOrmObject()
{
    iqOrmExtensionEnable(Extensions::Null);
}

void IqMeteoColor::initializeOrmMetaModel(IqOrmMetaModel *model) const
{
    model->setTableName("colors");
    model->setDirect("name");
    model->setDirect("color");
}

QString IqMeteoColor::name() const
{
    return m_name;
}

void IqMeteoColor::setName(const QString &name)
{
    if (m_name != name) {
        m_name = name;

        emit nameChanged();
    }
}

QString IqMeteoColor::color() const
{
    return m_color;
}

void IqMeteoColor::setColor(const QString &color)
{
    if (m_color != color) {
        m_color = color;

        emit colorChanged();
    }
}
