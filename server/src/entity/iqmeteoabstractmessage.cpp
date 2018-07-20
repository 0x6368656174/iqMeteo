#include "iqmeteoabstractmessage.h"

IqMeteoAbstractMessage::IqMeteoAbstractMessage(QObject *parent) :
    QObject(parent),
    m_type(IqMeteo::Type::Undefined)
{
}

IqMeteo::Type IqMeteoAbstractMessage::type() const
{
    return m_type;
}

void IqMeteoAbstractMessage::setType(const IqMeteo::Type &type)
{
    m_type = type;
}
