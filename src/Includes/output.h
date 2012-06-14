/***********************************************************************
 * Module:  output.h
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: mardi 15 mai 2012 01:45:20
 * Purpose: Declaration of the class Output
 ***********************************************************************/

#ifndef OUTPUT_H
#define OUTPUT_H

/*!
 * \file output.h
 * \brief Fichier du composant Output
 * \author SALMON PAUL
 *         MONLOUIS Kevyn
 *         DUREUIL Brice
 * \version 1.0
 * \date 15 mai 2012
 */

#include "item.h"

/*! \class Output
  * \brief Classe Output :
  *
  *  Classe du composant Output.
  */

class Output : public Item
{
public:
    /*!
     *  \brief Constructeur.
     *
     *  Constructeur de la classe Output.
     */
    explicit Output();

    /*!
     *  \brief Fonction de traitement des donnees.
     *
     *  \return true si les donnees ont ete correctement traitees sinon false
     */
    virtual bool _do();
};

#endif // OUTPUT_H
