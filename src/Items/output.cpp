/***********************************************************************
 * Module:  output.cpp
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: mardi 15 mai 2012 01:45:20
 * Purpose: Implementation of the class Output
 ***********************************************************************/

#include "output.h"

////////////////////////////////////////////////////////////////////////
// Name:       Output::Output() : Item()
// Purpose:    Implementation of Output::Output()
// Return:
////////////////////////////////////////////////////////////////////////

Output::Output() : Item()
{
    this->image = ":/Images/output.png";
    this->description = "An output gets one of the final value of the circuit.";
    this->classe = Item::Output;
    this->inputs.resize(1); // 1 entr�e
    this->aux = -1;
}

////////////////////////////////////////////////////////////////////////
// Name:       bool Output::_do()
// Purpose:    Implementation of Output::_do()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Output::_do() // A refaire ici
{
    this->aux = *(this->inputs.at(0)->value);

    return true;
}
