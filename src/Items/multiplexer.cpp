#include "multiplexer.h"

Multiplexer::Multiplexer(int n) : Item()
{
    this->image = ":/Images/mux.png";
    this->description = "Multiplexer";
    this->aux = n;
    this->inputs.resize(n + log2(n)); // n entrées + choix de l'entrée en log2 N
    this->outputs.resize(1); // ... et 1 sortie
}

bool Multiplexer::_do() {
    int in = 0;
    int s = this->inputs.size() - 1;

    if(this->outputs.at(0) == NULL) // Si il y'a pas de connection sur la premeire sortie
        return false; // Ba c'est pas bon ...

    for(int i = 0; i < log2(this->aux); i++)
        in += (*(this->inputs.at(s - i)->value)) * qPow(2,i);

    this->outputs.at(0)->value = new int;
    *(this->outputs.at(0)->value) = *(this->inputs.at(in)->value); // !!! Copie de la valeur, pas du pointeur

    return true;

}

int Multiplexer::getClass() {
    return Mux5;
}

bool Multiplexer::setAuxValue(int value) {
    this->aux = value;
    this->inputs.resize(this->aux + log2(this->aux));
    return true;
}
