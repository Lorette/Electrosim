#ifndef NOT_H
#define NOT_H

#include <QVector>

#include "item.h"

class Not : public Item
{

public:
    explicit Not();
    virtual bool _do();
    virtual int getClass();
};

#endif // NOT_H
