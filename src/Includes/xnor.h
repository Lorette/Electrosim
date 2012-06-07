#ifndef XNOR_H
#define XNOR_H

#include <QVector>

#include "item.h"

class XNOr : public Item
{
public:
    XNOr();
    virtual bool _do();
};

#endif // XNOR_H
