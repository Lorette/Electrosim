/***********************************************************************
 * Module:  multiplexer.cpp
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: mardi 5 juin 2012 16:27:12
 * Purpose: Implementation of the class Multiplexer
 ***********************************************************************/

#include "multiplexer.h"

////////////////////////////////////////////////////////////////////////
// Name:       Multiplexer::Multiplexer(int n) : Item()
// Purpose:    Implementation of Multiplexer::Multiplexer()
// Return:
////////////////////////////////////////////////////////////////////////

Multiplexer::Multiplexer(int n) : Item()
{
    int i;
    this->image = ":/Images/mux.png";
    this->classe = Item::Mux;
    this->aux = n;
    for(i = 0; n > qPow(2,i); i++); // Calcul du nombre d'entree supplementaire (Adressage)
    this->inputs.resize(n + i); // n entrees + nombre d'entree supplementaire
    this->outputs.resize(1); // ... et 1 sortie
}

////////////////////////////////////////////////////////////////////////
// Name:       bool Multiplexer::_do())
// Purpose:    Implementation of Multiplexer::_do()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Multiplexer::_do() {
    int in = 0;
    int s = this->inputs.size() - 1;

    if(this->outputs.at(0) == NULL) // Si il y'a pas de connection sur la premeire sortie
        return false; // Ba c'est pas bon ...

    for(int i = 0; i < log2(this->aux); i++) // Fonction du multiplexeur et
        in += (*(this->inputs.at(s - i)->value)) * qPow(2,i); // calcul de l'entree sur laquelle prendre la valeur

    if(in > this->aux) // Si l'entree n'existe pas ...
        return false; // faux

    this->outputs.at(0)->value = new int;
    *(this->outputs.at(0)->value) = *(this->inputs.at(in)->value); // !!! Copie de la valeur, pas du pointeur

    return true;

}

////////////////////////////////////////////////////////////////////////
// Name:       void Multiplexer::setAuxValue(int value)
// Purpose:    Implementation of Multiplexer::setAuxValue()
// Return:     void
////////////////////////////////////////////////////////////////////////

void Multiplexer::setAuxValue(int value) {
    int i;
    this->aux = value;
    for(i = 0; value > qPow(2,i); i++); // Calcul du nombre d'entree supplementaire (Adressage)
    this->inputs.resize(value + i); // n entrees + nombre d'entree supplementaire
}
