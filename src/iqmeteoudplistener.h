#ifndef IQMETEOUDPLISTENER_H
#define IQMETEOUDPLISTENER_H

#include <QObject>
#include <QUdpSocket>

class IqMeteoUdpListener : public QObject
{
    Q_OBJECT
public:
    explicit IqMeteoUdpListener(QObject *parent = 0);

private:
    QUdpSocket *m_socket;
    QByteArray m_datagram;

private:
    void readPendingDatagrams();
    void processDatagram();
    void processMessage(const QByteArray &message);
};

#endif // IQMETEOUDPLISTENER_H
