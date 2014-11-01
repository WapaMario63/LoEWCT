#include "database.h"
#include "mainwindow.h"
#include "loewct.h"

Database::Database()
{
}

void Database::dbConx(QString address, QString dbuser, QString dbpass, QString dbname)
{
    serverAddress = address;
    dbUser = dbuser;
    dbPass = dbpass;
    dbName = dbname;

    QString dsn = QString("DRIVER={SQL Native Client};SERVER=%1;DATABASE=%2;UID=%3;PWD=%4;").arg(serverAddress).arg(dbname).arg(dbUser).arg(dbPass);

    db.setDatabaseName(dsn);

    if (db.open())
    {
        win.logMsg("[INFO] Opened database "+dbName+" succesfully!");
        db.close();
    }
    else
    {
        win.logMsg("[ERROR] Error opening database "+dbName+": \n"+ db.lastError().text() );
    }
}
