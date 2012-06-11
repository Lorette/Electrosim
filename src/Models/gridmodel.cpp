/***********************************************************************
 * Module:  gridmodel.cpp
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: samedi 12 mai 2012 17:15:14
 * Purpose: Implementation of the class GridModel
 ***********************************************************************/

#include "gridmodel.h"

////////////////////////////////////////////////////////////////////////
// Name:       GridModel::GridModel(int rows, int columns)
// Purpose:    Implementation of GridModel::GridModel()
// Return:
////////////////////////////////////////////////////////////////////////

GridModel::GridModel(int rows, int columns) //Constructeur
{
    this->row_count = rows; // Nombre de lignes
    this->column_count = columns; // Nombre de colonnes
    this->current_modelIndex = QModelIndex(); // currentModelIndex a un faux index

    /* Initialise avec son constructeur, QmodelIndex() sera faux ... il faut le creer avec createIndex */

    this->items.resize(this->row_count); // Redimensionne le tableau a la bonne longueur

    for(int i = 0; i < this->row_count; i++)
        this->items[i].resize(this->column_count); // ... ainsi que toutes les colonnes
}

////////////////////////////////////////////////////////////////////////
// Name:       GridModel::~GridModel()
// Purpose:    Implementation of GridModel::~GridModel()
// Return:
////////////////////////////////////////////////////////////////////////

GridModel::~GridModel() {
    for(int i = 0; i < this->row_count; i++)
        for(int j = 0; j < this->column_count; j++)
            this->removeItem(this->index(i,j));
}

////////////////////////////////////////////////////////////////////////
// Name:       QModelIndex GridModel::index(int row, int column, const QModelIndex&)
// Purpose:    Implementation of QModelIndex GridModel::index()
// Return:     QModelIndex
////////////////////////////////////////////////////////////////////////

QModelIndex GridModel::index(int row, int column, const QModelIndex&) const { // Creer un index correct avec les bonnes coorodnnees
    QModelIndex index = this->createIndex(row,column);


   return index;
}

////////////////////////////////////////////////////////////////////////
// Name:       QModelIndex GridModel::parent(const QModelIndex&)
// Purpose:    Implementation of GridModel::parent()
// Return:     QModelIndex
////////////////////////////////////////////////////////////////////////

QModelIndex GridModel::parent(const QModelIndex&) const { // Non utilise, mais obligatoire
    QModelIndex index;

    return index;

}

////////////////////////////////////////////////////////////////////////
// Name:       int GridModel::rowCount(const QModelIndex&)
// Purpose:    Implementation of GridModel::rowCount()
// Return:     int
////////////////////////////////////////////////////////////////////////

int GridModel::rowCount(const QModelIndex&) const { // Retourne le nombre de ligne
    return this->row_count;
}

////////////////////////////////////////////////////////////////////////
// Name:       int GridModel::columnCount(const QModelIndex&)
// Purpose:    Implementation of GridModel::columnCount()
// Return:     int
////////////////////////////////////////////////////////////////////////

int GridModel::columnCount(const QModelIndex&) const { // Retourne le nombre de colonne
    return this->column_count;

}

////////////////////////////////////////////////////////////////////////
// Name:       QVariant GridModel::data(const QModelIndex &index, int role)
// Purpose:    Implementation of GridModel::data()
// Return:     QVariant
////////////////////////////////////////////////////////////////////////

QVariant GridModel::data(const QModelIndex &index, int role) const { // Retourne l'aspect d'un element du tableau (QVariant est un type non defini pouvant etre tout et n'importe quoi)
    Item *c;

    if((role == Qt::DecorationRole) && ((c = this->items.at(index.row()).at(index.column())) != NULL)) // Si le role est l'affichage ...
        return c->getImage(); // ... on retourne le lien de l'image

    if(role == Qt::BackgroundRole && this->current_modelIndex.isValid() && index == this->current_modelIndex) { // Si le role est l'arriere plan et que l'index est Valide et correspond a l'Index courant
        if(this->items.at(index.row()).at(index.column()) != NULL) // Si l'item a l'endroit existe bien
            return "#FF0000"; // On indique rouge
        else
            return "#00FF00"; // Sinon vert
    }

    if(role == Qt::ToolTipRole && ((c = this->items.at(index.row()).at(index.column())) != NULL)) // Plus ou moins fonctionnel
        return c->getName();

    if(role == Qt::UserRole && ((c = this->items.at(index.row()).at(index.column())) != NULL)) // Paul !!!!! @@@@@ Retourne qqch ...
        return getConnexions(c);

    if(role == Qt::UserRole+1 && ((c = this->items.at(index.row()).at(index.column())) != NULL) && c->getClass() == Item::Input)
        return c->getAuxValue();

    if(role == Qt::UserRole+2 && ((c = this->items.at(index.row()).at(index.column())) != NULL) && c->getClass() == Item::Output)
        return c->getAuxValue();

    return QVariant();
}

////////////////////////////////////////////////////////////////////////
// Name:       bool GridModel::insertColumn(int, const QModelIndex &parent)
// Purpose:    Implementation of GridModel::insertColumn()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool GridModel::insertColumn(int, const QModelIndex &parent) { // Insertion d'une colonne
    this->beginInsertColumns(parent,this->column_count, this->column_count);

    for(int i = 0; i < this->row_count; i++)
        this->items[i].resize(this->column_count +1);


    this->endInsertColumns();

    ++this->column_count;

    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       bool GridModel::removeColumn(int, const QModelIndex &parent)
// Purpose:    Implementation of GridModel::removeColumn()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool GridModel::removeColumn(int, const QModelIndex &parent) { // Suppression d'une colonne
    if(this->column_count == 0)
        return false;

    this->beginRemoveColumns(parent,this->column_count -1, this->column_count -1);

    for(int i = 0; i < this->row_count; i++) {
        if(this->items[i][this->column_count -1] != NULL) {
            QModelIndex in = this->index(i,this->column_count -1);
            this->removeItem(in);
        }
        this->items[i].resize(this->column_count -1);
    }

    this->endRemoveColumns();

    --this->column_count;

    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       bool GridModel::insertRow(int, const QModelIndex &parent)
// Purpose:    Implementation of GridModel::insertRow()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool GridModel::insertRow(int, const QModelIndex &parent) { // insertion d'une ligne
    this->beginInsertRows(parent, this->row_count, this->row_count);

    this->items.resize(this->row_count +1);
    this->items[this->row_count].resize(column_count);

    this->endInsertRows();

    ++this->row_count;

    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       bool GridModel::removeRow(int, const QModelIndex &parent)
// Purpose:    Implementation of GridModel::removeRow()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool GridModel::removeRow(int, const QModelIndex &parent) { // Suppression d'une ligne
    if(this->row_count == 0)
        return false;

    this->beginRemoveRows(parent, this->row_count -1, this->row_count -1);

    for(int i = 0; i < this->column_count; i++) {
        if(this->items[row_count -1][i] != NULL) {
            QModelIndex in = this->index(row_count -1,i);
            this->removeItem(in);
        }
    }
    this->items.resize(this->row_count -1);

    this->endRemoveRows();

    --this->row_count;

    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       bool GridModel::insertColumns(int, int count, const QModelIndex &parent)
// Purpose:    Implementation of GridModel::insertColumns()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool GridModel::insertColumns(int, int count, const QModelIndex &parent) { // Insertion de plusieurs colonnes
    if(count == 0)
        return false;

    this->beginInsertColumns(parent,this->column_count, this->column_count + count - 1);

    for(int i = 0; i < this->row_count; i++)
        this->items[i].resize(this->column_count + count);


    this->endInsertColumns();

    this->column_count += count;

    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       bool GridModel::removeColumns(int, int count, const QModelIndex &parent)
// Purpose:    Implementation of GridModel::removeColumns()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool GridModel::removeColumns(int, int count, const QModelIndex &parent) {
    if(this->column_count - count < 0 || count == 0)
        return false;

    this->beginRemoveColumns(parent,this->column_count - count, this->column_count - 1);

    for(int i = 0; i < this->row_count; i++) {
        for(int j = 0; j < count; j++) {
            if(this->items[i][this->column_count -1 - j] != NULL) {
                QModelIndex in = this->index(i,this->column_count -1 - j);
                this->removeItem(in);
            }
        }
        this->items[i].resize(this->column_count -count);
    }

    this->endRemoveColumns();

    this->column_count -= count;

    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       bool GridModel::insertRows(int, int count, const QModelIndex &parent)
// Purpose:    Implementation of GridModel::insertRows()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool GridModel::insertRows(int, int count, const QModelIndex &parent) { // Insertion de plusieurs lignes
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

////////////////////////////////////////////////////////////////////////
// Name:       bool GridModel::removeRows(int, int count, const QModelIndex &parent)
// Purpose:    Implementation of GridModel::removeRows()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool GridModel::removeRows(int, int count, const QModelIndex &parent) {
    if(this->row_count - count < 0 || count == 0)
        return false;

    this->beginRemoveRows(parent, this->row_count - count, this->row_count - 1);

    for(int i = 0; i < this->column_count; i++) {
        for(int j = 0; j < count; j++) {
            if(this->items[row_count -1 - j][i] != NULL) {
                QModelIndex in = this->index(row_count -1 - j,i);
                this->removeItem(in);
            }
        }
    }
    this->items.resize(this->row_count - count);

    this->endRemoveRows();

    this->row_count -= count;

    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       Item* GridModel::at(const QModelIndex &index)
// Purpose:    Implementation of GridModel::at()
// Return:     Item*
////////////////////////////////////////////////////////////////////////

Item* GridModel::at(const QModelIndex &index) { // Retourne l'element a l'index indique
    if(index.row() < 0 || index.row() > this->row_count || index.column() < 0 || index.column() > this->column_count)
        return NULL;

    return this->items.at(index.row()).at(index.column());
}

////////////////////////////////////////////////////////////////////////
// Name:       bool GridModel::addItem(const QModelIndex &index, Item* item)
// Purpose:    Implementation of GridModel::addItem()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool GridModel::addItem(const QModelIndex &index, Item* item) { // Rajoute un item a l'index indique
    if(!item)
        return false;

    //verification qu'il ny a pas deja un composant a cet emplacement
    if(this->items[index.row()][index.column()])
        return false;

    //Verification du nom
    if(!(this->nameIsCorrect(item->getName())))
        return false;

    //ajout de l'objet
    this->items[index.row()][index.column()] = item;

    if(item->getClass() == Item::Input) {
        this->inputs << item;
        QObject::connect(this, SIGNAL(launch()), item, SLOT(recvSignal())); // On cree une connexion entre lui et le controlleur pour la simulation
    }

    if(item->getClass() == Item::Output)
        this->outputs << item;

    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       bool GridModel::setData ( const QModelIndex & index, const QVariant&, int)
// Purpose:    Implementation of GridModel::setData()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool GridModel::setData ( const QModelIndex & index, const QVariant&, int) { // Mauvaise utilisation mais obligatoire
    this->current_modelIndex = index;

    QModelIndex topleft = this->createIndex(0,0);
    QModelIndex bottomright = this->createIndex(this->row_count, this->column_count);

    emit dataChanged(topleft,bottomright); // Provoque une mise a jour complete de la grille
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       bool GridModel::connexion(Item::s_connect* conn)
// Purpose:    Implementation of GridModel::connexion()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool GridModel::connexion(Item::s_connect* conn) { // Rajoute une connection a l'emetteur
     if(!conn->sender->addNext(conn))
         return false;

     this->connexions << conn;
     QObject::connect(conn->sender, SIGNAL(sendSignal()), conn->receiver, SLOT(recvSignal()));
     conn->sender->recvSignal();
     return true;

}

////////////////////////////////////////////////////////////////////////
// Name:       bool GridModel::removeItem(const QModelIndex &index)
// Purpose:    Implementation of GridModel::removeItem()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool GridModel::removeItem(const QModelIndex &index) { // Supprime un item a l'index indique
    Item *it = NULL;

    if(index.row() < 0 || index.row() > this->row_count || index.column() < 0 || index.column() > this->column_count || this->items.at(index.row()).at(index.column()) == NULL)
        return false;

    it = this->items[index.row()][index.column()];
    QVector<Item::s_connect *> i_inputs = it->getInputs();
    QVector<Item::s_connect *> i_outputs = it->getOutputs();

    if(it->getClass() == Item::Input)
        this->inputs.removeOne(it);
    if(it->getClass() == Item::Output)
        this->outputs.removeOne(it);

    for(int i = 0; i < i_inputs.size(); i++)
        this->removeConnexion(i_inputs.at(i));

    for(int i = 0; i < i_outputs.size(); i++)
        this->removeConnexion(i_outputs.at(i));

    delete it;
    this->items[index.row()][index.column()] = NULL;

    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       bool GridModel::resetAllConnexions()
// Purpose:    Implementation of GridModel::resetAllConnexions()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool GridModel::resetAllConnexions() { // Reinitialise toutes les connexions
    int n = this->connexions.size();

    for(int i = 0; i < n; i++)
        if(this->connexions.at(i) == NULL)
            this->connexions.removeAt(i);
        else
        {
            delete (this->connexions.at(i)->value); //on l'alloue avec new dans les differents composants, il faut le delete
            this->connexions.at(i)->value = NULL;
        }

    return true;

}

////////////////////////////////////////////////////////////////////////
// Name:       void GridModel::simulate()
// Purpose:    Implementation of GridModel::simulate()
// Return:     void
////////////////////////////////////////////////////////////////////////

void GridModel::simulate() {
    this->resetAllConnexions();
    //initialise les sorties a -1 (-1 signifie que la valeur est inconnu car le circuit n'est pas complet)
    for(QList<Item*>::iterator it = this->outputs.begin(); it != this->outputs.end(); ++it)
        (*it)->setAuxValue(-1);
    emit launch();
}

////////////////////////////////////////////////////////////////////////
// Name:       QPair < QVector < QString > , QVector< QVector < int > > > GridModel::verite()
// Purpose:    Implementation of GridModel::verite()
// Return:     QPair < QVector < QString > , QVector< QVector < int > > >
////////////////////////////////////////////////////////////////////////

QPair < QVector < QString > , QVector< QVector < int > > > GridModel::verite() {
    QPair <QVector < QString >, QVector<QVector<int> > > resultat;
    int nb_inputs = this->inputs.size();
    int nb_lignes = qPow(2.0,nb_inputs); //nombre de lignes de la table de verite = 2^(nombre d'entrees)
    int nb_colonnes = nb_inputs+this->outputs.size(); //nombre de colonne = nombre d'entrees + nombre de sorties
    QVector<int> save; //Pour sauvegarder l'etat actuel des inputs

    //met les tableaux a la bonne taille
    save.resize(this->inputs.size());
    resultat.first.resize(nb_colonnes); //il y a un nom de collonne pour chaque colonne.
    resultat.second.resize(nb_lignes);
    for(int i=0; i<nb_lignes; ++i)
        resultat.second[i].resize(nb_colonnes);

    //rempli la legende
    int i=0;
    for(QList<Item*>::iterator it = this->inputs.begin(); it != this->inputs.end(); ++it)
    {
        resultat.first[i] = (*it)->getName();
        save[i] = (*it)->getAuxValue(); //sauvegarde la valeur actuelle
        ++i;
    }
    for(QList<Item*>::iterator it = this->outputs.begin(); it != this->outputs.end(); ++it)
    {
        resultat.first[i] = (*it)->getName();
        ++i;
    }

    //rempli la partie des entrees
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
        //initialise les entrees
        i=0;
        for(QList<Item*>::iterator it = this->inputs.begin(); it != this->inputs.end(); ++it)
        {
            (*it)->setAuxValue(resultat.second[l][i]); //initialise l'input numero i avec la valeur presente dans la case (l,i)
            ++i;
        }

        //lance la simulation
        this->simulate();

        //recupere les valeurs des sorties et rempli le tableau
        i=0;
        for(QList<Item*>::iterator it = this->outputs.begin(); it != this->outputs.end(); ++it)
        {
            resultat.second[l][nb_inputs+i] = (*it)->getAuxValue();
            ++i;
        }
    }

    //Charge l'etat des inputs avant la fonction
    i=0;
    for(QList<Item*>::iterator it = this->inputs.begin(); it != this->inputs.end(); ++it)
    {
        (*it)->setAuxValue(save[i]);
        ++i;
    }
    //relance la simulation pour actualiser les sorties
    this->simulate();

    return resultat;
}

////////////////////////////////////////////////////////////////////////
// Name:       bool GridModel::setDefValueOnInput(Item *item, int value)
// Purpose:    Implementation of GridModel::setDefValueOnInput()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool GridModel::setDefValueOnInput(Item *item, int value) {
    if(item == NULL)
        return false;

    if(item->getClass() != Item::Input && item->getClass() != Item::Mux && item->getClass() != Item::Demux && item->getClass() != Item::IeO)
        return false;

    item->setAuxValue(value);
    item->recvSignal();

    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       bool GridModel::saveInFile(QFile* file)
// Purpose:    Implementation of GridModel::saveInFile()
// Return:     bool
////////////////////////////////////////////////////////////////////////

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
                case Item::Input :  out << "\tIN\t";
                    break;
                case Item::Output : out << "\tOUT\t";
                    break;
                case Item::Not : out << "\tNOT\t";
                    break;
                case Item::Or : out << "\tOR\t";
                    break;
                case Item::Xor : out << "\tXOR\t";
                    break;
                case Item::XNOr : out << "\tXNOR\t";
                    break;
                case Item::And : out << "\tAND\t";
                    break;
                case Item::Mux : out << "\tMUX\t";
                    break;
                case Item::Demux : out << "\tDEMUX\t";
                    break;
                case Item::IeO : out << "\tIEO\t";
                    break;

                }

                out << i << "\t" << j << "\t" << QString::number(this->items.at(i).at(j)->getAuxValue()) << "\n";
            }

    //Liste des liaisons
    for( int i = 0 ; i < this->connexions.size() ; i++)
        out << "liaison\t" << this->connexions.at(i)->sender->getName() << "\t" <<  this->connexions.at(i)->output << "\t" <<  this->connexions.at(i)->receiver->getName() << "\t" <<  this->connexions.at(i)->input << "\n";

    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       GridModel* GridModel::loadFromFile(QFile* file)
// Purpose:    Implementation of GridModel::loadFromFile()
// Return:     GridModel*
////////////////////////////////////////////////////////////////////////

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
        //On separe la ligne en liste, le delimiteur etant la tabulation \t
        QStringList list = line.split("\t" , QString::SkipEmptyParts);

        //si on lit la premiere partie, le premier element de la liste est "composant"
        if( list.size() > 0 && list[0] == "composant" )
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
            else if( list[2] == "DEMUX" )
            {
                Demultiplexer* demux = new Demultiplexer(list[5].toInt());
                demux->setName( list[1] );
                if(!model->addItem(model->createIndex(i,j), demux))
                    return NULL;
            }
            else if( list[2] == "XNOR")
            {
                XNOr* xnor = new XNOr();
                xnor->setName(list[1]);
                if(!model->addItem(model->createIndex(i,j), xnor))
                    return NULL;
            }
            else if( list[2] == "IEO")
            {
                IeO* ieo = new IeO(list[5].toInt());
                ieo->setName(list[1]);
                if(!model->addItem(model->createIndex(i,j), ieo))
                    return NULL;
            }
            else if( list[2] == "XOR")
            {
                Xor* ou_ex = new Xor();
                ou_ex->setName(list[1]);
                if(!model->addItem(model->createIndex(i,j), ou_ex))
                    return NULL;
            }


        }

        //si le premier element n'est pas "composant" on voit les liaisons, par verification on rajoute le test
        else if( list.size() > 0 &&  list[0] == "liaison" )
        {
            Item::s_connect *link = new Item::s_connect;
            link->sender = model->findChildByName( list[1] );
            link->output = (list[2]).toInt();
            link->receiver = model->findChildByName( list[3] );
            link->input = (list[4]).toInt();
            link->value = NULL;

            //si l'un des composants de la liaison existe pas on annule le chargement
            if( link->sender == NULL || link->receiver == NULL )
                return NULL;

            if( !model->connexion(link) )
                return NULL;
        }

        line = stream.readLine();
    }

    return model;


}

////////////////////////////////////////////////////////////////////////
// Name:       Item* GridModel::findChildByName(QString name)
// Purpose:    Implementation of GridModel::findChildByName()
// Return:     Item*
////////////////////////////////////////////////////////////////////////

Item* GridModel::findChildByName(QString name)
{
    for( int i = 0 ; i < this->row_count ; i++)
        for( int j = 0 ; j < this->column_count ; j++)
            if( this->items[i][j] != NULL && this->items[i][j]->getName() == name)
                return items[i][j];

    return NULL;

}

////////////////////////////////////////////////////////////////////////
// Name:       bool GridModel::nameIsCorrect(const QString& name)
// Purpose:    Implementation of GridModel::nameIsCorrect()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool GridModel::nameIsCorrect(const QString& name) const
{
    //verifie qu'il n'y a pas d'espace
    if(name.contains(" ") || name.contains("\t"))
        return false;

    //verifie si le nom est aps deja utilise
    for(int r=0; r<this->rowCount(); ++r)
        for(int c=0; c<this->columnCount(); ++c)
            if(this->items[r][c] && this->items[r][c]->getName() == name)
                    return false;
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       bool GridModel::removeConnexion()
// Purpose:    Implementation of GridModel::removeConnexion()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool GridModel::removeConnexion(Item::s_connect *conn) {
    if(conn == NULL || conn->sender == NULL || conn->receiver == NULL)
        return false;

    if(!conn->receiver->deleteInput(conn->input) || !conn->sender->deleteOutput(conn->output))
        return false;

    this->connexions.removeOne(conn);
    delete conn;

    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       QList<QVariant> GridModel::getConnexions(Item *it)
// Purpose:    Implementation of GridModel::getConnexions()
// Return:     QList<QVariant>
////////////////////////////////////////////////////////////////////////

QList<QVariant> GridModel::getConnexions(Item *it) const {
    QVector<Item::s_connect *> it_outs = it->getOutputs();
    int s = it_outs.size();
    QList< QVariant > resultat;

    for(int i = 0 ; i < s; ++i)
    {
        if(!it_outs[i])
            resultat.append(QVariant());
        else
        {
            QModelIndex index = this->getIndex(it_outs[i]->receiver);
            resultat.append(QVariant(QLine(index.column(), index.row(), it_outs[i]->input, it_outs.at(i)->receiver->getInputs().size())));
        }
    }

    return resultat;
}

////////////////////////////////////////////////////////////////////////
// Name:       QModelIndex GridModel::getIndex(Item *item)
// Purpose:    Implementation of GridModel::getIndex()
// Return:     QModelIndex
////////////////////////////////////////////////////////////////////////

QModelIndex GridModel::getIndex(Item *item) const {
    for(int i = 0; i < this->items.size(); i++)
        for(int j = 0; j < this->items.at(i).size(); j++)
            if(item == this->items.at(i).at(j))
                return this->index(i,j);

    return QModelIndex();


}
