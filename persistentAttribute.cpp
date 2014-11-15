#include "persistentAttribute.h"
#include<iostream>

PersistentAttribute::PersistentAttribute(QString nom, QVariant var){
    name = nom;
    variable = var;
}

PersistentAttribute::~PersistentAttribute(){
    std::cout<< "destructor of PersistentAttribute" << std::endl;
}

void PersistentAttribute::setVariable(QVariant var){
    variable = var;
}

QVariant PersistentAttribute::getVariable(){
    return variable;
}
