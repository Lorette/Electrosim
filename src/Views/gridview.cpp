/***********************************************************************
 * Module:  gridview.cpp
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: samedi 12 mai 2012 18:37:49
 * Purpose: Implementation of the class GridView
 ***********************************************************************/

#include "gridview.h"

////////////////////////////////////////////////////////////////////////
// Name:       GridView::GridView(QWidget *parent) : QTableView(parent)
// Purpose:    Implementation of GridView::GridView()
// Return:
////////////////////////////////////////////////////////////////////////

GridView::GridView(QWidget *parent) : QTableView(parent) // Constructeur
{
    this->setMouseTracking(true); // Active la traque de la souris
    this->tracking = false; // Desactive le suivi de la souris pour MouseMoveEvent

}

////////////////////////////////////////////////////////////////////////
// Name:       void GridView::mouseMoveEvent(QMouseEvent *event)
// Purpose:    Implementation of GridView::mouseMoveEvent()
// Return:     void
////////////////////////////////////////////////////////////////////////

void GridView::mouseMoveEvent(QMouseEvent *event) { // Des que la souris bouge, cette fonction est appelee
    const QModelIndex index = this->indexAt(event->pos()); // Recupere l'index a la position de la souris

    if(this->tracking) // Si la suivi est activee
        this->model()->setData(index, 0); // On l'indique au modele

}

////////////////////////////////////////////////////////////////////////
// Name:       void GridView::enableTracking(bool enable)
// Purpose:    Implementation of GridView::enableTracking()
// Return:     void
////////////////////////////////////////////////////////////////////////

void GridView::enableTracking(bool enable) { // Active/desactive le suivi de la souris
    this->tracking = enable;

    this->model()->setData(QModelIndex(),0);
}

////////////////////////////////////////////////////////////////////////
// Name:       void GridView::paintEvent(QPaintEvent *event)
// Purpose:    Implementation of GridView::paintEvent()
// Return:     void
////////////////////////////////////////////////////////////////////////

void GridView::paintEvent(QPaintEvent *event) { // !!!!!!!!! @@@@@@@@@@@ Paul
    // call QTableView's paint event first so we can draw over it
    QTableView::paintEvent(event);
    QPen pen(Qt::black, 2);
    QPainter painter(viewport());
    painter.setPen(pen);

    for(int i=0; i<this->model()->rowCount(); ++i)
    {
        for(int j=0; j<this->model()->columnCount(); ++j)
        {
            QModelIndex index = this->model()->index(i,j);

            QVariant v = this->model()->data(index,Qt::UserRole);
            if(!v.isNull())
            {
                QList < QVariant > list = v.toList();

                int x1 = this->columnViewportPosition(index.column()) + 9*(this->columnWidth(index.column()))/10;
                int list_size = list.size();

                int n = 0;
                while(!list.isEmpty())
                {
                    int y1 = this->rowViewportPosition(index.row()) + (n+1)*(this->rowHeight(index.row()))/(list_size+1);

                    QVariant v2 = list.takeFirst();

                    if(!v2.isNull())
                    {
                        QLine index2 = v2.toLine();
                        int x2 = this->columnViewportPosition(index2.x1()) + (this->columnWidth(index2.x1()))/10;
                        int y2 = this->rowViewportPosition(index2.y1()) + (index2.x2()+1)*(this->rowHeight(index2.y2()))/(index2.y2() +1);

                        //dessiner la ligne
                        painter.drawLine(x1, y1, x2, y2);
                    }

                    ++n;
                }
            }
        }
    }
}
