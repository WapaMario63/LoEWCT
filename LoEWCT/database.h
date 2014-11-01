#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>

class Database
{
public:
    Database();

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    QString serverAddress = "localhost";
    QString dbUser;
    QString dbPass;
    QString dbName = "loewct_";

    void dbConx(QString address, QString dbuser, QString dbpass, QString dbname);
};

#endif // DATABASE_H
