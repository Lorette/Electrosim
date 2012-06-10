/***********************************************************************
 * Module:  ieo.cpp
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: mardi 5 juin 2012 15:01:47
 * Purpose: Implementation of the class IeO
 ***********************************************************************/

#include "ieo.h"

////////////////////////////////////////////////////////////////////////
// Name:       IeO::IeO(int n) : Item()
// Purpose:    Implementation of IeO::IeO()
// Return:
////////////////////////////////////////////////////////////////////////

IeO::IeO(int n) : Item()
{
    this->image = ":/Images/ieo.png";
    this->aux = n;
    this->classe = Item::IeO;
    this->inputs.resize(1); // 1 entrée ...
    this->outputs.resize(n); // ... et n sorties
}

////////////////////////////////////////////////////////////////////////
// Name:       bool IeO::_do()
// Purpose:    Implementation of IeO::_do()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool IeO::_do() {
    for(int i = 0; i < this->outputs.size(); i++)
        if(this->outputs.at(i) == NULL) // Si une connexion n'est pas connectée
            return false; // Ba c'est pas bon ...

    for(int i = 0; i < this->outputs.size(); i++) {
        this->outputs.at(i)->value = new int;
        *(this->outputs.at(i)->value) = *(this->inputs.at(0)->value);
    }

    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       void IeO::setAuxValue(int value)
// Purpose:    Implementation of IeO::setAuxValue()
// Return:     void
////////////////////////////////////////////////////////////////////////

void IeO::setAuxValue(int value) {
    this->aux = value;
    this->outputs.resize(this->aux);
}
