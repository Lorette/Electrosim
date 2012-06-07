#ifndef INPUT_H
#define INPUT_H

#include <QVector>

#include "item.h"

class Input : public Item
{
public:
    explicit Input();
    virtual bool _do();

};

#endif // INPUT_H
