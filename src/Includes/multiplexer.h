#ifndef MULTIPLEXER_H
#define MULTIPLEXER_H

#include <QVector>
#include <QMessageBox>
#include <qmath.h>

#include "item.h"

class Multiplexer : public Item
{
public:
    Multiplexer(int n);
    virtual bool _do();
    virtual bool setAuxValue(int value);
};

#endif // MULTIPLEXER_H
