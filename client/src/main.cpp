#include "iqmeteoguimainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IqMeteoGuiMainWindow w;
    w.show();

    return a.exec();
}
