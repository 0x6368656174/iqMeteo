#ifndef IQMETEOMETARWIND_H
#define IQMETEOMETARWIND_H

#include <QObject>
#include <IqOrmObject>

class IqMeteoMetarWind : public QObject, public IqOrmObject
{
    Q_OBJECT
    IQORM_OBJECT

    Q_PROPERTY(bool variableDirection READ variableDirection WRITE setVariableDirection NOTIFY variableDirectionChanged)
    Q_PROPERTY(int direction READ direction WRITE setDirection NOTIFY directionChanged)
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(QString measurements READ measurements WRITE setMeasurements NOTIFY measurementsChanged)
    Q_PROPERTY(int gust READ gust WRITE setGust NOTIFY gustChanged)
    Q_PROPERTY(int variableDirectionMin READ variableDirectionMin WRITE setVariableDirectionMin NOTIFY variableDirectionMinChanged)
    Q_PROPERTY(int variableDirectionMax READ variableDirectionMax WRITE setVariableDirectionMax NOTIFY variableDirectionMaxChanged)
public:
    explicit IqMeteoMetarWind(QObject *parent = 0);

public:
    virtual void initializeOrmMetaModel(IqOrmMetaModel *model) const override ;

    bool variableDirection() const;
    void setVariableDirection(bool variableDirection);

    int direction() const;
    void setDirection(int direction);

    int speed() const;
    void setSpeed(int speed);

    QString measurements() const;
    void setMeasurements(const QString &measurements);

    int gust() const;
    void setGust(int gust);

    int variableDirectionMin() const;
    void setVariableDirectionMin(int variableDirectionMin);

    int variableDirectionMax() const;
    void setVariableDirectionMax(int variableDirectionMax);

signals:
    void variableDirectionChanged();
    void directionChanged();
    void speedChanged();
    void measurementsChanged();
    void gustChanged();
    void variableDirectionMinChanged();
    void variableDirectionMaxChanged();

private:
    bool m_variableDirection;
    int m_direction;
    int m_speed;
    QString m_measurements;
    int m_gust;
    int m_variableDirectionMin;
    int m_variableDirectionMax;
};

IQORM_REGISTER_CLASS(IqMeteoMetarWind)

#endif // IQMETEOMETARWIND_H
