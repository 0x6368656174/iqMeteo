#include "iqmeteomainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IqMeteoMainWindow w;
    w.show();

    return a.exec();
}
