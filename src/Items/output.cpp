#include "output.h"

Output::Output() : Item()
{
    this->image = ":/Images/output.png";
    this->image_connected = ":/Images/output_connected.png";
    this->description = "Output";
    this->inputs.resize(1);
}

bool Output::_do()
{
    QMessageBox::critical(0,"Output :::", QString::number(*this->inputs.at(0)->value));
    return false;
}

int Output::getClass() {
    return Output1;
}
