/**********************************************************************************
 * Copyright © 2016 Pavel A. Puchkov                                              *
 *                                                                                *
 * This file is part of IqMeteoServer.                                            *
 *                                                                                *
 * IqMeteoServer is free software: you can redistribute it and/or modify          *
 * it under the terms of the GNU Lesser General Public License as published by    *
 * the Free Software Foundation, either version 3 of the License, or              *
 * (at your option) any later version.                                            *
 *                                                                                *
 * IqMeteoServer is distributed in the hope that it will be useful,               *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                 *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                  *
 * GNU Lesser General Public License for more details.                            *
 *                                                                                *
 * You should have received a copy of the GNU Lesser General Public License       *
 * along with IqMeteoServer.  If not, see <http://www.gnu.org/licenses/>.         *
 **********************************************************************************/

#ifndef IQMETEOCOLORS_H
#define IQMETEOCOLORS_H

#include <QObject>
#include <IqOrmObject>

class IqMeteoColor: public QObject, public IqOrmObject
{
    Q_OBJECT
    IQORM_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
public:
    explicit IqMeteoColor(QObject *parent = 0);

public:
    virtual void initializeOrmMetaModel(IqOrmMetaModel *model) const override;

    QString name() const;
    void setName(const QString &name);

    QString color() const;
    void setColor(const QString &color);

signals:
    void nameChanged();
    void colorChanged();

private:
    QString m_name;
    QString m_color;
};

IQORM_REGISTER_CLASS(IqMeteoColor)

#endif //IQMETEOCOLORS_H
