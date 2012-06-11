/***********************************************************************
 * Module:  ieo.h
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: mardi 5 juin 2012 15:01:47
 * Purpose: Declaration of the class IeO
 ***********************************************************************/

#ifndef IEO_H
#define IEO_H

/*!
 * \file ieo.h
 * \brief Fichier du composant IeO
 * \author SALMON PAUL
 *         MONLOUIS Kevyn
 *         DUREUIL Brice
 * \version 1.0
 * \date 5 juin 2012
 */

#include <QVector>

#include "item.h"

/*! \class IeO
  * \brief Classe IeO :
  *
  *  Classe du composant IeO.
  */

class IeO : public Item
{

public:
    /*!
     *  \brief Constructeur.
     *  \param n : nombre de sortie
     *
     *  Constructeur de la classe IeO.
     */
    explicit IeO(int n);

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

#endif // IEO_H
