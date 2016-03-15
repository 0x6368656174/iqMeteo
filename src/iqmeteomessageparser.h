#ifndef IQMETEOMESSAGEPARSER_H
#define IQMETEOMESSAGEPARSER_H

#include "iqmeteo.h"
#include <QObject>

class IqMeteoMessageParser
{
public:
    static void parserAndSave(IqMeteo::Type type, const QString &message);
};

#endif // IQMETEOMESSAGEPARSER_H
