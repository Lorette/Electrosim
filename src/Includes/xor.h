/***********************************************************************
 * Module:  xor.h
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: mercredi 6 juin 2012 17:55:12
 * Purpose: Declaration of the class Xor
 ***********************************************************************/

#ifndef XOR_H
#define XOR_H

/*!
 * \file xor.h
 * \brief Fichier du composant Xor
 * \author SALMON PAUL
 *         MONLOUIS Kevyn
 *         DUREUIL Brice
 * \version 1.0
 * \date 6 juin 2012
 */

#include <QVector>

#include "item.h"

/*! \class Xor
  * \brief Classe Xor :
  *
  *  Classe du composant Xor.
  */

class Xor : public Item
{
public:
    /*!
     *  \brief Constructeur.
     *
     *  Constructeur de la classe Xor.
     */
    Xor();

    /*!
     *  \brief Fonction de traitement des données.
     *
     *  \return true si les données ont été correctement traitées sinon false
     */
    virtual bool _do();
};


#endif // XOR_H
