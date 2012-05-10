#include "gridview.h"
#include <QMessageBox>
#include <QToolTip>

GridView::GridView(QWidget *parent) : QTableView(parent)
{
    this->setMouseTracking(true);
    this->tracking = false;

}


void GridView::mouseMoveEvent(QMouseEvent *event) {
    const QModelIndex index = this->indexAt(event->pos());

    if(this->tracking)
        this->model()->setData(index, 0);

}

void GridView::enableTracking(bool enable) {
    this->tracking = enable;

    this->model()->setData(QModelIndex(),0);
}

void GridView::paintEvent(QPaintEvent *event) {
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

            QVariant v = this->model()->data(index,Qt::UserRole + 1);
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
