#include "iqmeteometar.h"

IqMeteoMetar::IqMeteoMetar(QObject *parent) :
    QObject(parent),
    IqOrmObject(),
    m_temperature(0),
    m_dewPoint(0),
    m_qnh(0),
    m_sourceText(""),
    m_wind(IqOrmSharedLazyPointer<IqMeteoMetarWind>(new IqMeteoMetarWind())),
    m_prevailingVisibility(IqOrmSharedLazyPointer<IqMeteoPrevailingVisibility>(new IqMeteoPrevailingVisibility()))
{
}

void IqMeteoMetar::initializeOrmMetaModel(IqOrmMetaModel *model) const
{
    model->setTableName("metars");
    model->setDirect("observationDateTime", "observation_date_time");
    model->setDirect("temperature");
    model->setDirect("dewPoint", "dew_point");
    model->setDirect("qnh");
    model->setDirect("sourceText", "source_text");

    model->setOneToOne<IqMeteoMetarWind>("wind", "id_winds");
    model->setManyToOne<IqMeteoAirdrome>("airdrome", "id_airdrome");
    model->setOneToOne<IqMeteoPrevailingVisibility>("prevailingVisibility", "id_prevailing_visibility");
}


QDateTime IqMeteoMetar::observationDateTime() const
{
    return m_observationDateTime;
}

void IqMeteoMetar::setObservationDateTime(const QDateTime &observationDateTime)
{
    if (m_observationDateTime != observationDateTime) {
        m_observationDateTime = observationDateTime;
        emit observationDateTimeChanged();
    }
}

int IqMeteoMetar::temperature() const
{
    return m_temperature;
}

void IqMeteoMetar::setTemperature(int temperature)
{
    if (m_temperature != temperature) {
        m_temperature = temperature;
        emit temperatureChanged();
    }
}

int IqMeteoMetar::dewPoint() const
{
    return m_dewPoint;
}

void IqMeteoMetar::setDewPoint(int dewPoint)
{
    if (m_dewPoint != dewPoint) {
        m_dewPoint = dewPoint;
        emit dewPointChanged();
    }
}

int IqMeteoMetar::qnh() const
{
    return m_qnh;
}

void IqMeteoMetar::setQnh(int qnh)
{
    if (m_qnh != qnh) {
        m_qnh = qnh;
        emit qnhChanged();
    }
}

QString IqMeteoMetar::sourceText() const
{
    return m_sourceText;
}

void IqMeteoMetar::setSourceText(const QString &sourceText)
{
    if (m_sourceText != sourceText) {
        m_sourceText = sourceText;
        emit sourceTextChanged();
    }
}

IqOrmSharedLazyPointer<IqMeteoMetarWind> IqMeteoMetar::wind() const
{
    return m_wind;
}

void IqMeteoMetar::setWind(const IqOrmSharedLazyPointer<IqMeteoMetarWind> &wind)
{
    if (m_wind != wind) {
        m_wind = wind;
        emit windChanged();
    }
}

IqOrmSharedLazyPointer<IqMeteoAirdrome> IqMeteoMetar::airdrome() const
{
    return m_airdrome;
}

void IqMeteoMetar::setAirdrome(const IqOrmSharedLazyPointer<IqMeteoAirdrome> &airdrome)
{
    if (m_airdrome != airdrome) {
        m_airdrome = airdrome;
        emit airdromeChanged();
    }
}
IqOrmSharedLazyPointer<IqMeteoPrevailingVisibility> IqMeteoMetar::prevailingVisibility() const
{
    return m_prevailingVisibility;
}

void IqMeteoMetar::setPrevailingVisibility(const IqOrmSharedLazyPointer<IqMeteoPrevailingVisibility> &prevailingVisibility)
{
    if (m_prevailingVisibility != prevailingVisibility) {
        m_prevailingVisibility = prevailingVisibility;
        emit prevailingVisibilityChanged();
    }
}
