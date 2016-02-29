#ifndef IQMETEOMAINWINDOW_H
#define IQMETEOMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class IqMeteoMainWindow;
}

class IqMeteoMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit IqMeteoMainWindow(QWidget *parent = 0);
    ~IqMeteoMainWindow();

private:
    Ui::IqMeteoMainWindow *ui;
};

#endif // IQMETEOMAINWINDOW_H
