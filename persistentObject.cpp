#include"persistentObject.h"
#include<iostream>

PersistentObject::PersistentObject(QString className,int isbn){
    attributes = new QList<PersistentAttribute *>();
    PersistentAttribute * ajout1 = new PersistentAttribute("Author");
    PersistentAttribute * ajout2 = new PersistentAttribute("Title");
    PersistentAttribute * ajout3 = new PersistentAttribute("ISBN");
    PersistentAttribute * ajout4 = new PersistentAttribute("Year");

    attributes->append(ajout1);
    attributes->append(ajout2);
    attributes->append(ajout3);
    attributes->append(ajout4);

    id = isbn;
    table = className;
}

PersistentObject::~PersistentObject(){
    delete [] attributes;
    std::cout << "destructor of persistantObject" << std::endl;
}
void PersistentObject::addAttribute(QString name,QVariant var){

    if(name == "Author")
        attributes->at(0)->setVariable(var);
    if(name == "Title")
        attributes->at(1)->setVariable(var);
    if(name == "ISBN")
        attributes->at(2)->setVariable(var);
    if(name == "Year")
        attributes->at(3)->setVariable(var);
    //std::cout << "persistentObject length is "<<attributes->length() << std::endl;
}

PersistentAttribute * PersistentObject::getIndexAttribut(int index){
    if(index < attributes->size())
        return attributes->at(index);
    else
        return NULL;
}

int PersistentObject::save(){
    return id;
}

void PersistentObject::testFunction(){
    for(int i =0;i < attributes->size();i++){
        qDebug() << attributes->at(i)->variable.toString();
    }
}
