#include "ieo.h"

IeO::IeO(int n) : Item()
{
    this->image = ":/Images/ieo.png";
    this->description = "Input egal Output";
    this->aux = n;
    this->classe = Item::IeO8;
    this->inputs.resize(1); // 1 entrée ...
    this->outputs.resize(n); // ... et n sorties
}

bool IeO::_do() {
    for(int i = 0; i < this->outputs.size(); i++)
        if(this->outputs.at(i) == NULL) // Si une connexion n'est pas connectée
            return false; // Ba c'est pas bon ...

    for(int i = 0; i < this->outputs.size(); i++) {
        this->outputs.at(i)->value = new int;
        *(this->outputs.at(i)->value) = *(this->inputs.at(0)->value);
    }

    return true;
}

bool IeO::setAuxValue(int value) {
    this->aux = value;
    this->outputs.resize(this->aux);
    return true;
}
