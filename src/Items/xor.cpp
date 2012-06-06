#include "xor.h"

Xor::Xor() : Item()
{
    this->image = ":/Images/xor.png";
    this->description = "Xor";
    this->inputs.resize(2); // 2 entrée ...
    this->outputs.resize(1); // ... et 1 sortie
}

bool Xor::_do() {
    if(this->outputs.at(0) == NULL) // Si il y'a pas de connection sur la premeire sortie
        return false; // Ba c'est pas bon ...

    this->outputs.at(0)->value = new int; // Sinon on réserve de la place pour la valeur de sortie
    *(this->outputs.at(0)->value) = ((*(this->inputs.at(0)->value)) != (*(this->inputs.at(1)->value))) ? 1 : 0; // Fonction XOR !

    return true;
}

int Xor::getClass() {
    return Xor9;
}
