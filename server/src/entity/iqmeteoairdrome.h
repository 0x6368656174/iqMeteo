#ifndef IQMETEOAIRDROME_H
#define IQMETEOAIRDROME_H

#include <QObject>
#include <IqOrmObject>

class IqMeteoAirdrome: public QObject, public IqOrmObject
{
    Q_OBJECT
    IQORM_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString icaoCode READ icaoCode WRITE setIcaoCode NOTIFY icaoCodeChanged)
public:
    explicit IqMeteoAirdrome(QObject *parent = 0);

public:
    virtual void initializeOrmMetaModel(IqOrmMetaModel *model) const override;

    QString name() const;
    void setName(const QString &name);

    QString icaoCode() const;
    void setIcaoCode(const QString &icaoCode);

signals:
    void nameChanged();
    void icaoCodeChanged();

private:
    QString m_name;
    QString m_icaoCode;
};

IQORM_REGISTER_CLASS(IqMeteoAirdrome)

#endif // IQMETEOAIRDROME_H
