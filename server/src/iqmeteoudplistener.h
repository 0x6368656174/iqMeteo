#ifndef IQMETEOUDPLISTENER_H
#define IQMETEOUDPLISTENER_H

#include <QObject>
#include <QUdpSocket>
#include "entity/iqmeteometar.h"

class IqMeteoUdpListener : public QObject
{
    Q_OBJECT
public:
    explicit IqMeteoUdpListener(QObject *parent = 0);

signals:
    void metarReserved(const QSharedPointer<IqMeteoMetar> &metar);

private:
    QUdpSocket *m_socket;
    QByteArray m_datagram;

private:
    void readPendingDatagrams();
    void processDatagram();
    void processMessage(const QString &message);
    QString m_codepage;
};

#endif // IQMETEOUDPLISTENER_H
