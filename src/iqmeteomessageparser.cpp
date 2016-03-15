#include "iqmeteomessageparser.h"
#include "entity/iqmeteometar.h"
#include "iqmeteometarparser.h"

void IqMeteoMessageParser::parserAndSave(IqMeteo::Type type, const QString &message)
{
    switch (type) {
    case IqMeteo::Metar:
        IqMeteoMetar metar;

        IqMeteoMetarParser parser;
        parser.parseAndSave(&metar, message);
        break;
    }
}
