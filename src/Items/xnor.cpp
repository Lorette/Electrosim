/***********************************************************************
 * Module:  xnor.cpp
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: mardi 5 juin 2012 14:12:23
 * Purpose: Implementation of the class XNOr
 ***********************************************************************/

#include "xnor.h"

////////////////////////////////////////////////////////////////////////
// Name:       XNOr::XNOr() : Item()
// Purpose:    Implementation of XNOr::XNOr()
// Return:
////////////////////////////////////////////////////////////////////////

XNOr::XNOr() : Item()
{
    this->image = ":/Images/xnor.png";
    this->classe = Item::XNOr;
    this->inputs.resize(2); // 2 entrées ...
    this->outputs.resize(1); // ... et 1 sortie
}

////////////////////////////////////////////////////////////////////////
// Name:       bool XNOr::_do()
// Purpose:    Implementation of XNOr::_do()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool XNOr::_do() {
    if(this->outputs.at(0) == NULL) // Si il y'a pas de connection sur la premeire sortie
        return false; // Ba c'est pas bon ...

    this->outputs.at(0)->value = new int; // Sinon on réserve de la place pour la valeur de sortie
    *(this->outputs.at(0)->value) = ((*(this->inputs.at(0)->value)) == (*(this->inputs.at(1)->value))) ? 1 : 0; // Fonction XNOR !

    return true;
}
