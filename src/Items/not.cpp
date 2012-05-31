#include "not.h"

Not::Not() : Item()
{
    this->image = ":/Images/not.png";
    this->description = "Not";
    this->inputs.resize(1); // 1 entr�e ...
    this->outputs.resize(1); // ... et 1 sortie ... logique
}

bool Not::_do() {
    if(this->outputs.at(0) == NULL) // Si il y'a pas de connection sur la premeire sortie
        return false; // Ba c'est pas bon ...

    this->outputs.at(0)->value = new int; // Sinon on r�serve de la place pour la valeur de sortie
    *(this->outputs.at(0)->value) = 1 - *(this->inputs.at(0)->value); // 1 devient 0 et 0 devient 1

    return true;
}

int Not::getClass() {
    return Not2;
}
