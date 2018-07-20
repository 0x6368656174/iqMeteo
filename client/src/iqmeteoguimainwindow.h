#ifndef IQMETEOGUIMAINWINDOW_H
#define IQMETEOGUIMAINWINDOW_H

#include <QMainWindow>
#include <IqWampClient>
#include "iqmeteoguimainmodel.h"

namespace Ui {
class IqMeteoGuiMainWindow;
}

class IqMeteoGuiMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit IqMeteoGuiMainWindow(QWidget *parent = 0);
    ~IqMeteoGuiMainWindow();

private:
    void addMetar(const QJsonObject &metar);
    void setMetars(const QJsonArray &metars);
    void setAirdromes(const QJsonArray &airdromes);
    void onError(const IqWampCallError &error);

private:
    Ui::IqMeteoGuiMainWindow *ui;

    IqWampClient *m_wampClient;
    IqMeteoGuiMainModel *m_model;
};

#endif // IQMETEOGUIMAINWINDOW_H
