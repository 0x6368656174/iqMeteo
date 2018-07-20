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

#ifndef IQMETEOGUIMAINMODEL_H
#define IQMETEOGUIMAINMODEL_H

#include <QAbstractListModel>
#include <QJsonArray>
#include <QSharedPointer>
#include "iqmeteoguiairdrome.h"

class IqMeteoGuiMainModel: public QAbstractListModel
{
    Q_OBJECT
public:
    explicit IqMeteoGuiMainModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    void setAirdromesFromJson(const QJsonArray &airdromes);

    QSharedPointer<IqMeteoGuiAirdrome> airdrome(int id) const;

private:
    QList<QSharedPointer<IqMeteoGuiAirdrome> > m_airdromes;
    QHash<int, QSharedPointer<IqMeteoGuiAirdrome> > m_airdromesOnId;
};

#endif //IQMETEOGUIMAINMODEL_H
