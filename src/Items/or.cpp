#include "or.h"

Or::Or() : Item()
{
    this->image = ":/Images/or.png";
    this->description = "Or";
    this->inputs.resize(2); // 1 entrée ...
    this->outputs.resize(1); // ... et 1 sortie
}

bool Or::_do() {
    if(this->outputs.at(0) == NULL) // Si il y'a pas de connection sur la premeire sortie
        return false; // Ba c'est pas bon ...

    this->outputs.at(0)->value = new int; // Sinon on réserve de la place pour la valeur de sortie
    *(this->outputs.at(0)->value) = ((*(this->inputs.at(0)->value)) == 1 || (*(this->inputs.at(1)->value)) == 1) ? 1 : 0; // Fonction OU !

    return true;
}

int Or::getClass() {
    return Or3;
}
