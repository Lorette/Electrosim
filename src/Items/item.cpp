#include "item.h"

Item::Item(QObject *parent) : QObject(parent) // Constructeur
{
    this->name = "";
    this->description = "Item"; // Nom par default
    this->image = ":/Images/item.png"; // Image par default
    this->inputs.resize(0); // Pas d'entrée ...
    this->outputs.resize(0); // et de sortie par default
    this->deleted = true;
    this->aux = 0;
}

Item::~Item() // Destructeur
{
}

bool Item::setAuxValue(int value) {
    this->aux = value;

    return true;

}
