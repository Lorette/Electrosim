#ifndef GRIDVIEW_H
#define GRIDVIEW_H

#include <QTableView>
#include <QMouseEvent>
#include <QPainter>


class GridView : public QTableView
{
    Q_OBJECT
public:
    explicit GridView(QWidget *parent = 0);
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
