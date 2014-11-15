#ifndef PERSISTENTATTRIBUTE_H
#define PERSISTENTATTRIBUTE_H

#include <QVariant>
class PersistentAttribute
{
public:
    QString name;
    QVariant variable;
    void setVariable(QVariant);
    QVariant getVariable();



PersistentAttribute(QString = NULL, QVariant = NULL);
~PersistentAttribute();
};

#endif // PERSISTENTATTRIBUTE_H
