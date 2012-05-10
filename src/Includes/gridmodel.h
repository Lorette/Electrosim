#ifndef GRIDMODEL_H
#define GRIDMODEL_H

#include <QAbstractItemModel>
#include <QVector>
#include <QMessageBox>
#include <QIcon>
#include "item.h"

class GridModel : public QAbstractItemModel
{

public:
    explicit GridModel(int rows = 0, int columns = 0);
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);

    bool insertColumn(int column, const QModelIndex &parent = QModelIndex());
    bool insertRow(int row, const QModelIndex &parent = QModelIndex());
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex());
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());

    Item* at(const QModelIndex &index);
    bool addItem(const QModelIndex &index, Item* item);
    bool connexion(Item::s_connect* conn);

private :
    int column_count;
    int row_count;
    QVector< QVector<Item*> > items;
    QModelIndex current_modelIndex;

};

#endif // GRIDMODEL_H
