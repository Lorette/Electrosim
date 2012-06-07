/***********************************************************************
 * Module:  or.h
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: vendredi 18 mai 2012 17:23:49
 * Purpose: Declaration of the class Or
 ***********************************************************************/

#ifndef OR_H
#define OR_H

/*!
 * \file or.h
 * \brief Fichier du composant Or
 * \author SALMON PAUL
 *         MONLOUIS Kevyn
 *         DUREUIL Brice
 * \version 1.0
 * \date 18 mai 2012
 */

#include <QVector>

#include "item.h"

/*! \class Or
  * \brief Classe Or :
  *
  *  Classe du composant Or.
  */

class Or : public Item
{
public:
    /*!
     *  \brief Constructeur.
     *
     *  Constructeur de la classe Or.
     */
    explicit Or();

    /*!
     *  \brief Fonction de traitement des donn�es.
     *
     *  \return true si les donn�es ont �t� correctement trait�es sinon false
     */
    virtual bool _do();
};

#endif // OR_H
