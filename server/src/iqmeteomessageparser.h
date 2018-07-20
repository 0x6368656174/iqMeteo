#ifndef IQMETEOMESSAGEPARSER_H
#define IQMETEOMESSAGEPARSER_H

#include "iqmeteo.h"
#include <QObject>
#include <QSharedPointer>
#include "entity/iqmeteoabstractmessage.h"

class IqMeteoMessageParser
{
public:
    static QSharedPointer<IqMeteoAbstractMessage> parserAndSave(IqMeteo::Type type, const QString &message);
};

#endif // IQMETEOMESSAGEPARSER_H
