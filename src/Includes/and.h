/***********************************************************************
 * Module:  and.h
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: samedi 12 mai 2012 17:18:12
 * Purpose: Declaration of the class And
 ***********************************************************************/

#ifndef AND_H
#define AND_H

/*!
 * \file and.h
 * \brief Fichier du composant And
 * \author SALMON PAUL
 *         MONLOUIS Kevyn
 *         DUREUIL Brice
 * \version 1.0
 * \date 12 mai 2012
 */

#include <QVector>

#include "item.h"

/*! \class And
  * \brief Classe And :
  *
  *  Classe du composant And.
  */

class And : public Item
{
public:
    /*!
     *  \brief Constructeur.
     *
     *  Constructeur de la classe And.
     */
    And();

    /*!
     *  \brief Fonction de traitement des donnees.
     *
     *  \return true si les donnees ont ete correctement traitees sinon false
     */
    virtual bool _do();
};

#endif // AND_H
