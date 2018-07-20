#ifndef IQMETEOABSTRACTMESSAGE_H
#define IQMETEOABSTRACTMESSAGE_H

#include <QObject>
#include "../iqmeteo.h"

class IqMeteoAbstractMessage : public QObject
{
    Q_OBJECT
public:
    explicit IqMeteoAbstractMessage(QObject *parent = 0);

public:
    IqMeteo::Type type() const;

protected:
    void setType(const IqMeteo::Type &type);

private:
    IqMeteo::Type m_type;
};

#endif // IQMETEOABSTRACTMESSAGE_H
