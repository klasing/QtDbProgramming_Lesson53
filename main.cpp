#include <QCoreApplication>
#include <QtSql>
#include <QDebug>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString serverName = "(localdb)\\Projects";
    QString dbName = "test";

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setConnectOptions();

    QString dsn = QString("Driver={SQL Server Native Client 11.0};Server=%1;Database=%2;Uid=odbc;Pwd=odbc;").arg(serverName).arg(dbName);
    db.setDatabaseName(dsn);

    if (db.open()) {
        qDebug() << "Opened!";
        // create a query to insert values into a table, with the use of variable binding
        QString sQuery = "INSERT INTO [test].[dbo].[people] ([ID], [FirstName], [LastName]) VALUES (:id, :firstName, :lastName)";
        QSqlQuery qry;
        qry.prepare(sQuery);
        // bind variables with values
        qry.bindValue(":id", 2); // id is primary key, so this query will run only once
        qry.bindValue(":firstName", "Arjan");
        qry.bindValue(":lastName", "Schippers");
        // execute the query
        if (qry.exec()) {
            qDebug() << "record inserted";
        } else {
           qDebug() << "Error: " << db.lastError().text();
        }
        qDebug() << "Closing...";
        db.close();
    } else {
        qDebug() << "Error: " << db.lastError().text();
    }

    return a.exec();
}
