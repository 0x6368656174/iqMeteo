#include <QApplication>

#include "iqmeteoapplication.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setOrganizationName("itQuasar");
    QApplication::setApplicationName("iqMeteoSerer");

    IqMeteoApplication application;

    return a.exec();
}
