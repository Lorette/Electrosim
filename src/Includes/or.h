#ifndef OR_H
#define OR_H

#include <QVector>

#include "item.h"

class Or : public Item
{
public:
    Or();
    virtual bool _do();
};

#endif // OR_H
