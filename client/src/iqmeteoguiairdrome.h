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

#ifndef IQMETEOGUIAIRDROME_H
#define IQMETEOGUIAIRDROME_H

#include <QObject>
#include <QJsonObject>

class IqMeteoGuiAirdrome
{
public:
    explicit IqMeteoGuiAirdrome();

    void setMetarFromJson(const QJsonObject &metar);

public:
    int id() const;
    void setId(int id);

    QString icaoCode() const;
    void setIcaoCode(const QString &code);

    QString name() const;
    void setName(const QString &name);

private:
    int m_id;
    QString m_icaoCode;
    QString m_name;
};


#endif //IQMETEOGUIAIRDROME_H
