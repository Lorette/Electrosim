#include "and.h"

And::And() : Item()
{
    this->image = ":/Images/and.png";
    this->description = "And";
    this->classe = Item::And4;
    this->inputs.resize(2); // 2 entrées ...
    this->outputs.resize(1); // ... et 1 sortie
}

bool And::_do() {
    if(this->outputs.at(0) == NULL) // Si il y'a pas de connection sur la premeire sortie
        return false; // Ba c'est pas bon ...

    this->outputs.at(0)->value = new int; // Sinon on réserve de la place pour la valeur de sortie
    *(this->outputs.at(0)->value) = ((*(this->inputs.at(0)->value)) == 1 && (*(this->inputs.at(1)->value)) == 1) ? 1 : 0; // Fonction OU !

    return true;
}
