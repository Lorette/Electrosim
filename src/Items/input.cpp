/***********************************************************************
 * Module:  input.cpp
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: dimanche 13 mai 2012 10:00:26
 * Purpose: Implementation of the class Input
 ***********************************************************************/

#include "input.h"

////////////////////////////////////////////////////////////////////////
// Name:       Input::Input() : Item()
// Purpose:    Implementation of Input::Input()
// Return:
////////////////////////////////////////////////////////////////////////

Input::Input() : Item()
{
    this->image = ":/Images/input.png"; // Image du composant
    this->description = "Input"; // Description à la con
    this->classe = Item::Input;
    this->outputs.resize(1); // Indique 1 sortie
}

////////////////////////////////////////////////////////////////////////
// Name:       bool Input::_do()
// Purpose:    Implementation of Input::_do()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Input::_do()
{
    if(this->outputs.at(0) == NULL) // Si il y'a pas de connection sur la premeire sortie
        return false; // Ba c'est pas bon ...

    this->outputs.at(0)->value = new int; // Sinon on réserve de la place pour la valeur de sortie
    *(this->outputs.at(0)->value) = this->aux;

    return true;
}
