#include "input.h"

Input::Input() : Item()
{
    this->image = ":/Images/input.png"; // Image du composant
    this->description = "Input"; // Description à la con
    this->outputs.resize(1); // Inidque 1 sortie
}

bool Input::_do()
{
    /* A IMPLEMENTER */
    return true;
}

int Input::getClass() {
    return Input0;
}
