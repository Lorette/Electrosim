/***********************************************************************
 * Module:  item.cpp
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: lundi 7 mai 2012 22:45:20
 * Purpose: Implementation of the class Item
 ***********************************************************************/

#include "item.h"

////////////////////////////////////////////////////////////////////////
// Name:       Item::Item(QObject *parent) : QObject(parent)
// Purpose:    Implementation of Item::Item()
// Return:
////////////////////////////////////////////////////////////////////////

Item::Item(QObject *parent) : QObject(parent) // Constructeur
{
    this->name = "";
    this->image = ":/Images/item.png"; // Image par default
    this->inputs.resize(0); // Pas d'entree ...
    this->outputs.resize(0); // et de sortie par default
    this->deleted = true;
    this->aux = 0;
}

////////////////////////////////////////////////////////////////////////
// Name:       QString Item::getName()
// Purpose:    Implementation of Item::getName()
// Return:     QString
////////////////////////////////////////////////////////////////////////

QString Item::getName()
{
    return this->name;
}

////////////////////////////////////////////////////////////////////////
// Name:       QString Item::getImage()
// Purpose:    Implementation of Item::getImage()
// Return:     QString
////////////////////////////////////////////////////////////////////////

QString Item::getImage()
{
    return this->image;
}

////////////////////////////////////////////////////////////////////////
// Name:       Item::Items Item::getClass()
// Purpose:    Implementation of Item::getClass()
// Return:     Item::Items
////////////////////////////////////////////////////////////////////////

Item::Items Item::getClass()
{
    return this->classe;
}

////////////////////////////////////////////////////////////////////////
// Name:       int Item::getAuxValue()
// Purpose:    Implementation of Item::getAuxValue()
// Return:     int
////////////////////////////////////////////////////////////////////////

int Item::getAuxValue()
{
    return this->aux;
}

////////////////////////////////////////////////////////////////////////
// Name:       QVector<Item::s_connect *> Item::getOutputs()
// Purpose:    Implementation of Item::getOutputs()
// Return:     QVector<Item::s_connect *>
////////////////////////////////////////////////////////////////////////

QVector<Item::s_connect *> Item::getOutputs()
{
    return this->outputs;
}

////////////////////////////////////////////////////////////////////////
// Name:       QVector<Item::s_connect *> Item::getInputs()
// Purpose:    Implementation of Item::getInputs()
// Return:     QVector<Item::s_connect *>
////////////////////////////////////////////////////////////////////////

QVector<Item::s_connect *> Item::getInputs()
{
    return this->inputs;
}

////////////////////////////////////////////////////////////////////////
// Name:       void Item::setName(QString name)
// Purpose:    Implementation of Item::setName()
// Return:     void
////////////////////////////////////////////////////////////////////////

void Item::setName(QString name)
{
    this->name = name;
}

////////////////////////////////////////////////////////////////////////
// Name:       void Item::setAuxValue(int value)
// Purpose:    Implementation of Item::setAuxValue()
// Return:     void
////////////////////////////////////////////////////////////////////////

void Item::setAuxValue(int value)
{
    this->aux = value;
}

////////////////////////////////////////////////////////////////////////
// Name:       bool Item::addNext(s_connect* conn)
// Purpose:    Implementation of Item::addNext()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Item::addNext(s_connect* conn)
{
    if((conn->output > this->outputs.size()) || (this->outputs.at(conn->output) != NULL) || (!conn->receiver->askForConnection(conn)))
        return false; // Si le numero de la sortie est incorrect ou si la sortie est deja utilise ou que la connection avec le composant recepteur ne se fait pas, on annule

    this->outputs[conn->output] = conn; // On le rajoute a la liste des connexions du composant courant
    this->deleted = false; // Il existe des connections dans ce composant
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       bool Item::askForConnection(s_connect* conn)
// Purpose:    Implementation of Item::askForConnection()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Item::askForConnection(s_connect* conn)
{
    if((conn->input > this->inputs.size()) || this->inputs.at(conn->input) != NULL) // Si le numero de l'entree est incorrect ou deja utilise
        return false; // On annule

    this->inputs[conn->input] = conn; // On rajoute la connexion a la liste de celles en entrees
    this->deleted = false; // Il existe des connexions dans ce composant
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       bool Item::checkAllValueReceived()
// Purpose:    Implementation of Item::checkAllValueReceived()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Item::checkAllValueReceived()
{
    for(int i = 0; i < this->inputs.size(); ++i) // Pour toutes les entrees
        if(this->inputs.at(i) == NULL || this->inputs.at(i)->value == NULL ) // SI une entree n'est pas connectee ou qu'une d'entre elle n'a pas de valeur en entree
            return false; // C'est pas bon

    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       Item::s_connect* Item::deleteInput(int input)
// Purpose:    Implementation of Item::deleteInput()
// Return:     Item::s_connect*
////////////////////////////////////////////////////////////////////////

Item::s_connect* Item::deleteInput(int input)
{
    Item::s_connect *conn;
    if(input < 0 || input > inputs.size()) //  Si l'entree n'existe pas
        return NULL; // C'est pas bon

    conn = inputs.at(input); // On sauvegarde la connexion pour le retour
    inputs[input] = NULL; // Plus de connexion a cette entree
    return conn;
}

////////////////////////////////////////////////////////////////////////
// Name:       Item::s_connect* Item::deleteOutput(int output)
// Purpose:    Implementation of Item::deleteOutput()
// Return:     Item::s_connect*
////////////////////////////////////////////////////////////////////////

Item::s_connect* Item::deleteOutput(int output)
{
    Item::s_connect *conn;
    if(output < 0 || output > outputs.size()) // Si la sortie n'existe pas
        return NULL; // C'est pas bon

    conn = outputs.at(output); // On sauvegarde la connexion pour le retour
    outputs[output] = NULL; // Plus de connexion a cette sortie
    return conn;
}

////////////////////////////////////////////////////////////////////////
// Name:       void Item::recvSignal()
// Purpose:    Implementation of Item::recvSignal()
// Return:     void
////////////////////////////////////////////////////////////////////////

void Item::recvSignal()
{
    if(this->checkAllValueReceived()) // SI toutes les valeurs ont ete reçu et
        if(this->_do()) // Si le traitement a ete correctement effectue
            emit sendSignal(); // On indique au composant suivant que les valeurs sont disponibles
}
