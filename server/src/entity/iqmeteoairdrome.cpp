#include "iqmeteoairdrome.h"

IqMeteoAirdrome::IqMeteoAirdrome(QObject *parent) :
    QObject(parent),
    IqOrmObject(),
    m_name(""),
    m_icaoCode("")
{
    iqOrmExtensionEnable(Extensions::Null);
}

void IqMeteoAirdrome::initializeOrmMetaModel(IqOrmMetaModel *model) const
{
    model->setTableName("airdrome");
    model->setDirect("name");
    model->setDirect("icaoCode", "icao_code");
}

QString IqMeteoAirdrome::name() const
{
    return m_name;
}

void IqMeteoAirdrome::setName(const QString &name)
{
    if (m_name != name) {
        m_name = name;
        emit nameChanged();
    }
}

QString IqMeteoAirdrome::icaoCode() const
{
    return m_icaoCode;
}

void IqMeteoAirdrome::setIcaoCode(const QString &icaoCode)
{
    if (m_icaoCode != icaoCode) {
        m_icaoCode = icaoCode;
        emit icaoCodeChanged();
    }
}
