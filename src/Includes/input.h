/***********************************************************************
 * Module:  input.h
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: dimanche 13 mai 2012 10:00:26
 * Purpose: Declaration of the class Input
 ***********************************************************************/

#ifndef INPUT_H
#define INPUT_H

/*!
 * \file input.h
 * \brief Fichier du composant Input
 * \author SALMON PAUL
 *         MONLOUIS Kevyn
 *         DUREUIL Brice
 * \version 1.0
 * \date 13 mai 2012
 */

#include <QVector>

#include "item.h"

/*! \class Input
  * \brief Classe Input :
  *
  *  Classe du composant Input.
  */

class Input : public Item
{
public:
    /*!
     *  \brief Constructeur.
     *
     *  Constructeur de la classe Input.
     */
    explicit Input();

    /*!
     *  \brief Fonction de traitement des données.
     *
     *  \return true si les données ont été correctement traitées sinon false
     */
    virtual bool _do();

};

#endif // INPUT_H
