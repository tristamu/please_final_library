#ifndef PERSISTENTOBJECT_H
#define PERSISTENTOBJECT_H

#include <QList>
#include <QDebug>
#include "persistentAttribute.h"
class PersistentObject
{
private:
    QList<PersistentAttribute *> *attributes;
    QString table;
    int id;
public:
    PersistentObject(QString = NULL,int = 0);
    ~PersistentObject();
    void addAttribute(QString, QVariant);
    PersistentAttribute * getIndexAttribut(int);
    int save();
    void testFunction();
};

#endif // PERSISTENTOBJECT_H
