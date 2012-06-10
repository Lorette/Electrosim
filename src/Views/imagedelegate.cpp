/***********************************************************************
 * Module:  imagedelegate.cpp
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: mardi 15 mai 2012 00:54:23
 * Purpose: Implementation of the class ImageDelegate
 ***********************************************************************/

#include "imagedelegate.h"

#include <QMessageBox>

////////////////////////////////////////////////////////////////////////
// Name:       ImageDelegate::ImageDelegate(QObject * parent) : QStyledItemDelegate(parent)
// Purpose:    Implementation of ImageDelegate::ImageDelegate()
// Return:
////////////////////////////////////////////////////////////////////////

ImageDelegate::ImageDelegate(QObject * parent) : QStyledItemDelegate(parent) // Constructeur
{
}

////////////////////////////////////////////////////////////////////////
// Name:       QSize ImageDelegate::sizeHint(const QStyleOptionViewItem&, const QModelIndex&)
// Purpose:    Implementation of ImageDelegate::sizeHint()
// Return:     QSize
////////////////////////////////////////////////////////////////////////

QSize ImageDelegate::sizeHint(const QStyleOptionViewItem&, const QModelIndex&) const
{
    return QSize(50,50); // Taille des cases (50 pixels x 50 pixels)
}

////////////////////////////////////////////////////////////////////////
// Name:       void ImageDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index)
// Purpose:    Implementation of ImageDelegate::paint()
// Return:     void
////////////////////////////////////////////////////////////////////////

void ImageDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    QVariant decoration = index.data(Qt::DecorationRole); // Recupère une information pour l'affichage
    QVariant background = index.data(Qt::BackgroundRole); // Recupère une information pour l'arrière plan
    QVariant user1 = index.data(Qt::UserRole +1);
    QVariant user2 = index.data(Qt::UserRole +2);

    if(!background.isNull()) // Si c'est différent de NULL
        painter->fillRect(option.rect, QBrush(QColor(background.toString()))); // On colorie l'arrière plan de la case
    if(!decoration.isNull()) // Si c'est différent de NULL
        painter->drawPixmap(option.rect,QPixmap(decoration.toString())); // On affiche une image
    if(!user1.isNull())
        painter->drawText(option.rect.adjusted(5,5,6,6), user1.toString());
    if(!user2.isNull())
        painter->drawText(option.rect.adjusted(40,5,41,6), user2.toString());
}
