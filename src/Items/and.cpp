/***********************************************************************
 * Module:  and.cpp
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: samedi 12 mai 2012 17:18:12
 * Purpose: Implementation of the class And
 ***********************************************************************/

#include "and.h"

////////////////////////////////////////////////////////////////////////
// Name:       And::And() : Item()
// Purpose:    Implementation of And::And()
// Return:
////////////////////////////////////////////////////////////////////////

And::And() : Item()
{
    this->image = ":/Images/and.png";
    this->classe = Item::And;
    this->inputs.resize(2); // 2 entrees ...
    this->outputs.resize(1); // ... et 1 sortie
}

////////////////////////////////////////////////////////////////////////
// Name:       bool And::_do()
// Purpose:    Implementation of And::_do()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool And::_do() {
    if(this->outputs.at(0) == NULL) // Si il y'a pas de connection sur la premeire sortie
        return false; // Ba c'est pas bon ...

    this->outputs.at(0)->value = new int; // Sinon on reserve de la place pour la valeur de sortie
    *(this->outputs.at(0)->value) = ((*(this->inputs.at(0)->value)) == 1 && (*(this->inputs.at(1)->value)) == 1) ? 1 : 0; // Fonction OU !

    return true;
}
