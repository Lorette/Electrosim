#include "gridmodel.h"


GridModel::GridModel(int rows, int columns)
{
    this->row_count = rows;
    this->column_count = columns;
    this->current_modelIndex = QModelIndex();

    this->items.resize(this->row_count);

    for(int i = 0; i < this->row_count; i++)
        this->items[i].resize(this->column_count);
}

QModelIndex GridModel::index(int row, int column, const QModelIndex &parent) const {
    QModelIndex index = this->createIndex(row,column);


   return index;
}

QModelIndex GridModel::parent(const QModelIndex &child) const {
    QModelIndex index;

    return index;

}

int GridModel::rowCount(const QModelIndex &parent) const {
    return this->row_count;
}

int GridModel::columnCount(const QModelIndex &parent) const {
    return this->column_count;

}

QVariant GridModel::data(const QModelIndex &index, int role) const {
    Item *c;

    if((role == Qt::DecorationRole) && ((c = this->items.at(index.row()).at(index.column())) != NULL))
        return c->getImage();

    if(role == Qt::BackgroundRole && this->current_modelIndex.isValid() && index == this->current_modelIndex) {
        if(this->items.at(index.row()).at(index.column()) != NULL)
            return "#FF0000";
        else
            return "#00FF00";
    }

    if(role == Qt::ToolTipRole && ((c = this->items.at(index.row()).at(index.column())) != NULL))
        return c->getDescription();

    if(role == (Qt::UserRole) && ((c = this->items.at(index.row()).at(index.column())) != NULL))
        return c->getIndexOutputs();

    return QVariant();
}

bool GridModel::insertColumn(int column, const QModelIndex &parent) {
    ++this->column_count;

    for(int i = 0; i < this->row_count; i++)
        this->items[i].resize(this->column_count);

    return true;
}

bool GridModel::insertRow(int row, const QModelIndex &parent) {
    ++this->row_count;

    this->items.resize(this->row_count);

    return true;
}

bool GridModel::insertColumns(int column, int count, const QModelIndex &parent) {
    this->column_count += count;

    for(int i = 0; i < this->row_count; i++)
        this->items[i].resize(this->column_count);

    return true;
}

bool GridModel::insertRows(int row, int count, const QModelIndex &parent) {
    this->row_count += count;

    this->items.resize(this->row_count);

    return true;
}

Item* GridModel::at(const QModelIndex &index) {
    if(index.row() < 0 || index.row() > items.size() || index.column() < 0 || index.column() > items.at(0).size())
        return NULL;

    return this->items.at(index.row()).at(index.column());
}

bool GridModel::addItem(const QModelIndex &index, Item* item) {
    this->items[index.row()][index.column()] = item;
    item->setIndex(index);

    return true;
}

bool GridModel::setData ( const QModelIndex & index, const QVariant & value, int role) {
    this->current_modelIndex = index;

    QModelIndex topleft = this->createIndex(0,0);
    QModelIndex bottomright = this->createIndex(this->row_count, this->column_count);

    emit dataChanged(topleft,bottomright);
    return true;
}

bool GridModel::connexion(Item::s_connect* conn) {
    return conn->sender->addNext(conn);
}
