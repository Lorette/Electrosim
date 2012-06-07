#include "output.h"

Output::Output() : Item()
{
    this->image = ":/Images/output.png";
    this->description = "An output gets one of the final value of the circuit.";
    this->classe = Item::Output1;
    this->inputs.resize(1); // 1 entrée
    this->aux = -1;
}

bool Output::_do() // A refaire ici
{
    this->aux = *(this->inputs.at(0)->value);

    return true;
}
