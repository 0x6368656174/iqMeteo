#include "iqmeteomainwindow.h"
#include "ui_iqmeteomainwindow.h"

IqMeteoMainWindow::IqMeteoMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IqMeteoMainWindow)
{
    ui->setupUi(this);
}

IqMeteoMainWindow::~IqMeteoMainWindow()
{
    delete ui;
}
