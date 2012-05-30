#include "output.h"

Output::Output() : Item()
{
    this->image = ":/Images/output.png";
    this->image_connected = ":/Images/output_connected.png";
    this->description = "Output";
    this->inputs.resize(1); // 1 entrée
}

bool Output::_do() // A refaire ici
{
    QMessageBox::critical(0,"Output :::", QString::number(*this->inputs.at(0)->value));
    return false;
}

int Output::getClass() {
    return Output1;
}
