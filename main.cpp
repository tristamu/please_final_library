#include "mainwindow.h"
#include "database.h"
#include "persistentAttribute.h"
#include "persistentObject.h"
#include <QApplication>
#include <QtSql>
#include <QObject>
#include<iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.setWindowTitle("Information Table");
    w.show();


    return app.exec();
}
/*
int main( int argc, char **argv )
{
  QApplication app( argc, argv );

  QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );

  db.setDatabaseName( "/home/jerry/testdatabase.db" );

  if( !db.open() )
  {
    qDebug() << db.lastError();
    qFatal( "Failed to connect." );
  }

  qDebug( "Connected!" );

  QSqlQuery qry;

    qry.prepare( "CREATE TABLE IF NOT EXISTS names (id INTEGER UNIQUE PRIMARY KEY, firstname VARCHAR(30), lastname VARCHAR(30))" );
    if( !qry.exec() )
      qDebug() << qry.lastError();
    else
      qDebug() << "Table created!";

    qry.prepare( "INSERT INTO names (id, firstname, lastname) VALUES (1, 'John', 'Doe')" );
    if( !qry.exec() )
      qDebug() << qry.lastError();
    else
      qDebug( "Inserted!" );

    qry.prepare( "INSERT INTO names (id, firstname, lastname) VALUES (2, 'Jane', 'Doe')" );
    if( !qry.exec() )
      qDebug() << qry.lastError();
    else
      qDebug( "Inserted!" );

    qry.prepare( "INSERT INTO names (id, firstname, lastname) VALUES (3, 'James', 'Doe')" );
    if( !qry.exec() )
      qDebug() << qry.lastError();
    else
      qDebug( "Inserted!" );

    qry.prepare( "INSERT INTO names (id, firstname, lastname) VALUES (4, 'Judy', 'Doe')" );
    if( !qry.exec() )
      qDebug() << qry.lastError();
    else
      qDebug( "Inserted!" );

    qry.prepare( "INSERT INTO names (id, firstname, lastname) VALUES (5, 'Richard', 'Roe')" );
    if( !qry.exec() )
      qDebug() << qry.lastError();
    else
      qDebug( "Inserted!" );

    qry.prepare( "INSERT INTO names (id, firstname, lastname) VALUES (6, 'Jane', 'Roe')" );
    if( !qry.exec() )
      qDebug() << qry.lastError();
    else
      qDebug( "Inserted!" );

    qry.prepare( "INSERT INTO names (id, firstname, lastname) VALUES (7, 'John', 'Noakes')" );
    if( !qry.exec() )
      qDebug() << qry.lastError();
    else
      qDebug( "Inserted!" );

    qry.prepare( "INSERT INTO names (id, firstname, lastname) VALUES (8, 'Donna', 'Doe')" );
    if( !qry.exec() )
      qDebug() << qry.lastError();
    else
      qDebug( "Inserted!" );

    //selection
    qry.prepare( "SELECT * FROM names" );
    if( !qry.exec() )
      qDebug() << qry.lastError();
    else
    {
      qDebug( "Selected!" );

      QSqlRecord rec = qry.record();

      int cols = rec.count();

      for( int c=0; c<cols; c++ )
        qDebug() << QString( "Column %1: %2" ).arg( c ).arg( rec.fieldName(c) ); // print the header of the table

      for( int r=0; qry.next(); r++ )
        for( int c=0; c<cols; c++ )
          qDebug() << QString( "Row %1, %2: %3" ).arg( r ).arg( rec.fieldName(c) ).arg( qry.value(c).toString() );
    }

    db.close();

  return 0;//app.exec();;
}*/

