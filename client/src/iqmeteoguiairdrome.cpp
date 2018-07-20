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

#include "iqmeteoguiairdrome.h"

IqMeteoGuiAirdrome::IqMeteoGuiAirdrome():
    m_id(0)
{
}

int IqMeteoGuiAirdrome::id() const
{
    return m_id;
}

void IqMeteoGuiAirdrome::setId(int id)
{
    m_id = id;
}

QString IqMeteoGuiAirdrome::icaoCode() const
{
    return m_icaoCode;
}

void IqMeteoGuiAirdrome::setIcaoCode(const QString &code)
{
    m_icaoCode = code;
}

QString IqMeteoGuiAirdrome::name() const
{
    return m_name;
}

void IqMeteoGuiAirdrome::setName(const QString &name)
{
    m_name = name;
}

void IqMeteoGuiAirdrome::setMetarFromJson(const QJsonObject &metar)
{

}

