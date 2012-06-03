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

GridModel::~GridModel() {
// A IMPLEMENTER :: tout détruire !!
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
        return c->getAuxValue();

    if(role == Qt::UserRole+2 && ((c = this->items.at(index.row()).at(index.column())) != NULL) && c->getClass() == Item::Output1)
        return c->getAuxValue();

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
    if(!item)
        return false;

    //vérification qu'il ny a pas déjà un composant à cet emplacement
    if(this->items[index.row()][index.column()])
        return false;

    //Vérification du nom
    if(!(this->nameIsCorrect(item->getName())))
        return false;

    //ajout de l'objet
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
     conn->sender->recvSignal();
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
        {
            delete (this->connexions.at(i)->value); //on l'alloue avec new dans les différents composants, il faut le delete
            this->connexions.at(i)->value = NULL;
        }

    return true;

}

void GridModel::simulate() {
    this->resetAllConnexions();
    //initialise les sorties à -1 (-1 signifie que la valeur est inconnu car le circuit n'est pas complet)
    for(QList<Item*>::iterator it = this->outputs.begin(); it != this->outputs.end(); ++it)
        (*it)->setAuxValue(-1);
    emit launch();
}

QPair < QVector < QString > , QVector< QVector < int > > > GridModel::verite() {
    QPair <QVector < QString >, QVector<QVector<int> > > resultat;
    int nb_inputs = this->inputs.size();
    int nb_lignes = qPow(2.0,nb_inputs); //nombre de lignes de la table de vérité = 2^(nombre d'entrées)
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
        int n = qPow(2.0,c); //calcul de 2^c
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
            (*it)->setAuxValue(resultat.second[l][i]); //initialise l'input numéro i avec la valeur présente dans la case (l,i)
            ++i;
        }

        //lance la simulation
        this->simulate();

        //récupère les valeurs des sorties et rempli le tableau
        i=0;
        for(QList<Item*>::iterator it = this->outputs.begin(); it != this->outputs.end(); ++it)
        {
            resultat.second[l][nb_inputs+i] = (*it)->getAuxValue();
            ++i;
        }
    }

    return resultat;
}

bool GridModel::setDefValueOnInput(Item *item, int value) {
    if(item == NULL)
        return false;

    if(item->getClass() != Item::Input0 && item->getClass() != Item::Mux5)
        return false;

    item->setAuxValue(value);
    item->recvSignal();

    return true;
}

bool GridModel::saveInFile(QFile* file){

    QTextStream out(file);

    // ajout du nombre de lignes et de colonnes sur les 2 premieres lignes du fichier
    out << this->row_count << "\n";
    out << this->column_count << "\n";

    for(int i = 0 ; i < this->row_count ; i++)
        for(int j = 0 ; j < this->column_count ; j++)
          if(this->items.at(i).at(j) != NULL) {
                out << "composant\t" << this->items.at(i).at(j)->getName();

                switch (this->items.at(i).at(j)->getClass()) {
                case Item::Input0 :  out << "\tIN\t";
                    break;
                case Item::Output1 : out << "\tOUT\t";
                    break;
                case Item::Not2 : out << "\tNOT\t";
                    break;
                case Item::Or3 : out << "\tOR\t";
                    break;
                case Item::And4 : out << "\tAND\t";
                    break;
                case Item::Mux5 : out << "\tMUX\t";
                    break;
                }

                out << i << "\t" << j << "\t" << this->items.at(i).at(j)->getAuxValue() << "\n";
            }

    //Liste des liaisons
    for( int i = 0 ; i < this->connexions.size() ; i++)
        out << "liaison\t" << this->connexions.at(i)->sender->getName() << "\t" <<  this->connexions.at(i)->output << "\t" <<  this->connexions.at(i)->receiver->getName() << "\t" <<  this->connexions.at(i)->input << "\n";

    return true;
}

GridModel* GridModel::loadFromFile(QFile* file) {
    GridModel *model;
    QTextStream stream(file);
    QString line;
    line = stream.readLine();

    if( line.isNull() )
        return NULL;

    //on redimensionne la grille avec les valeurs du fichiers
    int n_row = line.toInt();
    line = stream.readLine();
    int n_column = line.toInt();

    model = new GridModel(n_row, n_column);

    int i,j;

    line = stream.readLine();
    while( !line.isNull() )
    {
        //On sépare la ligne en liste, le délimiteur étant la tabulation \t
        QStringList list = line.split("\t" , QString::SkipEmptyParts);

        //si on lit la premiere partie, le premier élément de la liste est "composant"
        if( list[0] == "composant" )
        {
            // on prend les indices de lignes et de colonne (pareil tout composant confondu)
            i = list[3].toInt();
            j = list[4].toInt();
            if( list[2] == "IN" )
            {
                Input* in = new Input();
                in->setName( list[1] );
                in->setAuxValue(list[5].toInt());
                if(!model->addItem(model->createIndex(i,j), in))
                    return NULL;
            }
            else if( list[2] == "OUT" )
            {
                Output* out = new Output();
                out->setName( list[1] );
                if(!model->addItem(model->createIndex(i,j), out))
                    return NULL;
            }
            else if( list[2] == "NOT" )
            {
                Not* no = new Not();
                no->setName( list[1] );
                if(!model->addItem(model->createIndex(i,j), no))
                    return NULL;
            }
            else if( list[2] == "AND" )
            {
                And* et = new And();
                et->setName( list[1] );
                if(!model->addItem(model->createIndex(i,j), et))
                    return NULL;
            }
            else if( list[2] == "OR" )
            {
                Or* ou = new Or();
                ou->setName( list[1] );
                if(!model->addItem(model->createIndex(i,j), ou))
                    return NULL;
            }
            else if( list[2] == "MUX" )
            {
                Multiplexer* mux = new Multiplexer(list[5].toInt());
                mux->setName( list[1] );
                if(!model->addItem(model->createIndex(i,j), mux))
                    return NULL;
            }
        }

        //si le premier élément n'est pas "composant" on voit les liaisons, par verification on rajoute le test
        else if( list[0] == "liaison" )
        {
            Item::s_connect *link = new Item::s_connect;
            link->sender = model->findChildByName( list[1] );
            link->output = (list[2]).toInt();
            link->receiver = model->findChildByName( list[3] );
            link->input = (list[4]).toInt();
            link->value = NULL;



            if( !model->connexion(link) )
                return NULL;
        }

        line = stream.readLine();
    }

    return model;


}

Item* GridModel::findChildByName(QString name)
{
    for( int i = 0 ; i < this->row_count ; i++)
    {
        for( int j = 0 ; j < this->column_count ; j++)
        {
            if( this->items[i][j] != NULL && this->items[i][j]->getName() == name)
            {
                return items[i][j];
            }
        }
    }

    return NULL;

}

bool GridModel::nameIsCorrect(const QString& name) const
{
    //vérifie qu'il n'y a pas d'espace
    if(name.contains(" ") || name.contains("\t"))
        return false;

    //vérifie si le nom est aps déjà utilisé
    for(int r=0; r<this->rowCount(); ++r)
    {
        for(int c=0; c<this->columnCount(); ++c)
        {
            if(this->items[r][c])
            {
                if(this->items[r][c]->getName() == name)
                    return false;
            }
        }
    }

    return true;
}
