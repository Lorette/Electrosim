#include "imagedelegate.h"

#include <QMessageBox>

ImageDelegate::ImageDelegate(QObject * parent) : QStyledItemDelegate(parent)
{
}

QSize ImageDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    return QSize(50,50);
}

void ImageDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{

    QVariant decoration = index.data(Qt::DecorationRole);
    QVariant background = index.data(Qt::BackgroundRole);
    QVariant rotation = index.data(Qt::UserRole);


    if(!background.isNull())
        painter->fillRect(option.rect, QBrush(QColor(background.toString())));
    if(!decoration.isNull()) {
        QTransform trans;
        QPixmap pix(decoration.toString());
        painter->drawPixmap(option.rect,pix.transformed(trans.rotate(rotation.toReal())));
    }
}
