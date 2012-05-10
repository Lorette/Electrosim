#ifndef OUTPUT_H
#define OUTPUT_H

#include <QMessageBox>
#include "item.h"

class Output : public Item
{
public:
    explicit Output();
    virtual bool _do();
    virtual int getClass();
};

#endif // OUTPUT_H
