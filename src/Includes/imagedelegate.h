#ifndef IMAGEDELEGATE_H
#define IMAGEDELEGATE_H

#include <QStyledItemDelegate>
#include <QSize>
#include <QPixmap>
#include <QPainter>
#include <QTransform>


class ImageDelegate : public QStyledItemDelegate
{
public:
    ImageDelegate(QObject * parent = 0);

    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;
};

#endif // IMAGEDELEGATE_H
