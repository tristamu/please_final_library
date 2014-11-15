#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ligne = -1; // to add a row in a blank table
    colonne = 0;
    indice = 0; // index of the table activated
    nombreTableEcrit = 0;
    nomFichier = "";

    flag = 0; // indicate whether we have to insert an new element to the table or not
    book = new PersistentObject();
    database = new DatabaseManager();
    tableau = new QList<QTableWidget*>();
    ui->setupUi(this);
    ui->menuBar->show();
    ui->pushButton_3->setEnabled(false);
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(nouvelleBib()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(fermer()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(enregistrement()));
    connect(ui->actionSave_as, SIGNAL(triggered()), this, SLOT(enregistreSous()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(ouvertureBib()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete book;
    delete database;
    delete [] tableau;
}

int MainWindow::askToLeaveEditedTable()
{
    QMessageBox msgBox;

    msgBox.setText("Abandon current table ?");
    msgBox.setInformativeText("You might as well choose to save your current information");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Save);
    msgBox.setDefaultButton(QMessageBox::Yes);

    int ret = msgBox.exec();
    qDebug()<<ret;


    switch (ret)
    {
      case QMessageBox::Save:
          qDebug()<<"Save was clicked";
          return 2;
      case QMessageBox::Yes:
          qDebug()<<"Don't Save was clicked";
          return 0;
      case QMessageBox::No:
           qDebug()<<"Cancel was clicked";
          // Cancel was clicked
          return 1;
      default:
          // should never be reached
          break;
          return -1;
    }

}



void MainWindow::nouvelleBib()
{
    bool ok;

    QString text;
    if(tableau->empty()== true)
    {
        text = QInputDialog::getText(this, tr("Library creation"),tr("Library name:"), QLineEdit::Normal,"", &ok);
        database->setNomBib(text);
        ui->pushButton_3->setEnabled(true);
        nomFichier="D:\\"+text+".db";
        ui->textEdit->setText(nomFichier);
        database->path=nomFichier;

     }else{

        int continueChoice=askToLeaveEditedTable();


        if(continueChoice ==0 )
        {

            int nb_table = tableau->size();
            qDebug()<<"nouvelleBib table size is "+nb_table;
            for(int i=0;i<nb_table;i++)
            {
                tableau->at(i)->hide();

            }
            tableau->clear();
            ui->comboBox->clear();



            text = QInputDialog::getText(this, tr("Library creation"),tr("Library name:"), QLineEdit::Normal,"", &ok);
            database->setNomBib(text);
            ui->pushButton_3->setEnabled(true);
            nomFichier="D:\\"+text+".db";
            database->path=nomFichier;
            ui->textEdit->setText(nomFichier);
         }else if(continueChoice == 1)
         {
             qDebug()<<"No was clicked";

         }else if(continueChoice == 2)
         {
            enregistrement();

         }




    }






}




void MainWindow::fermer(){
    if(ui->comboBox->count() == 0)
        ui->pushButton_3->setEnabled(false);
    tableau->at(indice)->hide();
    database->closeDB();
}
int MainWindow::enregistrement(){

    int nb = tableau->size();
    std::cout<<"enregistrement table size is "<<nb;
    if (nb == 0)
        return 0;

    //cas tableau non vide
    if(flag == 0)
        database->openDB();
    //creation of new tables
    while(nb > nombreTableEcrit){
        QString name = ui->comboBox->itemText(nombreTableEcrit);
        database->createLibraryTable(name);
        nombreTableEcrit++;
    }
    if(flag == 0){ // if there are new rows
        flag = 1; // lose its virginity
        for(int i =0; i< nb; i++){ //parcourir tous les tables
            database->setNomTable(ui->comboBox->itemText(i));
            int rowCnt = tableau->at(i)->rowCount();
            for(int j = 0;j < rowCnt;j++){
                book = readLineTable(i,j);
                database->saveBook(book);
            }
        }
    }else{
        database->clearDB();
        //creation of new tables
        nombreTableEcrit = 0;
        while(nb > nombreTableEcrit){
            QString name = ui->comboBox->itemText(nombreTableEcrit);
            database->createLibraryTable(name);
            nombreTableEcrit++;
        }
        for(int i =0; i< nb; i++){ //parcourir tous les tables
            database->setNomTable(ui->comboBox->itemText(i));
            int rowCnt = tableau->at(i)->rowCount();
            for(int j = 0;j < rowCnt;j++){
                book = readLineTable(i,j);
                database->saveBook(book);
            }
        }
    }
    return 0;
}

int MainWindow::enregistreSous()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Save File"),QString(),
                                           tr("Database files(*.db);;Text Files (*.txt);;C++ Files (*.cpp *.h)") );
    QFile file(fileName);
    if(!fileName.isEmpty())
    {
        if(!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::critical(this,tr("Error"),tr("Could not write into this file"));
            return 0;
        }
    }
    qDebug()<<"filename: "<<fileName;
    //QString nomTmp = QDir(fileName).dirName(); // nom.db
    //database->setNomBib(nomTmp.left(nomTmp.length()-3));

    nomFichier = QDir::toNativeSeparators(fileName);
    ui->textEdit->setText(nomFichier);
    database->path = fileName;

    int nb = tableau->size();
    qDebug()<<"enregistreSous table size is "+nb;
    if (nb == 0)
        return 0;

    //cas tableau non vide
    database->openDB();
    //creation of new tables
    while(nb > nombreTableEcrit){
        QString name = ui->comboBox->itemText(nombreTableEcrit);
        database->createLibraryTable(name);
        nombreTableEcrit++;
    }

    for(int i =0; i< nb; i++){ //parcourir tous les tables
        database->setNomTable(ui->comboBox->itemText(i));
        int rowCnt = tableau->at(i)->rowCount();
        for(int j = 0;j < rowCnt;j++){
            book = readLineTable(i,j);
            database->saveBook(book);
        }
    }
    nombreTableEcrit = 0; // RAZ
    database->closeDB();

    return 0;
}

int MainWindow::ouvertureBib(){
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"),QString(),
                                           tr("Database files(*.db)") );
    QFile file(fileName);
    if(!fileName.isEmpty())
    {
        if(!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::critical(this,tr("Error"),tr("Could not write into this file"));
            return 0;
        }
    }
    qDebug()<<"filename: "<<fileName;
    QString nomTmp = QDir(fileName).dirName(); // nom.db
    database->setNomBib(nomTmp.left(nomTmp.length()-3));
    database->path = fileName.left(fileName.length()-nomTmp.length());
    nomFichier = fileName;
    ui->textEdit->setText(nomFichier);
    database->openDB();
    database->readDB();

    return 0;
}

PersistentObject * MainWindow::readLineTable(int tabNum,int row){
    for(int i=0;i<4;i++){
        QString qs = tableau->at(tabNum)->horizontalHeaderItem(i)->text();
        if(tableau->at(tabNum)->item(row,i) != NULL){
            QVariant qvar(tableau->at(tabNum)->item(row,i)->text());
            book->addAttribute(qs,qvar);
        }else{
            book->addAttribute(qs,"");
        }
    }
    return book;
}

// update the coordinates of the cell selected
void MainWindow::updateCoordinate(int row, int column)
{
    ligne = row;
    colonne = column;
    //std::cout << "row: " << row << "    column: " << column << std::endl;
}


void MainWindow::on_pushButton_clicked() // add row
{
    //std::cout << ui->tableWidget->rowCount() << std::endl;
    //ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    if(tableau->size() == 0){
        QMessageBox msgBox  ;
        msgBox.setText("Table does not exist!");
        msgBox.setInformativeText("Press OK to continue");
        msgBox.exec();
    }else
        tableau->at(indice)->insertRow(tableau->at(indice)->rowCount());
}

void MainWindow::on_pushButton_2_clicked() // delete row
{
     if( (ligne == -1) || (ligne >= tableau->at(indice)->rowCount()) ){
         QMessageBox msgBox;
         msgBox.setText("Please select a row first.");
         msgBox.exec();
     }
     tableau->at(indice)->removeRow(ligne);   //removeRow(ligne);
     if(ligne == 0) // allows to check if we have to specify a row to delete
         ligne--;

}

void MainWindow::on_pushButton_3_clicked() // creat table
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Table creation"),tr("Table name:"), QLineEdit::Normal,"", &ok);
    if (ok && !text.isEmpty()){
        ui->comboBox->addItem(text);
        database->totTable.append(text);
    }

    QTableWidget *tableWidget = new QTableWidget(0, 4, this);
    QStringList headers;
    headers << "Author"<< "Title"<< "ISBN"<< "Year";
    tableWidget->setHorizontalHeaderLabels(headers);
    //tableWidget->resize(420,270);
    tableWidget->setGeometry(0,60,420,270);
    tableau->append(tableWidget);
    if(indice!=-1)
    {
      tableau->at(indice)->hide();
      connect(tableau->at(indice), SIGNAL(cellClicked(int,int)), this, SLOT(updateCoordinate(int,int)));
    }
    indice=tableau->size()-1;
    tableau->at(indice)->show();
    ui->comboBox->setCurrentIndex(indice);

    connect(tableau->at(indice), SIGNAL(cellClicked(int,int)), this, SLOT(updateCoordinate(int,int)));
    //cellClicked
    //connect(tableau->at(indice), SIGNAL(cellClicked(int,int)), this, SLOT(updateCoordinate(int,int)));
    statusBar()->showMessage(tr("Table created"),2000);
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    int size = tableau->size();

    for(int i=0;i<size;i++){
        if(i == index){
            tableau->at(index)->show();
            connect(tableau->at(index), SIGNAL(cellClicked(int,int)), this, SLOT(updateCoordinate(int,int)));
        }
        else{
            tableau->at(i)->hide();
            disconnect(tableau->at(i), SIGNAL(cellClicked(int,int)), this, SLOT(updateCoordinate(int,int)));
        }
    }
    indice = index;
    //std::cout << "index: " << index  << "   nombre: " << tableau->size() << std::endl; // test ok
}

void MainWindow::deleteATable(int _ind)
{
    tableau->at(_ind)->hide();
    tableau->removeAt(_ind);
}


void MainWindow::on_deleteTable_clicked()
{
    int oldindice;
    if(tableau->size()>0)
    {
        oldindice=indice;
        deleteATable(indice);

        if(indice>0)
        {

            indice=indice-1;

        }else if(indice==0)
        {

            indice=tableau->size()-1;

        }


        ui->comboBox->setCurrentIndex(indice);
        ui->comboBox->removeItem(oldindice);

    }
}
