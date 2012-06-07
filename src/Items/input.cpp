#include "input.h"

Input::Input() : Item()
{
    this->image = ":/Images/input.png"; // Image du composant
    this->description = "Input"; // Description à la con
    this->classe = Item::Input0;
    this->outputs.resize(1); // Indique 1 sortie
}

bool Input::_do()
{
    if(this->outputs.at(0) == NULL) // Si il y'a pas de connection sur la premeire sortie
        return false; // Ba c'est pas bon ...

    this->outputs.at(0)->value = new int; // Sinon on réserve de la place pour la valeur de sortie
    *(this->outputs.at(0)->value) = this->aux;

    return true;
}
