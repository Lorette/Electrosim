/***********************************************************************
 * Module:  xor.cpp
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: mercredi 6 juin 2012 17:55:12
 * Purpose: Implementation of the class Xor
 ***********************************************************************/

#include "xor.h"

////////////////////////////////////////////////////////////////////////
// Name:       Xor::Xor() : Item()
// Purpose:    Implementation of Xor::Xor()
// Return:
////////////////////////////////////////////////////////////////////////

Xor::Xor() : Item()
{
    this->image = ":/Images/xor.png";
    this->classe = Item::Xor;
    this->inputs.resize(2); // 2 entrée ...
    this->outputs.resize(1); // ... et 1 sortie
}

////////////////////////////////////////////////////////////////////////
// Name:       bool Xor::_do(
// Purpose:    Implementation of Xor::_do(
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Xor::_do() {
    if(this->outputs.at(0) == NULL) // Si il y'a pas de connection sur la premeire sortie
        return false; // Ba c'est pas bon ...

    this->outputs.at(0)->value = new int; // Sinon on réserve de la place pour la valeur de sortie
    *(this->outputs.at(0)->value) = ((*(this->inputs.at(0)->value)) != (*(this->inputs.at(1)->value))) ? 1 : 0; // Fonction XOR !

    return true;
}
