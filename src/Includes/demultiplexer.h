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

#include <QVector>
#include <qmath.h>

#include "item.h"

/*! \class Demultiplexer
  * \brief Classe Demultiplexer :
  *
  *  Classe du composant Demultiplexer.
  */

class Demultiplexer : public Item
{
public:
    /*!
     *  \brief Constructeur.
     *  \param n : nombre d'entrées du demultiplexur
     *
     *  Constructeur de la classe Demultiplexer.
     */
    Demultiplexer(int n);

    /*!
     *  \brief Fonction de traitement des données.
     *
     *  \return true si les données ont été correctement traitées sinon false
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
