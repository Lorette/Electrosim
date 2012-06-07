/***********************************************************************
 * Module:  not.h
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: dimanche 20 mai 2012 12:14:24
 * Purpose: Declaration of the class Not
 ***********************************************************************/

#ifndef NOT_H
#define NOT_H

/*!
 * \file not.h
 * \brief Fichier du composant Not
 * \author SALMON PAUL
 *         MONLOUIS Kevyn
 *         DUREUIL Brice
 * \version 1.0
 * \date 20 mai 2012
 */

#include <QVector>

#include "item.h"

/*! \class Not
  * \brief Classe Not :
  *
  *  Classe du composant Not.
  */

class Not : public Item
{

public:
    /*!
     *  \brief Constructeur.
     *
     *  Constructeur de la classe Not.
     */
    explicit Not();

    /*!
     *  \brief Fonction de traitement des données.
     *
     *  \return true si les données ont été correctement traitées sinon false
     */
    virtual bool _do();
};

#endif // NOT_H
