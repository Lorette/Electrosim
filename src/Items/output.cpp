#include "output.h"

Output::Output() : Item()
{
    this->image = ":/Images/output.png";
    this->description = "Output";
    this->inputs.resize(1); // 1 entrée
    this->aux = -1;
}

bool Output::_do() // A refaire ici
{
    this->aux = *(this->inputs.at(0)->value);

    return true;
}

int Output::getClass() {
    return Output1;
}
