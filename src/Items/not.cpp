/***********************************************************************
 * Module:  not.cpp
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: dimanche 20 mai 2012 12:14:24
 * Purpose: Implementation of the class Not
 ***********************************************************************/

#include "not.h"

////////////////////////////////////////////////////////////////////////
// Name:       Not::Not() : Item()
// Purpose:    Implementation of Not::Not()
// Return:
////////////////////////////////////////////////////////////////////////

Not::Not() : Item()
{
    this->image = ":/Images/not.png";
    this->classe = Item::Not;
    this->inputs.resize(1); // 1 entrée ...
    this->outputs.resize(1); // ... et 1 sortie ... logique
}

////////////////////////////////////////////////////////////////////////
// Name:       bool Not::_do()
// Purpose:    Implementation of Not::_do()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Not::_do() {
    if(this->outputs.at(0) == NULL) // Si il y'a pas de connection sur la premeire sortie
        return false; // Ba c'est pas bon ...

    this->outputs.at(0)->value = new int; // Sinon on réserve de la place pour la valeur de sortie
    *(this->outputs.at(0)->value) = 1 - *(this->inputs.at(0)->value); // 1 devient 0 et 0 devient 1

    return true;
}
