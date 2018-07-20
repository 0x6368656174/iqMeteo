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

#ifndef IQMETEORUNWAYVISIBILITY_H
#define IQMETEORUNWAYVISIBILITY_H

#include <QObject>
#include <IqOrmObject>

class IqMeteoRunwayVisibility: public QObject, public IqOrmObject
{
    Q_OBJECT
    IQORM_OBJECT

    Q_PROPERTY(QString runwayName READ runwayName WRITE setRunwayName NOTIFY runwayNameChanged)
    Q_PROPERTY(int average READ average WRITE setAverage NOTIFY averageChanged)
    Q_PROPERTY(QString tendency READ tendency WRITE setTendency NOTIFY tendencyChanged)
    Q_PROPERTY(int min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(int max READ max WRITE setMax NOTIFY maxChanged)
public:
    explicit IqMeteoRunwayVisibility(QObject *parent = 0);

public:
    virtual void initializeOrmMetaModel(IqOrmMetaModel *model) const override;

    QString runwayName() const;
    void setRunwayName(const QString &runwayName);

    int average() const;
    void setAverage(int average);

    QString tendency() const;
    void setTendency(QString tendency);

    int min() const;
    void setMin(int min);

    int max() const;
    void setMax(int max);

signals:
    void runwayNameChanged();
    void averageChanged();
    void tendencyChanged();
    void variableChanged();
    void minChanged();
    void maxChanged();

private:
    QString m_runwayName;
    int m_average;
    QString m_tendency;
    int m_max;
    int m_min;
};

IQORM_REGISTER_CLASS(IqMeteoRunwayVisibility)

#endif //IQMETEORUNWAYVISIBILITY_H
