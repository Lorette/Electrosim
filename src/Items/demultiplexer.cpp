/***********************************************************************
 * Module:  demultiplexer.cpp
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: lundi 4 juin 2012 14:31:54
 * Purpose: Implementation of the class Demultiplexer
 ***********************************************************************/

#include "demultiplexer.h"

////////////////////////////////////////////////////////////////////////
// Name:       Demultiplexer::Demultiplexer(int n) : Item()
// Purpose:    Implementation of Demultiplexer::Demultiplexer()
// Return:
////////////////////////////////////////////////////////////////////////

Demultiplexer::Demultiplexer(int n) : Item()
{
    this->image = ":/Images/demux.png";
    this->classe = Item::Demux;
    this->aux = n;
    this->inputs.resize(n+1); // n entrees
    this->outputs.resize(qPow(2,n)); // ... et 2^n sortie
}

////////////////////////////////////////////////////////////////////////
// Name:       bool Demultiplexer::_do()
// Purpose:    Implementation of Demultiplexer::_do(
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Demultiplexer::_do() {
    int in = 0;

    //met toutes les sorties � 0
    for(int i = 0; i < qPow(2, this->aux); i++) {
        if(this->outputs.at(i) != NULL) {
            this->outputs.at(i)->value = new int;
            *(this->outputs.at(i)->value) = 0;
        }
    }

    for(int i = 0; i < this->aux; i++)
        in += (*(this->inputs.at(i)->value)) * qPow(2,i);

    if(this->outputs.at(in) != NULL) {
        this->outputs.at(in)->value = new int;
        *(this->outputs.at(in)->value) = *(this->inputs.at(this->aux)->value); // !!! On met la sortie a la valeur de l'entree
    }

    return true;

}

////////////////////////////////////////////////////////////////////////
// Name:       void Demultiplexer::setAuxValue(int value)
// Purpose:    Implementation of Demultiplexer::setAuxValue()
// Return:     void
////////////////////////////////////////////////////////////////////////

void Demultiplexer::setAuxValue(int value) {
    this->aux = value;
    this->inputs.resize(value+1);
    this->outputs.resize(qPow(2,value));
}
