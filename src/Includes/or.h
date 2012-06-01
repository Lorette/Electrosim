#ifndef OR_H
#define OR_H

#include <QVector>

#include "item.h"

class Or : public Item
{
public:
    Or();
    virtual bool _do();
    virtual int getClass();
};

#endif // OR_H
