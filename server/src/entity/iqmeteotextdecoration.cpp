/**********************************************************************************
 **
 ** Copyright © 2016 Pavel A. Puchkov 
 **
 ** This file is part of IqMeteoServer. 
 **
 ** IqMeteoServer is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** IqMeteoServer is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with IqMeteoServer.  If not, see <http://www.gnu.org/licenses/>.
 **
 **********************************************************************************/

#include "iqmeteotextdecoration.h"

IqMeteoTextDecoration::IqMeteoTextDecoration() :
    start(0),
    length(0),
    color("")
{
}

IqMeteoTextDecoration::IqMeteoTextDecoration(int start, int length, const QString &color):
    start(start),
    length(length),
    color(color)
{
}

QJsonObject IqMeteoTextDecoration::toJson() const
{
    QJsonObject result;
    result.insert("start", start);
    result.insert("length", length);
    result.insert("color", color);

    return result;
}

void IqMeteoTextDecoration::fromJson(QJsonObject jsonObject)
{
    start = jsonObject.value("start").toInt();
    length = jsonObject.value("length").toInt();
    color = jsonObject.value("color").toString();
}






