/***********************************************************************
 * Module:  item.cpp
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: lundi 7 mai 2012 22:45:20
 * Purpose: Implementation of the class Item
 ***********************************************************************/

#include "item.h"

////////////////////////////////////////////////////////////////////////
// Name:       Item::Item(QObject *parent) : QObject(parent)
// Purpose:    Implementation of Item::Item()
// Return:
////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////
// Name:       void Item::setAuxValue(int value)
// Purpose:    Implementation of Item::setAuxValue()
// Return:     void
////////////////////////////////////////////////////////////////////////

void Item::setAuxValue(int value) {
    this->aux = value;
}
