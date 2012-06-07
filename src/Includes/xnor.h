/***********************************************************************
 * Module:  xnor.h
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: mardi 5 juin 2012 14:12:23
 * Purpose: Declaration of the class XNOr
 ***********************************************************************/

#ifndef XNOR_H
#define XNOR_H

/*!
 * \file xnor.h
 * \brief Fichier du composant XNOr
 * \author SALMON PAUL
 *         MONLOUIS Kevyn
 *         DUREUIL Brice
 * \version 1.0
 * \date 5 juin 2012
 */

#include <QVector>

#include "item.h"

/*! \class XNOr
  * \brief Classe XNOr :
  *
  *  Classe du composant XNOr.
  */

class XNOr : public Item
{
public:
    /*!
     *  \brief Constructeur.
     *
     *  Constructeur de la classe XNOr.
     */
    XNOr();

    /*!
     *  \brief Fonction de traitement des donn�es.
     *
     *  \return true si les donn�es ont �t� correctement trait�es sinon false
     */
    virtual bool _do();
};

#endif // XNOR_H
