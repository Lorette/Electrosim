/***********************************************************************
 * Module:  gridview.h
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: samedi 12 mai 2012 18:37:49
 * Purpose: Declaration of the class GridView
 ***********************************************************************/

#ifndef GRIDVIEW_H
#define GRIDVIEW_H

/*!
 * \file gridview.h
 * \brief Vue
 * \author SALMON PAUL
 *         MONLOUIS Kevyn
 *         DUREUIL Brice
 * \version 1.0
 * \date 12 mai 2011
 */

#include <QTableView>
#include <QMouseEvent>
#include <QPainter>
#include <item.h>

/*! \class GridView
  * \brief Classe GridView :
  *
  *  Classe de la vue.
  */

class GridView : public QTableView
{
    Q_OBJECT
public:
    /*!
     *  \brief Constructeur.
     *
     *  Constructeur de la classe GridView.
     *  \param parent : widget parent
     */
    explicit GridView(QWidget *parent = 0);
    /*!
     *  \brief Crée un index.
     *  \param row : numéro de la ligne
     *  \param column : numéro de la colonne
     *  \param parent : index parent
     *
     *  \return l'index crée.
     */
    void enableTracking(bool enable);

private:
    bool tracking;

signals :
    void modelIndexChanged(const QModelIndex &index);

public slots:
    void mouseMoveEvent ( QMouseEvent * event );
    void paintEvent (QPaintEvent* event);
};

#endif // GRIDVIEW_H
