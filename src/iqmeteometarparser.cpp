#include "iqmeteometarparser.h"
#include <IqOrmModel>
#include <src/entity/iqmeteorunwayvisibility.h>

void IqMeteoMetarParser::parseTemperature(IqMeteoMetar *metar, const QString &message)
{
    QRegExp temperatureRx("\\s(M{0,1})(\\d{2})\\/(M{0,1})(\\d{2})\\s");

    if (temperatureRx.indexIn(message) != -1) {
        int temp = temperatureRx.cap(2).toInt();
        if (!temperatureRx.cap(1).isEmpty())
            temp = -1* temp;
        metar->setTemperature(temp);

        int dewPoint = temperatureRx.cap(4).toInt();
        if (!temperatureRx.cap(3).isEmpty())
            dewPoint = -1 * dewPoint;
        metar->setDewPoint(dewPoint);
    }
}

void IqMeteoMetarParser::parseAndSave(IqMeteoMetar *metar, const QString &message)
{
    Q_CHECK_PTR(metar);
    if (metar == Q_NULLPTR)
        return;

    metar->setSourceText(message);

    parseSpeed(metar, message);
    parseAirdrome(metar, message);
    parseTemperature(metar, message);
    parseObservationDateTime(metar, message);
    parseQnh(metar, message);
    parserPrevailingVisibility(metar, message);

    metar->wind()->save();
    metar->prevailingVisibility()->save();
    metar->save();
}

void IqMeteoMetarParser::parseSpeed(IqMeteoMetar *metar, const QString &message)
{
    QRegExp speedRx("\\s((VRB)|(\\d{3}))(\\d{2})(G(\\d{2})){0,1}((MPS)|(KT)|(KMH))(\\s+(\\d{3})V(\\d{3})){0,1}\\s");

    if (speedRx.indexIn(message) != -1) {
        if (!speedRx.cap(2).isEmpty())
            metar->wind()->setVariableDirection(true);
        else
            metar->wind()->setDirection(speedRx.cap(3).toInt());

        metar->wind()->setSpeed(speedRx.cap(4).toInt());

        if (!speedRx.cap(5).isEmpty())
            metar->wind()->setSpeed(speedRx.cap(6).toInt());

        metar->wind()->setMeasurements(speedRx.cap(7));

        if (!speedRx.cap(11).isEmpty()) {
            metar->wind()->setVariableDirectionMin(speedRx.cap(12).toInt());
            metar->wind()->setVariableDirectionMax(speedRx.cap(13).toInt());
        }
    }
}

void IqMeteoMetarParser::parseAirdrome(IqMeteoMetar *metar, const QString &message)
{
    QRegExp airdromeRx("\\s(\\w{4})\\s+\\d{6}Z\\s");

    if (airdromeRx.indexIn(message) != -1) {
        QString icaoCode = airdromeRx.cap(1);

        IqOrmModel<IqMeteoAirdrome> model;
        model.find("icaoCode", IqOrmFilter::Equals, icaoCode);


        if (!model.isEmpty()) {
            IqOrmSharedLazyPointer<IqMeteoAirdrome> airdrome (model.takeFirst());
            metar->setAirdrome(airdrome);
        }
    }
}

void IqMeteoMetarParser::parseObservationDateTime(IqMeteoMetar *metar, const QString &message)
{
    QRegExp observationDateTimeRx("\\s\\w{4}\\s+(\\d{6})Z\\s");

    if (observationDateTimeRx.indexIn(message) != -1) {
        QDateTime observationDateTime = QDateTime::fromString(observationDateTimeRx.cap(1), "ddhhmm");

        QDate currentDate = QDate::currentDate();
        QDate observationDate = observationDateTime.date();
        observationDate.setDate(currentDate.year(), currentDate.month(), observationDate.day());
        observationDateTime.setDate(observationDate);

        metar->setObservationDateTime(observationDateTime);
    }
}

void IqMeteoMetarParser::parseQnh(IqMeteoMetar *metar, const QString &message)
{
    QRegExp qnhRx("\\sQ(\\d{4})\\s");

    if (qnhRx.indexIn(message) != -1) {
        metar->setQnh(qnhRx.cap(1).toInt());
    }
}

void IqMeteoMetarParser::parserPrevailingVisibility(IqMeteoMetar *metar, const QString &message)
{
    QRegExp prevailingVisibilityRx("\\s(\\d{4})(\\w{2})?(\\s+(\\d{4})(\\w{2})?)?((\\s+R\\d{1,3}[LCR]?\\/[PM]?\\d{4}(V[PM]?\\d{4})?[UD]?)*)\\s");

    if (prevailingVisibilityRx.indexIn(message) != -1) {
        if (prevailingVisibilityRx.cap(2).isEmpty()) {
            metar->prevailingVisibility()->setAverage(prevailingVisibilityRx.cap(1).toInt());
        } else {
            metar->prevailingVisibility()->setMin(prevailingVisibilityRx.cap(1).toInt());
            metar->prevailingVisibility()->setMinDirection(prevailingVisibilityRx.cap(2));
        }

        if (!prevailingVisibilityRx.cap(3).isEmpty()) {
            metar->prevailingVisibility()->setMax(prevailingVisibilityRx.cap(4).toInt());
            metar->prevailingVisibility()->setMaxDirection(prevailingVisibilityRx.cap(5));
        }

        if (!prevailingVisibilityRx.cap(6).isEmpty()) {
            QString runwaysString = prevailingVisibilityRx.cap(6);

            qDebug() << "/n" << "Found runways" << runwaysString << "/n";

            QRegExp runwayRx("(R\\d{1,3}[LCR]?)\\/(([MP]?)(\\d{4}))(V([MP]?)(\\d{4}))?(U|D|N)?");

            IqOrmSharedLazyPointerSet<IqMeteoRunwayVisibility> runwayVisibilities;

            int lastIndex = runwayRx.indexIn(runwaysString);
            while (lastIndex != -1) {
                IqOrmSharedLazyPointer<IqMeteoRunwayVisibility> runwayVisibility (new IqMeteoRunwayVisibility());
                runwayVisibility->setRunwayName(runwayRx.cap(1));

                if (runwayRx.cap(5).isEmpty()) {
                    if (runwayRx.cap(3).isEmpty())
                        runwayVisibility->setAverage(runwayRx.cap(4).toInt());
                    else if (runwayRx.cap(3) == "P")
                        runwayVisibility->setAverage(9999);
                    else
                        runwayVisibility->setAverage(1);
                } else {
                    if (runwayRx.cap(3).isEmpty())
                        runwayVisibility->setMin(runwayRx.cap(4).toInt());
                    else if (runwayRx.cap(3) == "P")
                        runwayVisibility->setMin(9999);
                    else
                        runwayVisibility->setMin(1);

                    if (runwayRx.cap(6).isEmpty())
                        runwayVisibility->setMax(runwayRx.cap(7).toInt());
                    else if (runwayRx.cap(6) == "P")
                        runwayVisibility->setMax(9999);
                    else
                        runwayVisibility->setMax(1);
                }

                if (!runwayRx.cap(8).isEmpty())
                    runwayVisibility->setTendency(runwayRx.cap(8));

                runwayVisibilities << runwayVisibility;

                lastIndex = runwayRx.indexIn(runwaysString, lastIndex + runwayRx.matchedLength());
            }

            metar->prevailingVisibility()->setRunwayVisibilities(runwayVisibilities);
        }
    }

}

