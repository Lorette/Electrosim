/***********************************************************************
 * Module:  multiplexer.h
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: mardi 5 juin 2012 16:27:12
 * Purpose: Declaration of the class Multiplexer
 ***********************************************************************/

#ifndef MULTIPLEXER_H
#define MULTIPLEXER_H

/*!
 * \file multiplexer.h
 * \brief Fichier du composant Multiplexer
 * \author SALMON PAUL
 *         MONLOUIS Kevyn
 *         DUREUIL Brice
 * \version 1.0
 * \date 5 juin 2012
 */

#include <QVector>
#include <QMessageBox>
#include <qmath.h>

#include "item.h"

/*! \class Multiplexer
  * \brief Classe Multiplexer :
  *
  *  Classe du composant Multiplexer.
  *  Un multiplexeur possede un certain nombre d'entree en fonction de son nombre de bit d'adressage.
  *  Son nombre de bit d'adressage est la valeur de la variable aux. Si aux vaut n, dans la liste des
  *  entrees (inputs) les n premiers elements sont les bits d'adressages et les elements restants sont les entrees.
  *  Sa sortie est l'entree indiquee par les bits d'adressage.
  */

class Multiplexer : public Item
{
public:
    /*!
     *  \brief Constructeur.
     *  \param n : nombre de sortie
     *
     *  Constructeur de la classe Multiplexer.
     */
    Multiplexer(int n);

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

#endif // MULTIPLEXER_H
