#define SETTINGS_METEO_LISTENER_GROUP "listener"
#define SETTINGS_METEO_LISTENER_CODEPAGE "codepage"
#define SETTINGS_METEO_LISTENER_PORT "listen_port"

#define DATAGRAM_DELIMITER_START "ZCZC\r\n"
#define DATAGRAM_DELIMITER_END "\r\nNNNN"

#include "iqmeteoudplistener.h"
#include <QSettings>
#include <QTextCodec>
#include "iqmeteo.h"
#include "iqmeteomessageparser.h"

IqMeteoUdpListener::IqMeteoUdpListener(QObject *parent) :
    QObject(parent),
    m_socket(new QUdpSocket(this))
{
    QSettings settings;

    settings.beginGroup(SETTINGS_METEO_LISTENER_GROUP);

    if (!settings.contains(SETTINGS_METEO_LISTENER_PORT))
        settings.setValue(SETTINGS_METEO_LISTENER_PORT, 20200);
    if (!settings.contains(SETTINGS_METEO_LISTENER_CODEPAGE))
        settings.setValue(SETTINGS_METEO_LISTENER_CODEPAGE, "IBM 866");

    quint16 port = static_cast<quint16>(settings.value(SETTINGS_METEO_LISTENER_PORT).toInt());
    m_codepage = settings.value(SETTINGS_METEO_LISTENER_CODEPAGE).toString();

    settings.endGroup();

    m_socket->bind(port);

    connect(m_socket, &QUdpSocket::readyRead, this, &IqMeteoUdpListener::readPendingDatagrams);
}

void IqMeteoUdpListener::readPendingDatagrams()
{
    while (m_socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(static_cast<int>(m_socket->pendingDatagramSize()));
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

        QTextCodec *codec = QTextCodec::codecForName(m_codepage.toLocal8Bit());
        QString textMessage = codec->toUnicode(message);

        processMessage(textMessage);
        m_datagram.remove(0, end + datagramDelimiterEndLength);

        end = m_datagram.indexOf(DATAGRAM_DELIMITER_END);
    }
}

void IqMeteoUdpListener::processMessage(const QString &message)
{
    QString messageText = message;

    IqMeteo::Type messageType = static_cast<IqMeteo::Type>(messageText.left(2).toInt());

    int messageStart = messageText.indexOf("\r\n");
    if (messageStart == -1)
        return;
    messageText.remove(0, messageStart + 2);

    const QSharedPointer<IqMeteoAbstractMessage> newMessage = IqMeteoMessageParser::parserAndSave(messageType, messageText);
    if (newMessage) {
        switch (newMessage->type()) {
        case IqMeteo::Type::Metar: {
            emit metarReserved(qSharedPointerCast<IqMeteoMetar>(newMessage));
        } break;
        }
    }
}
