#ifndef IEO_H
#define IEO_H

#include <QVector>

#include "item.h"

class IeO : public Item
{

public:
    explicit IeO(int n);
    virtual bool _do();
    virtual bool setAuxValue(int value);
};

#endif // IEO_H
