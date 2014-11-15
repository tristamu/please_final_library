#include"database.h"
#include <QVariant>
#include <iostream>
#include <QDebug>

DatabaseManager::DatabaseManager(QObject *parent): QObject(parent){
    db = QSqlDatabase();
    nomBib = "hao";
    nomTable = "";
    path = "";
}

DatabaseManager::~DatabaseManager(){
    std::cout << "destructor of database\n";
}

void DatabaseManager::setNomBib(QString name){
    nomBib = name;
}

void DatabaseManager::setNomTable(QString name){
    nomTable = name;
}

bool DatabaseManager::openDB(){
    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");//driver sqlite

    #ifdef Q_OS_LINUX
    // NOTE: We have to store database file into user home folder in Linux
    QString path(QDir::home().path());
    path.append(QDir::separator()).append("hao.db");//("my.db.sqlite");
    path = QDir::toNativeSeparators(path);
    db.setDatabaseName(path);
    #else
    // NOTE: File exists in the application private folder, in Symbian Qt implementation
    if(path == NULL ) // save
        db.setDatabaseName(nomBib+".db");
    else {// save as
        db.setDatabaseName(path);
        path = "";
    }
    //qDebug() << path.path();
    #endif

    // Open databasee
    bool ouvrir = db.open();
    if( !ouvrir )
    {
      qDebug() << db.lastError();
      qFatal( "Failed to connect." );
    }

    qDebug( "Connected!" );
    return ouvrir;
}

bool DatabaseManager::readDB(){
    bool ret = false;
    QSqlQuery qry;

    //selection
    //qry.exec("ATTACH "+ nomBib + ".db AS my_db");
    //ret = qry.exec("SELECT name FROM my_db.sqlite_master WHERE type='table'");

    ret = qry.exec( "SELECT * FROM haohao" );
    /*if( !ret )
      qDebug() << qry.lastError();
    else
    {
      qDebug() << "Selected!";

      QSqlRecord rec = qry.record();

      int cols = rec.count();

      for( int c=0; c<cols; c++ )
        qDebug() << QString( "Column %1: %2" ).arg( c ).arg( rec.fieldName(c) ); // print the header of the table

      for( int r=0; qry.next(); r++ )
        for( int c=0; c<cols; c++ )
          qDebug() << QString( "Row %1, %2: %3" ).arg( r ).arg( rec.fieldName(c) ).arg( qry.value(c).toString() );
    }*/
    return ret;
}

bool DatabaseManager::createLibraryTable(QString nameTable){
    // Create table "library"
    bool ret = false;
    QSqlQuery query;
    if (db.isOpen()){
        ret = query.exec("CREATE TABLE IF NOT EXISTS "+nameTable+
                  "(author varchar(20), "
                  "title varchar(20), "
                  "isbn varchar(20) primary key, " /*this is an autoincrement field*/
                  "year varchar(20))");
}
    if( !ret )
      qDebug() << query.lastError();
    else
      qDebug() << "Table created!";
    return ret;
}

int DatabaseManager::insertRecord(QString author, QString title, QString isbn, QString year){
    int newId = -1;
    bool ret = false;

    if (db.isOpen()){
        //http://www.sqlite.org/autoinc.html
        // NULL = is the keyword for the autoincrement to generate next value

        QSqlQuery query;
        ret = query.exec(QString("INSERT INTO " +nomTable+ " VALUES('%1','%2','%3','%4')")
        .arg(author).arg(title).arg(isbn).arg(year));

        // Get database given autoincrement value
        if (ret){
            // http://www.sqlite.org/c3ref/last_insert_rowid.html
            newId = query.lastInsertId().toInt();
            qDebug( "Inserted!" );
        }else
            qDebug() << query.lastError();

    }
    return newId;
}

bool DatabaseManager::deleteBook(QString isbn){
    bool ret = false;
    if (db.isOpen()){
        QSqlQuery query;
        ret = query.exec(QString("DELETE FROM " + nomTable + " WHERE isbn='%1'").arg(isbn));

        if (ret)
            qDebug( "Deleted!" );
        else
            qDebug() << query.lastError();
    }
    return ret;
}

bool DatabaseManager::clearDB(){
    bool ret = false;
    if (db.isOpen()){
        QSqlQuery query;
        int size = totTable.size();
        for(int i =0;i<size;i++)
            ret = query.exec(QString("DROP TABLE ")+totTable.at(i));
        if (ret)
            qDebug( "Cleared!" );
        else
            qDebug() << query.lastError();
    }
    return ret;
}



int DatabaseManager::saveBook(PersistentObject *theBook){

   // if(BookObjec) is the right table
    insertRecord(theBook->getIndexAttribut(0)->variable.toString(),
                 theBook->getIndexAttribut(1)->variable.toString(),
                 theBook->getIndexAttribut(2)->variable.toString(),
                 theBook->getIndexAttribut(3)->variable.toString());
    return 0;
}

QSqlError DatabaseManager::lastError(){
    // If opening database has failed user can ask
    // error description by QSqlError::text()
    return db.lastError();
}

void DatabaseManager::closeDB(){
    // Close database
    QString connection;
    connection=db.connectionName();
    db.close();
    QSqlDatabase::removeDatabase(connection);
    qDebug() << "Closed " << connection;
    /*#ifdef Q_OS_LINUX
    // NOTE: We have to store database file into user home folder in Linux
    QString path(QDir::home().path());
    path.append(QDir::separator()).append("hao.db");
    path = QDir::toNativeSeparators(path);
    //return QFile::remove(path);
    #else

    // Remove created database binary file
    QFile::remove(nomTable+".db");
    #endif*/
}
