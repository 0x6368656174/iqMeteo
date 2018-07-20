#include "iqmeteoguimainwindow.h"
#include "ui_iqmeteoguimainwindow.h"
#include <QDebug>

IqMeteoGuiMainWindow::IqMeteoGuiMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IqMeteoGuiMainWindow),
    m_wampClient(new IqWampClient(this)),
    m_model(new IqMeteoGuiMainModel(this))
{
    ui->setupUi(this);

    ui->airdromesListView->setModel(m_model);

    connect(m_wampClient, &IqWampClient::opened, this, [this]() {
        m_wampClient->subscribe("ru.itquasar.meteo.metar", this, &IqMeteoGuiMainWindow::addMetar);

        m_wampClient->call("ru.itquasar.meteo.airdrome.list", this, &IqMeteoGuiMainWindow::setAirdromes, &IqMeteoGuiMainWindow::onError);
    });

    m_wampClient->open("ws://localhost:12000", "main");
}

IqMeteoGuiMainWindow::~IqMeteoGuiMainWindow()
{
    delete ui;
}

void IqMeteoGuiMainWindow::addMetar(const QJsonObject &metar)
{
    QSharedPointer<IqMeteoGuiAirdrome> airdrome = m_model->airdrome(metar.value("airdromeId").toInt(-1));

    if (!airdrome) {
        qWarning() << "Not found airdrome for metar" << metar;
        return;
    }

    airdrome->setMetarFromJson(metar);
}

void IqMeteoGuiMainWindow::setAirdromes(const QJsonArray &airdromes)
{
    m_model->setAirdromesFromJson(airdromes);
    m_wampClient->call("ru.itquasar.meteo.metar.list", this, &IqMeteoGuiMainWindow::setMetars, &IqMeteoGuiMainWindow::onError);
}

void IqMeteoGuiMainWindow::onError(const IqWampCallError &error)
{
    qDebug() << error.error();
}

void IqMeteoGuiMainWindow::setMetars(const QJsonArray &metars)
{
    for(QJsonValue metar: metars) {
        addMetar(metar.toObject());
    }
}
