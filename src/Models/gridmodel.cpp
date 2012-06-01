#include "gridmodel.h"

#include <QMessageBox>

GridModel::GridModel(int rows, int columns) //Constructeur
{
    this->row_count = rows; // Nombre de lignes
    this->column_count = columns; // Nombre de colonnes
    this->current_modelIndex = QModelIndex(); // currentModelIndex a un faux index

    /* Initialisé avec son constructeur, QmodelIndex() sera faux ... il faut le créer avec createIndex */

    this->items.resize(this->row_count); // Redimensionne le tableau a la bonne longueur

    for(int i = 0; i < this->row_count; i++)
        this->items[i].resize(this->column_count); // ... ainsi que toutes les colonnes
}

QModelIndex GridModel::index(int row, int column, const QModelIndex &parent) const { // Créer un index correct avec les bonnes coorodnnées
    QModelIndex index = this->createIndex(row,column);


   return index;
}

QModelIndex GridModel::parent(const QModelIndex &child) const { // Non utilisé, mais obligatoire
    QModelIndex index;

    return index;

}

int GridModel::rowCount(const QModelIndex &parent) const { // Retourne le nombre de ligne
    return this->row_count;
}

int GridModel::columnCount(const QModelIndex &parent) const { // Retourne le nombre de colonne
    return this->column_count;

}

QVariant GridModel::data(const QModelIndex &index, int role) const { // Retourne l'aspect d'un élément du tableau (QVariant est un type non défini pouvant être tout et n'importe quoi)
    Item *c;

    if((role == Qt::DecorationRole) && ((c = this->items.at(index.row()).at(index.column())) != NULL)) // Si le role est l'affichage ...
        return c->getImage(); // ... on retourne le lien de l'image

    if(role == Qt::BackgroundRole && this->current_modelIndex.isValid() && index == this->current_modelIndex) { // Si le role est l'arrière plan et que l'index est Valide et correspond à l'Index courant
        if(this->items.at(index.row()).at(index.column()) != NULL) // Si l'item à l'endroit existe bien
            return "#FF0000"; // On indique rouge
        else
            return "#00FF00"; // Sinon vert
    }

    if(role == Qt::ToolTipRole && ((c = this->items.at(index.row()).at(index.column())) != NULL)) // Plus ou moins fonctionnel
        return c->getDescription();

    if(role == (Qt::UserRole) && ((c = this->items.at(index.row()).at(index.column())) != NULL)) // Paul !!!!! @@@@@ Retourne qqch ...
        return c->getIndexOutputs();

    if(role == Qt::UserRole+1 && ((c = this->items.at(index.row()).at(index.column())) != NULL) && c->getClass() == Item::Input0)
        return c->getDefaultValue();

    return QVariant();
}

bool GridModel::insertColumn(int column, const QModelIndex &parent) { // Insertion d'une colonne
    this->beginInsertColumns(parent,this->column_count, this->column_count);

    for(int i = 0; i < this->row_count; i++)
        this->items[i].resize(this->column_count +1);


    this->endInsertColumns();

    ++this->column_count;

    return true;
}

bool GridModel::removeColumn(int column, const QModelIndex &parent) { // Suppression d'une colonne
    if(this->column_count == 0)
        return false;

    this->beginRemoveColumns(parent,this->column_count -1, this->column_count -1);

    for(int i = 0; i < this->row_count; i++) {
        if(this->items[i][this->column_count -1] != NULL)
            delete this->items[i][this->column_count -1];
        this->items[i].resize(this->column_count -1);
    }

    this->endRemoveColumns();

    --this->column_count;

    return true;
}

bool GridModel::insertRow(int row, const QModelIndex &parent) { // insertion d'une ligne
    this->beginInsertRows(parent, this->row_count, this->row_count);

    this->items.resize(this->row_count +1);
    this->items[this->row_count].resize(column_count);

    this->endInsertRows();

    ++this->row_count;

    return true;
}

bool GridModel::removeRow(int row, const QModelIndex &parent) { // Suppression d'une ligne
    if(this->row_count == 0)
        return false;

    this->beginRemoveRows(parent, this->row_count -1, this->row_count -1);

    for(int i = 0; i < this->column_count; i++)
        if(this->items[row_count -1][i] != NULL)
            delete this->items[row_count -1][i];
    this->items.resize(this->row_count -1);

    this->endRemoveRows();

    --this->row_count;

    return true;
}

bool GridModel::insertColumns(int column, int count, const QModelIndex &parent) { // Insertion de plusieurs colonnes
    if(count == 0)
        return false;

    this->beginInsertColumns(parent,this->column_count, this->column_count + count - 1);

    for(int i = 0; i < this->row_count; i++)
        this->items[i].resize(this->column_count + count);


    this->endInsertColumns();

    this->column_count += count;

    return true;
}

bool GridModel::removeColumns(int column, int count, const QModelIndex &parent) {
    if(this->column_count - count < 0 || count == 0)
        return false;

    this->beginRemoveColumns(parent,this->column_count - count, this->column_count - 1);

    for(int i = 0; i < this->row_count; i++) {
        for(int j = 0; j < count; j++)
            if(this->items[i][this->column_count -1 - j] != NULL)
                delete this->items[i][this->column_count -1 - j];
        this->items[i].resize(this->column_count -count);
    }

    this->endRemoveColumns();

    this->column_count -= count;

    return true;
}

bool GridModel::insertRows(int row, int count, const QModelIndex &parent) { // Insertion de plusieurs lignes
    if(count == 0)
        return false;

    this->beginInsertRows(parent, this->row_count, this->row_count + count - 1);

    this->items.resize(this->row_count + count);

    for(int i = 0; i < count; i++)
        this->items[this->row_count + i].resize(column_count);

    this->endInsertRows();

    this->row_count += count;

    return true;
}

bool GridModel::removeRows(int row, int count, const QModelIndex &parent) {
    if(this->row_count - count < 0 || count == 0)
        return false;

    this->beginRemoveRows(parent, this->row_count - count, this->row_count - 1);

    for(int i = 0; i < this->column_count; i++)
        for(int j = 0; j < count; j++)
        if(this->items[row_count -1 - j][i] != NULL)
            delete this->items[row_count -1 - j][i];
    this->items.resize(this->row_count - count);

    this->endRemoveRows();

    this->row_count -= count;

    return true;
}

Item* GridModel::at(const QModelIndex &index) { // Retourne l'élément à l'index indiqué
    if(index.row() < 0 || index.row() > this->row_count || index.column() < 0 || index.column() > this->column_count)
        return NULL;

    return this->items.at(index.row()).at(index.column());
}

bool GridModel::addItem(const QModelIndex &index, Item* item) { // Rajoute un item à l'index indiqué
    this->items[index.row()][index.column()] = item;

    if(item->getClass() == Item::Input0) {
        this->inputs << item;
        QObject::connect(this, SIGNAL(launch()), item, SLOT(recvSignal())); // On crée une connexion entre lui et le controlleur pour la simulation
    }

    if(item->getClass() == Item::Output1)
        this->outputs << item;

    item->setIndex(index);

    return true;
}

bool GridModel::setData ( const QModelIndex & index, const QVariant & value, int role) { // Mauvaise utilisation mais obligatoire
    this->current_modelIndex = index;

    QModelIndex topleft = this->createIndex(0,0);
    QModelIndex bottomright = this->createIndex(this->row_count, this->column_count);

    emit dataChanged(topleft,bottomright); // Provoque une mise à jour complète de la grille
    return true;
}

bool GridModel::connexion(Item::s_connect* conn) { // Rajoute une connection à l'emetteur
     if(!conn->sender->addNext(conn))
         return false;

     this->connexions << conn;

     return true;

}


bool GridModel::removeItem(const QModelIndex &index) { // Supprime un item à l'index indiqué
    Item *i = NULL;

    if(index.row() < 0 || index.row() > this->row_count || index.column() < 0 || index.column() > this->column_count || this->items.at(index.row()).at(index.column()) == NULL)
        return false;

    i = this->items[index.row()][index.column()];

    if(i->getClass() == Item::Input0)
        this->inputs.removeOne(i);
    if(i->getClass() == Item::Output1)
        this->outputs.removeOne(i);

    delete i;
    this->items[index.row()][index.column()] = NULL;

    return true;
}

bool GridModel::resetAllConnexions() { // Réinitialise toutes les connexions
    int n = this->connexions.size();

    for(int i = 0; i < n; i++)
        if(this->connexions.at(i) == NULL)
            this->connexions.removeAt(i);
        else
            this->connexions.at(i)->value = NULL;

    return true;

}

void GridModel::simulate() {
    this->resetAllConnexions();
    emit launch();
}

QPair < QVector < QString > , QVector< QVector < int > > > GridModel::verite() {
    QPair <QVector < QString >, QVector<QVector<int> > > resultat;
    int nb_inputs = this->inputs.size();
    int nb_lignes = pow(2.0,nb_inputs); //nombre de lignes de la table de vérité = 2^(nombre d'entrées)
    int nb_colonnes = nb_inputs+this->outputs.size(); //nombre de colonne = nombre d'entrées + nombre de sorties

    //met les tableaux à la bonne taille
    resultat.first.resize(nb_colonnes); //il y a un nom de collonne pour chaque colonne.
    resultat.second.resize(nb_lignes);
    for(int i=0; i<nb_lignes; ++i)
        resultat.second[i].resize(nb_colonnes);

    //rempli la légende
    int i=0;
    for(QList<Item*>::iterator it = this->inputs.begin(); it != this->inputs.end(); ++it)
    {
        resultat.first[i] = (*it)->getName();
        ++i;
    }
    for(QList<Item*>::iterator it = this->outputs.begin(); it != this->outputs.end(); ++it)
    {
        resultat.first[i] = (*it)->getName();
        ++i;
    }

    //rempli la partie des entrées
    for(int c=0; c<nb_inputs; ++c)
    {
        int n = pow(2.0,c); //calcul de 2^c
        int val = 1;
        for(int l=0; l<nb_lignes; ++l)
        {
            //toutes les 2^c lignes, on inverse val
            if(l%n == 0)
            {
                if(val == 0)
                    val = 1;
                else
                    val = 0;
            }

            //enregistre la valeur (val)
            resultat.second[l][c] = val;
        }
    }

    //pour chaque ligne, remplie la partie des sorties
    for(int l=0; l<nb_lignes; ++l)
    {
        //initialise les entrées
        i=0;
        for(QList<Item*>::iterator it = this->inputs.begin(); it != this->inputs.end(); ++it)
        {
            (*it)->setDefaultValue(resultat.second[l][i]); //initialise l'input numéro i avec la valeur présente dans la case (l,i)
            ++i;
        }

        //lance la simulation
        this->simulate();

        //récupère les valeurs des sorties et rempli le tableau
        i=0;
        for(QList<Item*>::iterator it = this->outputs.begin(); it != this->outputs.end(); ++it)
        {
            resultat.second[l][nb_inputs+i] = (*it)->getDefaultValue();
            ++i;
        }
    }

    return resultat;
}
