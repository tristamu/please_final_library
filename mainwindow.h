#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QInputDialog>
#include <QTableWidget>
#include <QStringList>
#include <QFileDialog>
#include "persistentAttribute.h"
#include "persistentObject.h"
#include "database.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int ligne, colonne;
    int indice, flag, nombreTableEcrit;
    QString nomFichier;

    DatabaseManager * database;
    PersistentObject * book;
    QList<QTableWidget*> *tableau;


    PersistentObject * readLineTable(int, int);
    int askToLeaveEditedTable();
    void deleteATable(int);

private slots:
    void nouvelleBib();
    void fermer();
    int enregistrement();
    int enregistreSous();
    int ouvertureBib();
    //void on_tableWidget_itemChanged(QTableWidgetItem *item);
    void on_pushButton_clicked();
    //void on_tableWidget_cellClicked(int row, int column);
    void updateCoordinate(int row, int column);
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_deleteTable_clicked();

signals:
    void rowChanged(int row);
};

#endif // MAINWINDOW_H
