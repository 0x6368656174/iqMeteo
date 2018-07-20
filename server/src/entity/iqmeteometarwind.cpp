#include "iqmeteometarwind.h"

IqMeteoMetarWind::IqMeteoMetarWind(QObject *parent) :
    QObject(parent),
    IqOrmObject(),
    m_variableDirection(false),
    m_direction(0),
    m_speed(0),
    m_measurements(""),
    m_gust(0),
    m_variableDirectionMin(0),
    m_variableDirectionMax(0)
{
    iqOrmExtensionEnable(Extensions::Null);
}

void IqMeteoMetarWind::initializeOrmMetaModel(IqOrmMetaModel *model) const
{
    model->setTableName("winds");
    model->setDirect("variableDirection", "variable");
    model->setDirect("direction");
    model->setDirect("speed");
    model->setDirect("measurements");
    model->setDirect("gust");
    model->setDirect("variableDirectionMin", "variable_direction_min");
    model->setDirect("variableDirectionMax", "variable_direction_max");
}

bool IqMeteoMetarWind::variableDirection() const
{
    return m_variableDirection;
}

void IqMeteoMetarWind::setVariableDirection(bool variableDirection)
{
    if (m_variableDirection != variableDirection) {
        m_variableDirection = variableDirection;
        emit variableDirectionChanged();
    }
}

int IqMeteoMetarWind::direction() const
{
    return m_direction;
}

void IqMeteoMetarWind::setDirection(int direction)
{
    if (m_direction != direction) {
        m_direction = direction;
        emit directionChanged();
    }
}

int IqMeteoMetarWind::speed() const
{
    return m_speed;
}

void IqMeteoMetarWind::setSpeed(int speed)
{
    if (m_speed != speed) {
        m_speed = speed;
        emit speedChanged();
    }
}

QString IqMeteoMetarWind::measurements() const
{
    return m_measurements;
}

void IqMeteoMetarWind::setMeasurements(const QString &measurements)
{
    if (m_measurements != measurements) {
        m_measurements = measurements;
        emit measurementsChanged();
    }
}

int IqMeteoMetarWind::gust() const
{
    return m_gust;
}

void IqMeteoMetarWind::setGust(int gust)
{
    if (m_gust != gust) {
        m_gust = gust;
        emit gustChanged();
    }
}

int IqMeteoMetarWind::variableDirectionMin() const
{
    return m_variableDirectionMin;
}

void IqMeteoMetarWind::setVariableDirectionMin(int variableDirectionMin)
{
    if (m_variableDirectionMin != variableDirectionMin) {
        m_variableDirectionMin = variableDirectionMin;
        emit variableDirectionMinChanged();
    }
}

int IqMeteoMetarWind::variableDirectionMax() const
{
    return m_variableDirectionMax;
}

void IqMeteoMetarWind::setVariableDirectionMax(int variableDirectionMax)
{
    if (m_variableDirectionMax != variableDirectionMax) {
        m_variableDirectionMax = variableDirectionMax;
        emit variableDirectionMaxChanged();
    }
}
