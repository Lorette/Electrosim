/***********************************************************************
 * Module:  node.h
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: mardi 5 juin 2012 15:01:47
 * Purpose: Declaration of the class Node
 ***********************************************************************/

#ifndef NODE_H
#define NODE_H

/*!
 * \file node.h
 * \brief Fichier du composant Node
 * \author SALMON PAUL
 *         MONLOUIS Kevyn
 *         DUREUIL Brice
 * \version 1.0
 * \date 5 juin 2012
 */

#include <QVector>

#include "item.h"

/*! \class Node
  * \brief Classe Node :
  *
  *  Classe du composant Node.
  *  Un node est un composant qui envoie son entree sur toutes ses sorties.
  *  Son nombre de sortie est changeable et est defini par la valeur de aux.
  */

class Node : public Item
{

public:
    /*!
     *  \brief Constructeur.
     *  \param n : nombre de sortie
     *
     *  Constructeur de la classe Node.
     */
    explicit Node(int n);

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

#endif // NODE_H
