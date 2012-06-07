/***********************************************************************
 * Module:  or.cpp
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: vendredi 18 mai 2012 17:23:49
 * Purpose: Implementation of the class Or
 ***********************************************************************/

#include "or.h"

////////////////////////////////////////////////////////////////////////
// Name:       Or::Or() : Item()
// Purpose:    Implementation of Or::Or()
// Return:
////////////////////////////////////////////////////////////////////////

Or::Or() : Item()
{
    this->image = ":/Images/or.png";
    this->description = "Or";
    this->classe = Item::Or;
    this->inputs.resize(2); // 2 entrées ...
    this->outputs.resize(1); // ... et 1 sortie
}

////////////////////////////////////////////////////////////////////////
// Name:       bool Or::_do()
// Purpose:    Implementation of Or::_do()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Or::_do() {
    if(this->outputs.at(0) == NULL) // Si il y'a pas de connection sur la premeire sortie
        return false; // Ba c'est pas bon ...

    this->outputs.at(0)->value = new int; // Sinon on réserve de la place pour la valeur de sortie
    *(this->outputs.at(0)->value) = ((*(this->inputs.at(0)->value)) == 1 || (*(this->inputs.at(1)->value)) == 1) ? 1 : 0; // Fonction OU !

    return true;
}
