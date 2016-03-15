#include "iqmeteomainwindow.h"
#include "ui_iqmeteomainwindow.h"

#include <IqOrmSqlDataSource>
#include <IqOrmCore>

IqMeteoMainWindow::IqMeteoMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IqMeteoMainWindow),
    m_listener(new IqMeteoUdpListener(this))
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("iq_meteo");
    db.setUserName("postgres");
    db.setPassword("rootpass");

    IqOrmSqlDataSource *dataSource = new IqOrmSqlDataSource();
    dataSource->setDatabase(db);

    IqOrmCore::setDataSource(dataSource);
}

IqMeteoMainWindow::~IqMeteoMainWindow()
{
    delete ui;
}
