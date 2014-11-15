#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>
#include <QDir>
#include <QSqlQuery>
#include <QSqlRecord>
#include"persistentObject.h"
#include "persistentAttribute.h"

class DatabaseManager : public QObject
    {
    public:
        explicit DatabaseManager(QObject *parent = 0);
        ~DatabaseManager();
        QList<QString> totTable;
        QString path;

    public:
        void setNomBib(QString);
        void setNomTable(QString);
        bool openDB();
        bool readDB();
        bool createLibraryTable(QString);
        int saveBook(PersistentObject *);
        int insertRecord(QString , QString , QString , QString);
        bool deleteBook(QString);
        void closeDB();
        bool clearDB();
        QSqlError lastError();

    private:
        QSqlDatabase db;
        QString nomBib;
        QString nomTable;

    };

#endif // DATABASE_H

