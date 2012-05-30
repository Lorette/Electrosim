#include "output.h"

Output::Output() : Item()
{
    this->image = ":/Images/output.png";
    this->image_connected = ":/Images/output_connected.png";
    this->description = "Output";
    this->inputs.resize(1); // 1 entr�e
}

bool Output::_do() // A refaire ici
{
    emit sendSignal(this->inputs.at(0)->value);

    return false;
}

int Output::getClass() {
    return Output1;
}
