#define SETTINGS_LISTEN_PORT "listen_port"
#define SETTINGS_LISTEN_PORT_DEFAULT 20200

#define DATAGRAM_DELIMITER_START "ZCZC\r\n"
#define DATAGRAM_DELIMITER_END "\r\nNNNN"

#include "iqmeteoudplistener.h"
#include <QSettings>
#include "iqmeteo.h"
#include "iqmeteomessageparser.h"

IqMeteoUdpListener::IqMeteoUdpListener(QObject *parent) :
    QObject(parent),
    m_socket(new QUdpSocket(this))
{
    QSettings settings;

    quint16 port = settings.value(SETTINGS_LISTEN_PORT, SETTINGS_LISTEN_PORT_DEFAULT).toInt();
    m_socket->bind(port);

    connect(m_socket, &QUdpSocket::readyRead, this, &IqMeteoUdpListener::readPendingDatagrams);
}

void IqMeteoUdpListener::readPendingDatagrams()
{
    while (m_socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        m_socket->readDatagram(datagram.data(), datagram.size(),
                               &sender, &senderPort);

        m_datagram.append(datagram);
    }

    processDatagram();
}

void IqMeteoUdpListener::processDatagram()
{
    QByteArray message;
    int start = m_datagram.indexOf(DATAGRAM_DELIMITER_START);
    if (start == -1)
        m_datagram.clear();
    if (start != 0)
        m_datagram.remove(0, start);

    int datagramDelimiterStartLength = QString(DATAGRAM_DELIMITER_START).length();
    int datagramDelimiterEndLength = QString(DATAGRAM_DELIMITER_END).length();

    int end = m_datagram.indexOf(DATAGRAM_DELIMITER_END);

    while (end != -1) {
        message = m_datagram.mid(datagramDelimiterStartLength, end - datagramDelimiterEndLength);

        processMessage(message);
        m_datagram.remove(0, end + datagramDelimiterEndLength);

        end = m_datagram.indexOf(DATAGRAM_DELIMITER_END);
    }
}

void IqMeteoUdpListener::processMessage(const QByteArray &message)
{
    QString messageText(message);

    IqMeteo::Type messageType = static_cast<IqMeteo::Type>(messageText.left(2).toInt());

    int messageStart = messageText.indexOf("\r\n");
    if (messageStart == -1)
        return;
    messageText.remove(0, messageStart + 2);

    IqMeteoMessageParser::parserAndSave(messageType, messageText);
}
