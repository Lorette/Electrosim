/***********************************************************************
 * Module:  Node.cpp
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: mardi 5 juin 2012 15:01:47
 * Purpose: Implementation of the class Node
 ***********************************************************************/

#include "node.h"

////////////////////////////////////////////////////////////////////////
// Name:       Node::Node(int n) : Item()
// Purpose:    Implementation of Node::Node()
// Return:
////////////////////////////////////////////////////////////////////////

Node::Node(int n) : Item()
{
    this->image = ":/Images/node.png";
    this->aux = n;
    this->classe = Item::Node;
    this->inputs.resize(1); // 1 entree ...
    this->outputs.resize(n); // ... et n sorties
}

////////////////////////////////////////////////////////////////////////
// Name:       bool Node::_do()
// Purpose:    Implementation of Node::_do()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Node::_do() {
    for(int i = 0; i < this->outputs.size(); i++) {
        if(this->outputs.at(i) != NULL) {
            this->outputs.at(i)->value = new int;
            *(this->outputs.at(i)->value) = *(this->inputs.at(0)->value);
        }
    }

    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       void Node::setAuxValue(int value)
// Purpose:    Implementation of Node::setAuxValue()
// Return:     void
////////////////////////////////////////////////////////////////////////

void Node::setAuxValue(int value) {
    this->aux = value;
    this->outputs.resize(this->aux);
}
