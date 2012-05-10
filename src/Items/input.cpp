#include "input.h"

Input::Input() : Item()
{
    this->image = ":/Images/input.png";
    this->image_connected = ":/Images/input_connected.png";
    this->description = "Input";
    this->outputs.resize(1);
}

bool Input::_do()
{
    /* A IMPLEMENTER */
    return true;
}

int Input::getClass() {
    return Input0;
}
