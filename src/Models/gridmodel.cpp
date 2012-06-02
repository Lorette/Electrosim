#include "gridmodel.h"

#include <QMessageBox>

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

    if(role == Qt::UserRole+1 && ((c = this->items.at(index.row()).at(index.column())) != NULL) && c->getClass() == Item::Input0)
        return c->getDefaultValue();

    if(role == Qt::UserRole+2 && ((c = this->items.at(index.row()).at(index.column())) != NULL) && c->getClass() == Item::Output1)
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

Item* GridModel::at(const QModelIndex &index) { // Retourne l'�l�ment � l'index indiqu�
    if(index.row() < 0 || index.row() > this->row_count || index.column() < 0 || index.column() > this->column_count)
        return NULL;

    return this->items.at(index.row()).at(index.column());
}

bool GridModel::addItem(const QModelIndex &index, Item* item) { // Rajoute un item � l'index indiqu�
    this->items[index.row()][index.column()] = item;

    if(item->getClass() == Item::Input0) {
        this->inputs << item;
        QObject::connect(this, SIGNAL(launch()), item, SLOT(recvSignal())); // On cr�e une connexion entre lui et le controlleur pour la simulation
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

    emit dataChanged(topleft,bottomright); // Provoque une mise � jour compl�te de la grille
    return true;
}

bool GridModel::connexion(Item::s_connect* conn) { // Rajoute une connection � l'emetteur
     if(!conn->sender->addNext(conn))
         return false;

     this->connexions << conn;
     conn->sender->recvSignal();
     return true;

}


bool GridModel::removeItem(const QModelIndex &index) { // Supprime un item � l'index indiqu�
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

bool GridModel::resetAllConnexions() { // R�initialise toutes les connexions
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
    int nb_lignes = qPow(2.0,nb_inputs); //nombre de lignes de la table de v�rit� = 2^(nombre d'entr�es)
    int nb_colonnes = nb_inputs+this->outputs.size(); //nombre de colonne = nombre d'entr�es + nombre de sorties

    //met les tableaux � la bonne taille
    resultat.first.resize(nb_colonnes); //il y a un nom de collonne pour chaque colonne.
    resultat.second.resize(nb_lignes);
    for(int i=0; i<nb_lignes; ++i)
        resultat.second[i].resize(nb_colonnes);

    //rempli la l�gende
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

    //rempli la partie des entr�es
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
        //initialise les entr�es
        i=0;
        for(QList<Item*>::iterator it = this->inputs.begin(); it != this->inputs.end(); ++it)
        {
            (*it)->setDefaultValue(resultat.second[l][i]); //initialise l'input num�ro i avec la valeur pr�sente dans la case (l,i)
            ++i;
        }

        //lance la simulation
        this->simulate();

        //r�cup�re les valeurs des sorties et rempli le tableau
        i=0;
        for(QList<Item*>::iterator it = this->outputs.begin(); it != this->outputs.end(); ++it)
        {
            resultat.second[l][nb_inputs+i] = (*it)->getDefaultValue();
            ++i;
        }
    }

    return resultat;
}

bool GridModel::setDefValueOnInput(Item *item, int value) {
    if(item == NULL)
        return false;

    if(item->getClass() != Item::Input0)
        return false;

    item->setDefaultValue(value);
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
                }

                out << i << "\t" << j << "\n";
            }

    //Liste des liaisons
    for( int i = 0 ; i < this->connexions.size() ; i++)
        out << "liaison\t" << this->connexions.at(i)->sender->getName() << "\t" <<  this->connexions.at(i)->output << "\t" <<  this->connexions.at(i)->receiver->getName() << "\t" <<  this->connexions.at(i)->input << "\n";

    return true;
}

bool GridModel::loadFromFile(QFile* file) {

    QMessageBox erreur;
    QTextStream stream(file);
    QString line;
    line = stream.readLine();
    if( line.isNull() )
    {
        erreur.setText("Erreur Fichier non valide.Le fichier n'est pas compatible.");
        erreur.exec();
        return false;
    }

    //on vide l'ancienne grille
    this->removeRows(0,this->rowCount());
    this->removeColumns(0,this->columnCount());

    //on vide les Lists
    this->inputs.clear();
    this->outputs.clear();
    this->connexions.clear();

    //on redimensionne la grille avec les valeurs du fichiers
    int n_row = line.toInt();
    line = stream.readLine();
    int n_column = line.toInt();

    this->insertRows(0, n_row);
    this->insertColumns(0, n_column);

    //on raffraichis l'affichage
    //this->setData( QModelIndex(), QVariant(), 0 );


    int i,j;

    line = stream.readLine();
    while( !line.isNull() )
    {
        //On s�pare la ligne en liste, le d�limiteur �tant la tabulation \t
        QStringList list = line.split("\t" , QString::SkipEmptyParts);

        //si on lit la premiere partie, le premier �l�ment de la liste est "composant"
        if( list[0] == "composant" )
        {
            // on prend les indices de lignes et de colonne (pareil tout composant confondu)
            i = list[3].toInt();
            j = list[4].toInt();
            if( list[2] == "IN" )
            {
                Input* in = new Input();
                in->setName( list[1] );
                addItem(this->createIndex(i,j), in);
            }
            else if( list[2] == "OUT" )
            {
                Output* out = new Output();
                out->setName( list[1] );
                addItem(this->createIndex(i,j), out);
            }
            else if( list[2] == "NOT" )
            {
                Not* no = new Not();
                no->setName( list[1] );
                addItem(this->createIndex(i,j), no);
            }
            else if( list[2] == "AND" )
            {
                And* et = new And();
                et->setName( list[1] );
                addItem(this->createIndex(i,j), et);
            }
            else if( list[2] == "OR" )
            {
                Or* ou = new Or();
                ou->setName( list[1] );
                addItem(this->createIndex(i,j), ou);
            }

        }

        //si le premier �l�ment n'est pas "composant" on voit les liaisons, par verification on rajoute le test
        else if( list[0] == "liaison" )
        {
            Item::s_connect *link = new Item::s_connect;
            link->sender = this->findChildByName( list[1] );
            link->output = (list[2]).toInt();
            link->receiver = this->findChildByName( list[3] );
            link->input = (list[4]).toInt();
            link->value = NULL;



            if( !this->connexion(link) )
            {
                erreur.setText("Liaison invalide detecter dans le fichier.\n Ligne: \n"+line);
                erreur.exec();
            }
        }

        line = stream.readLine();
    }

    //on raffraichis l'affichage
    this->setData( QModelIndex(), QVariant(), 0 );

    return true;


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
