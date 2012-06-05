#include "imagedelegate.h"

#include <QMessageBox>

ImageDelegate::ImageDelegate(QObject * parent) : QStyledItemDelegate(parent) // Constructeur
{
}

ImageDelegate::~ImageDelegate()
{
}

QSize ImageDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    return QSize(50,50); // Taille des cases (50 pixels x 50 pixels)
}

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
