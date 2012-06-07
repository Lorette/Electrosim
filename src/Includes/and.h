#ifndef AND_H
#define AND_H

#include <QVector>

#include "item.h"

class And : public Item
{
public:
    And();
    virtual bool _do();
};

#endif // AND_H
