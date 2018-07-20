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

#ifndef IQMETEOPREVAILINGVISIBILITY_H
#define IQMETEOPREVAILINGVISIBILITY_H

#include <QObject>
#include <IqOrmObject>
#include "iqmeteorunwayvisibility.h"

class IqMeteoPrevailingVisibility: public QObject, public IqOrmObject
{
    Q_OBJECT
    IQORM_OBJECT

    Q_PROPERTY(int average READ average WRITE setAverage NOTIFY averageChanged)
    Q_PROPERTY(int min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(QString minDirection READ minDirection WRITE setMinDirection NOTIFY minDirectionChanged)
    Q_PROPERTY(int max READ max WRITE setMax NOTIFY maxChanged)
    Q_PROPERTY(QString maxDirection READ maxDirection WRITE setMaxDirection NOTIFY maxDirectionChanged)
    Q_PROPERTY(bool noDivision READ noDivision WRITE setNoDivision NOTIFY noDivisionChanged)
    Q_PROPERTY(IqOrmSharedLazyPointerSet<IqMeteoRunwayVisibility> runwayVisibilities READ runwayVisibilities WRITE setRunwayVisibilities NOTIFY runwayVisibilitiesChanged)
public:
    explicit IqMeteoPrevailingVisibility(QObject *parent = 0);

public:
    virtual void initializeOrmMetaModel(IqOrmMetaModel *model) const override;

    int average() const;
    void setAverage(int average);

    int min() const;
    void setMin(int min);

    QString minDirection() const;
    void setMinDirection(const QString &minDirection);

    int max() const;
    void setMax(int max);

    QString maxDirection() const;
    void setMaxDirection(const QString &maxDirection);

    bool noDivision() const;
    void setNoDivision(bool noDivision);

    IqOrmSharedLazyPointerSet<IqMeteoRunwayVisibility> runwayVisibilities() const;
    void setRunwayVisibilities(const IqOrmSharedLazyPointerSet<IqMeteoRunwayVisibility> &runwayVisibilities);

signals:
    void averageChanged();
    void minChanged();
    void minDirectionChanged();
    void maxChanged();
    void maxDirectionChanged();
    void noDivisionChanged();
    void runwayVisibilitiesChanged();

private:
    int m_average;
    int m_min;
    QString m_minDirection;
    int m_max;
    QString m_maxDirection;
    bool m_noDivision;

    IqOrmSharedLazyPointerSet<IqMeteoRunwayVisibility> m_runwayVisibilities;
};

IQORM_REGISTER_CLASS(IqMeteoPrevailingVisibility)

#endif //IQMETEOPREVAILINGVISIBILITY_H
