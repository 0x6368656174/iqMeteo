#ifndef IQMETEOMETARPARSER_H
#define IQMETEOMETARPARSER_H

#include "entity/iqmeteometar.h"

class IqMeteoMetarParser
{
public:
    void parseAndSave(IqMeteoMetar *metar, const QString &message);

private:
    void parseSpeed(IqMeteoMetar *metar, const QString &message);
    void parseAirdrome(IqMeteoMetar *metar, const QString &message);
    void parseTemperature(IqMeteoMetar *metar, const QString &message);
    void parseObservationDateTime(IqMeteoMetar *metar, const QString &message);
    void parseQnh(IqMeteoMetar *metar, const QString &message);
    void parserPrevailingVisibility(IqMeteoMetar *metar, const QString &message);
};

#endif // IQMETEOMETARPARSER_H
