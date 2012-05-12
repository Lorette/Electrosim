#include "item.h"

Item::Item(QObject *parent) : QObject(parent)
{
    this->name = "";
    this->description = "Item";
    this->image = ":/Images/item.png";
    this->image_connected = ":/Images/item_connected.png";
    this->inputs.resize(0);
    this->outputs.resize(0);
    this->deleted = true;
}

void Item::setIndex(const QModelIndex &i)
{
    index = i;
}

Item::s_index Item::getIndex() const
{
    s_index resultat;
    resultat.c = index.column();
    resultat.r = index.row();
    resultat.num_max_input = inputs.size();
    return resultat;
}

QList< QVariant > Item::getIndexOutputs() const {
    int s = outputs.size();
    QList< QVariant > resultat;
    for(int i=0; i<s; ++i)
    {
        if(!outputs[i])
            resultat.append(QVariant());
        else
        {
            s_index index = outputs[i]->receiver->getIndex();
            QLine l(index.c, index.r, outputs[i]->input, index.num_max_input);
            QVariant var(l);
            resultat.append(var);
        }
    }

    return resultat;
}
