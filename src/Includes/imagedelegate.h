/***********************************************************************
 * Module:  imagedelegate.h
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: mardi 15 mai 2012 00:54:23
 * Purpose: Declaration of the class ImageDelegate
 ***********************************************************************/

#ifndef IMAGEDELEGATE_H
#define IMAGEDELEGATE_H

/*!
 * \file imageDelegate.h
 * \brief Fichier du delegue ImageDelegate
 * \author SALMON PAUL
 *         MONLOUIS Kevyn
 *         DUREUIL Brice
 * \version 1.0
 * \date 15 mai 2012
 */

#include <QStyledItemDelegate>
#include <QSize>
#include <QPixmap>
#include <QPainter>
#include <QTransform>

/*! \class ImageDelegate
  * \brief Classe ImageDelegate :
  *
  *  Classe du delegue ImageDelegate.
  */

class ImageDelegate : public QStyledItemDelegate
{
public:
    /*!
     *  \brief Constructeur.
     *
     *  Constructeur de la classe ImageDelegate.
     *  \param parent : objet parent
     */
    ImageDelegate(QObject * parent = 0);

    /*!
     *  \brief Fonction d'affichage d'une case de la grille.
     *  \param painter : Affichage
     *  \param option : options supplementaires
     *  \param index : position d'une case de la grille
     *
     */
    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;

    /*!
     *  \brief Fonction de determination de la taille d'une case.
     *  \param option : options supplementaires
     *  \param index : position d'une case de la grille
     *
     *  \return la taille de la case a afficher
     */
    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;
};

#endif // IMAGEDELEGATE_H
