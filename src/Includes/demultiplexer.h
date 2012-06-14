/***********************************************************************
 * Module:  demultiplexer.h
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: lundi 4 juin 2012 14:31:54
 * Purpose: Declaration of the class Demultiplexer
 ***********************************************************************/

#ifndef DEMULTIPLEXER_H
#define DEMULTIPLEXER_H

/*!
 * \file demultiplexer.h
 * \brief Fichier du composant Demultiplexer
 * \author SALMON PAUL
 *         MONLOUIS Kevyn
 *         DUREUIL Brice
 * \version 1.0
 * \date 4 juin 2012
 */

#include <qmath.h>

#include "item.h"

/*! \class Demultiplexer
  * \brief Classe Demultiplexer :
  *
  *  Classe du composant Demultiplexer.
  *  Un demultiplexeur possede un certain nombre de sortie en fonction de son nombre de bit d'adressage et a une entree.
  *  Son nombre de bit d'adressage est la valeur de la variable aux.
  *  Si aux vaut n, dans la liste des entrees (inputs) les n premiers elements sont les bits d'adressages
  *  et le dernier element restant est l'entree du demultiplexeur.
  *  Il donne a la sortie indiquee par les bits d'adressage la valeur de son entree.
  */

class Demultiplexer : public Item
{
public:
    /*!
     *  \brief Constructeur.
     *  \param n : nombre d'entrees du demultiplexur
     *
     *  Constructeur de la classe Demultiplexer.
     */
    Demultiplexer(int n);

    /*!
     *  \brief Fonction de traitement des donnees.
     *
     *  \return true si les donnees ont ete correctement traitees sinon false
     */
    virtual bool _do();

    /*!
     *  \brief Fonction d'application de la valeur auxiliaire.
     *  \param value : nouvelle valeur pour la variable auxiliaire
     *
     */
    virtual void setAuxValue(int value);
};

#endif // DEMULTIPLEXER_H
