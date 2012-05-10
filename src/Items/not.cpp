#include "not.h"

Not::Not() : Item()
{
    this->image = ":/Images/not.png";
    this->image_connected = ":/Images/not_connected.png";
    this->description = "Not";
    this->inputs.resize(1);
    this->outputs.resize(1);
}

bool Not::_do() {
    if(this->outputs.at(0) == NULL)
        return false;

    this->outputs.at(0)->value = new int;
    if(*(this->inputs.at(0)->value) == 0)
        *(this->outputs.at(0)->value) = 1;
    else
        *(this->outputs.at(0)->value) = 0;

    return true;
}

int Not::getClass() {
    return Not2;
}
