#include "demultiplexer.h"

Demultiplexer::Demultiplexer(int n) : Item()
{
    this->image = ":/Images/demux.png";
    this->description = "Demultiplexer";
    this->aux = n;
    this->inputs.resize(n); // n entr�es
    this->outputs.resize(qPow(2,n)); // ... et 2^n sortie
}

bool Demultiplexer::_do() {
    int in = 0;
    int s = this->inputs.size();

    for(int i = 0; i < qPow(2, this->aux); i++)
        if(this->outputs.at(i) == NULL) // Si il y'a une des sorties nulles ...
            return false; // Ba c'est pas bon ...

    for(int i = 0; i < qPow(2, this->aux); i++) {
        this->outputs.at(i)->value = new int;
        *(this->outputs.at(i)->value) = 0;
    }

    for(int i = 0; i < s; i++)
        in += (*(this->inputs.at(i)->value)) * qPow(2,i);

    this->outputs.at(in)->value = new int;
    *(this->outputs.at(in)->value) = 1; // !!! On met la sortie � 1

    return true;

}

int Demultiplexer::getClass() {
    return Demux6;
}

bool Demultiplexer::setAuxValue(int value) {
    this->aux = value;
    this->inputs.resize(this->aux);
    this->outputs.resize(qPow(2,this->aux));
    return true;
}
