#include "item.h"

Item::Item(QObject *parent) : QObject(parent) // Constructeur
{
    this->name = "";
    this->description = "Item"; // Nom par default
    this->image = ":/Images/item.png"; // Image par default
    this->inputs.resize(0); // Pas d'entrée ...
    this->outputs.resize(0); // et de sortie par default
    this->deleted = true;
    this->aux = 0;
}

Item::~Item() // Destructeur
{
    this->deleteAllConnexion();
}

bool Item::setAuxValue(int value) {
    if(this->getClass() != Item::Input0 && this->getClass() != Item::Output1 && this->getClass() != Item::Mux5)
        return false;

    this->aux = value;

    return true;

}

void Item::setIndex(const QModelIndex &i)
{
    index = i; // !!!!!!!!!!!! @@@@@@@@@
}

Item::s_index Item::getIndex() const // !!!!!!!!!! @@@@@@@@@@@@
{
    s_index resultat;
    resultat.c = index.column();
    resultat.r = index.row();
    resultat.num_max_input = inputs.size();
    return resultat;
}

QList< QVariant > Item::getIndexOutputs() const { // Paul !!!!!!!!! @@@@@@@@
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
