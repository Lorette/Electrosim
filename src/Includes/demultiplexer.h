#ifndef DEMULTIPLEXER_H
#define DEMULTIPLEXER_H

#include <QVector>
#include <qmath.h>

#include "item.h"

class Demultiplexer : public Item
{
public:
    Demultiplexer(int n);
    virtual bool _do();
    virtual int getClass();
    virtual bool setAuxValue(int value);
};

#endif // DEMULTIPLEXER_H
