#include "gridmodel.h"


GridModel::GridModel(int rows, int columns) //Constructeur
{
    this->row_count = rows; // Nombre de lignes
    this->column_count = columns; // Nombre de colonnes
    this->current_modelIndex = QModelIndex(); // currentModelIndex a un faux index

    /* Initialis� avec son constructeur, QmodelIndex() sera faux ... il faut le cr�er avec createIndex */

    this->items.resize(this->row_count); // Redimensionne le tableau a la bonne longueur

    for(int i = 0; i < this->row_count; i++)
        this->items[i].resize(this->column_count); // ... ainsi que toutes les colonnes
}

QModelIndex GridModel::index(int row, int column, const QModelIndex &parent) const { // Cr�er un index correct avec les bonnes coorodnn�es
    QModelIndex index = this->createIndex(row,column);


   return index;
}

QModelIndex GridModel::parent(const QModelIndex &child) const { // Non utilis�, mais obligatoire
    QModelIndex index;

    return index;

}

int GridModel::rowCount(const QModelIndex &parent) const { // Retourne le nombre de ligne
    return this->row_count;
}

int GridModel::columnCount(const QModelIndex &parent) const { // Retourne le nombre de colonne
    return this->column_count;

}

QVariant GridModel::data(const QModelIndex &index, int role) const { // Retourne l'aspect d'un �l�ment du tableau (QVariant est un type non d�fini pouvant �tre tout et n'importe quoi)
    Item *c;

    if((role == Qt::DecorationRole) && ((c = this->items.at(index.row()).at(index.column())) != NULL)) // Si le role est l'affichage ...
        return c->getImage(); // ... on retourne le lien de l'image

    if(role == Qt::BackgroundRole && this->current_modelIndex.isValid() && index == this->current_modelIndex) { // Si le role est l'arri�re plan et que l'index est Valide et correspond � l'Index courant
        if(this->items.at(index.row()).at(index.column()) != NULL) // Si l'item � l'endroit existe bien
            return "#FF0000"; // On indique rouge
        else
            return "#00FF00"; // Sinon vert
    }

    if(role == Qt::ToolTipRole && ((c = this->items.at(index.row()).at(index.column())) != NULL)) // Plus ou moins fonctionnel
        return c->getDescription();

    if(role == (Qt::UserRole) && ((c = this->items.at(index.row()).at(index.column())) != NULL)) // Paul !!!!! @@@@@ Retourne qqch ...
        return c->getIndexOutputs();

    return QVariant();
}

bool GridModel::insertColumn(int column, const QModelIndex &parent) { // Insertion d'une colonne
    ++this->column_count;

    for(int i = 0; i < this->row_count; i++)
        this->items[i].resize(this->column_count);

    return true;
}

bool GridModel::insertRow(int row, const QModelIndex &parent) { // insertion d'une ligne
    ++this->row_count;

    this->items.resize(this->row_count);

    return true;
}

bool GridModel::insertColumns(int column, int count, const QModelIndex &parent) { // Insertion de plusieurs colonnes
    this->column_count += count;

    for(int i = 0; i < this->row_count; i++)
        this->items[i].resize(this->column_count);

    return true;
}

bool GridModel::insertRows(int row, int count, const QModelIndex &parent) { // Insertion de plusieurs lignes
    this->row_count += count;

    this->items.resize(this->row_count);

    return true;
}

Item* GridModel::at(const QModelIndex &index) { // Retourne l'�l�ment � l'index indiqu�
    if(index.row() < 0 || index.row() > this->row_count || index.column() < 0 || index.column() > this->column_count)
        return NULL;

    return this->items.at(index.row()).at(index.column());
}

bool GridModel::addItem(const QModelIndex &index, Item* item) { // Rajoute un item � l'index indiqu�
    this->items[index.row()][index.column()] = item;
    item->setIndex(index);

    return true;
}

bool GridModel::setData ( const QModelIndex & index, const QVariant & value, int role) { // Mauvaise utilisation mais obligatoire
    this->current_modelIndex = index;

    QModelIndex topleft = this->createIndex(0,0);
    QModelIndex bottomright = this->createIndex(this->row_count, this->column_count);

    emit dataChanged(topleft,bottomright); // Provoque une mise � jour compl�te de la grille
    return true;
}

bool GridModel::connexion(Item::s_connect* conn) { // Rajoute une connection � l'emetteur
    return conn->sender->addNext(conn);
}
