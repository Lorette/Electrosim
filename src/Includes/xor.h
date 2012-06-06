#ifndef XOR_H
#define XOR_H

#include <QVector>

#include "item.h"

class Xor : public Item
{
public:
    Xor();
    virtual bool _do();
    virtual int getClass();
};


#endif // XOR_H
