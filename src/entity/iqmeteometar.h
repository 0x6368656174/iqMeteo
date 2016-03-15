#ifndef IQMETEOMETAR_H
#define IQMETEOMETAR_H

#include <QObject>
#include <IqOrmObject>
#include <QDateTime>
#include <IqOrmSharedLazyPointer>
#include "iqmeteometarwind.h"
#include "iqmeteoairdrome.h"
#include "iqmeteopreveilingvisibility.h"

class IqMeteoMetar : public QObject, public IqOrmObject
{
    Q_OBJECT
    IQORM_OBJECT

    Q_PROPERTY(QString sourceText READ sourceText WRITE setSourceText NOTIFY sourceTextChanged)
    Q_PROPERTY(QDateTime observationDateTime READ observationDateTime WRITE setObservationDateTime NOTIFY observationDateTimeChanged)
    Q_PROPERTY(int temperature READ temperature WRITE setTemperature NOTIFY temperatureChanged)
    Q_PROPERTY(int dewPoint READ dewPoint WRITE setDewPoint NOTIFY dewPointChanged)
    Q_PROPERTY(int qnh READ qnh WRITE setQnh NOTIFY qnhChanged)
    Q_PROPERTY(QString sourceText READ sourceText WRITE setSourceText NOTIFY sourceTextChanged)

    Q_PROPERTY(IqOrmSharedLazyPointer<IqMeteoMetarWind> wind READ wind WRITE setWind NOTIFY windChanged)
    Q_PROPERTY(IqOrmSharedLazyPointer<IqMeteoAirdrome> airdrome READ airdrome WRITE setAirdrome NOTIFY airdromeChanged)
    Q_PROPERTY(IqOrmSharedLazyPointer<IqMeteoPrevailingVisibility> prevailingVisibility READ prevailingVisibility WRITE setPrevailingVisibility NOTIFY prevailingVisibilityChanged)
public:
    explicit IqMeteoMetar(QObject *parent = 0);

public:
    virtual void initializeOrmMetaModel(IqOrmMetaModel *model) const override;

    QDateTime observationDateTime() const;
    void setObservationDateTime(const QDateTime &observationDateTime);

    int temperature() const;
    void setTemperature(int temperature);

    int dewPoint() const;
    void setDewPoint(int dewPoint);

    int qnh() const;
    void setQnh(int qnh);

    QString sourceText() const;
    void setSourceText(const QString &sourceText);

    IqOrmSharedLazyPointer<IqMeteoMetarWind> wind() const;
    void setWind(const IqOrmSharedLazyPointer<IqMeteoMetarWind> &wind);

    IqOrmSharedLazyPointer<IqMeteoAirdrome> airdrome() const;
    void setAirdrome(const IqOrmSharedLazyPointer<IqMeteoAirdrome> &airdrome);

    IqOrmSharedLazyPointer<IqMeteoPrevailingVisibility> prevailingVisibility() const;
    void setPrevailingVisibility(const IqOrmSharedLazyPointer<IqMeteoPrevailingVisibility> &prevailingVisibility);

signals:
    void observationDateTimeChanged();
    void temperatureChanged();
    void dewPointChanged();
    void qnhChanged();
    void sourceTextChanged();
    void windChanged();
    void airdromeChanged();
    void prevailingVisibilityChanged();

private:
    QDateTime m_observationDateTime;
    int m_temperature;
    int m_dewPoint;
    int m_qnh;
    QString m_sourceText;

    IqOrmSharedLazyPointer<IqMeteoMetarWind> m_wind;
    IqOrmSharedLazyPointer<IqMeteoAirdrome> m_airdrome;
    IqOrmSharedLazyPointer<IqMeteoPrevailingVisibility> m_prevailingVisibility;
};

IQORM_REGISTER_CLASS(IqMeteoMetar)

#endif // IQMETEOMETAR_H
