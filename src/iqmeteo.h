#ifndef IQMETEO_H
#define IQMETEO_H


class IqMeteo
{
public:
    IqMeteo();

    enum Type {
        Airdrome = 03,
        Metar = 04,
        Ping = 10
    };
};

#endif // IQMETEO_H
