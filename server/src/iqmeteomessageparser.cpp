#include "iqmeteomessageparser.h"
#include "entity/iqmeteometar.h"
#include "iqmeteometarparser.h"

QSharedPointer<IqMeteoAbstractMessage> IqMeteoMessageParser::parserAndSave(IqMeteo::Type type, const QString &message)
{
    switch (type) {
    case IqMeteo::Type::Metar:
        QSharedPointer<IqMeteoMetar> metar (new IqMeteoMetar);

        IqMeteoMetarParser parser;
        parser.parseAndSave(metar.data(), message);

        return metar;
    }

    return QSharedPointer<IqMeteoAbstractMessage>();
}
