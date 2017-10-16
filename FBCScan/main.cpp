#include "analyzetraffic.h"
#include <QApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // database
    // create db connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("FBCTraffic");
    db.setUserName("root");
    db.setPassword("FBC_rootU5769");

    bool dbConnOpened = db.open();

    // widgets
    Analyzetraffic w;
    w.show();

    if(dbConnOpened) {
        qDebug() << "db connection opened!";
        db.close();
    } else {
        qDebug() << "ERROR = " << db.lastError().text();
    }

    return a.exec();
}
