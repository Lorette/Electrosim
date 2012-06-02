/***********************************************************************
 * Module:  mapp.cpp
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: samedi 12 mai 2012 17:12:23
 * Purpose: Implementation of the class MApp
 ***********************************************************************/

#include "mapp.h"
#include "ui_mapp.h"
#include "ui_conn_option.h"
#include "ui_settings.h"
#include "ui_modify.h"
#include "ui_verite.h"

////////////////////////////////////////////////////////////////////////
// Name:       MApp::MApp(QWidget *parent) : QMainWindow(parent),ui(new Ui::MApp)
// Purpose:    Implementation of MApp::MApp()
// Return:
////////////////////////////////////////////////////////////////////////

MApp::MApp(QWidget *parent) : QMainWindow(parent),ui(new Ui::MApp)
{
    model = new GridModel(0,0); // Initialise le model de 9x14 par defaut

    ui->setupUi(this); // Relie l'interface à cet objet

    ui->tableView->setModel(model); //Indique à la vue d'utiliserle model crée
    ui->tableView->setItemDelegate(new ImageDelegate(this)); // Créer un délégué

    ui->listWidget->addItem(new QListWidgetItem("Input")); // Rajoute une entrée à la liste des composants
    ui->listWidget->addItem(new QListWidgetItem("Output")); // Idem
    ui->listWidget->addItem(new QListWidgetItem("Not")); // Idem
    ui->listWidget->addItem(new QListWidgetItem("Or")); // Idem
    ui->listWidget->addItem(new QListWidgetItem("And")); // Idem

    this->currentItem = NULL; // Indique qu'aucune sélection n'est faite ...
    this->currentAction = VIEW; // Indique que l'action est la vue simple
}

////////////////////////////////////////////////////////////////////////
// Name:       MApp::~MApp()
// Purpose:    Implementation of MApp::~MApp()
// Return:
////////////////////////////////////////////////////////////////////////

MApp::~MApp()
{
    delete ui; // Détruit l'interface
}

////////////////////////////////////////////////////////////////////////
// Name:       MApp::on_tableView_clicked(const QModelIndex &index)
// Purpose:    Implementation of MApp::on_tableView_clicked()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_tableView_clicked(const QModelIndex &index) // SI on clic sur la grille
{
    Item *aux = NULL;
    QString name;
    Item::s_connect *conn;
    this->currentIndex = index;

    switch(this->currentAction) {
    case VIEW : // SI l'action courante est la vue
        if((this->currentItem = this->model->at(index)) != NULL) { // Et que l'Item séléctionné dans la grille existe
            this->ui->name->setText(this->currentItem->getName()); // On met son nom dans la partie Informations
            this->ui->Delete->setEnabled(true); // On active la suppression
            this->ui->modify->setEnabled(true); // On active la modification
            (this->currentItem->getClass() == Item::Input0) ? this->ui->def_value->setEnabled(true) : this->ui->def_value->setEnabled(false); // Activation/désactivation valeur par default
            this->ui->def_value->setValue(this->currentItem->getDefaultValue());
        }
        else {
            this->ui->name->setText(""); // Sinon on ne met pas de nom ...
            this->ui->Delete->setEnabled(false); // On désactive la suppression
            this->ui->def_value->setEnabled(false); // Désactivation valeur par default
            this->ui->modify->setEnabled(false);
        }
        break;
    case PLACE : // Si l'action est le placement d'un nouvel Item
        if(this->currentItem != NULL) { // Si il y a un Item en cours de placement
            if(this->model->at(index) != NULL) // Et qu'il y a un Item à l'endroit séléctionné
                QMessageBox::critical(0,"Enculé","Hey, fils de pute, ta pas le droit ici"); // On indique que l'endroit est déjà pris
            else if((name = QInputDialog::getText(this,"Entrez un nom","Entre un nom fils de pute", QLineEdit::Normal, "Item")) != "") { // Sinon on demande un nom
                this->currentItem->setName(name); // On met le nom à l'Item en cours de placement
                this->model->addItem(index, this->currentItem); // On le rajoute ua model
                this->ui->tableView->enableTracking(false); // On désactive la coloration des cases pour le placement
                this->currentItem = NULL; // Plus d'item en cours de placement
                this->currentAction = VIEW; // Action remise par defaut à la vue
                this->ui->Place->setText("Place"); // On remet le text du bouton par defaut pour un nouveau placement

            }
        }
        break;

    case CONNECT1 : // SI c'est la première fois qu'on clic sur la grille alors qu'on veut faire une connection
        if((this->currentItem = this->model->at(index)) == NULL) // Si il n'y a pas d'item à l'endroit séléctionné + on sauvegarde cet Item
            QMessageBox::critical(this,"Enculé","Vous devez selectionner un objet"); // On l'indique
        else
            this->currentAction = CONNECT2; // Sinon on peut passer  à la deuxième phase
        break;
    case CONNECT2 : // Si c'est la deuxième fois qu'on clic sur la grille alors qu'on veut faire une connection
        if((aux = this->model->at(index)) != NULL && aux != this->currentItem) { // Si le deuxième Item séléctionné existe et qu'il est différent du premier
            conn = this->autoS_connect(this->currentItem, aux); // On crée une connection entre ces deux Items

            if(conn != NULL) { // Si la connection s'est correctement crée
                if(this->model->connexion(conn)) { // On le rajoute au model
                    this->ui->connect->setText("Connect"); // On reinitialise le bouton pour une nouvelle connection
                    this->currentAction = VIEW; // On remet l'action par defaut à la vue
                }
                else // Sinon
                    QMessageBox::critical(this,"Erreur","Impossible de connecter ces 2 objets"); // On indique une erreur
            }
            else
                    QMessageBox::critical(this,"Erreur","Impossible de connecter ces 2 objets"); // On indique une erreur
        }
        else
            QMessageBox::critical(this,"Enculé","Vous deevez selectionner au moins un objet différent");
        break;

    }

    this->ui->tableView->update(index); // On met à jour la grille
}

////////////////////////////////////////////////////////////////////////
// Name:       MApp::on_connect_clicked()
// Purpose:    Implementation of MApp::on_connect_clicked()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_connect_clicked() // SI on clic sur le bouton connect
{
    this->currentItem = NULL; // On reinitialise l'Item courant
    this->ui->Delete->setEnabled(false);
    this->ui->modify->setEnabled(false);
    if(this->currentAction == CONNECT1 || this->currentAction == CONNECT2) { // Si l'action courante est une connection de n'importe quel phase
        this->currentAction = VIEW; // On annule l'action de connection et on remet l'action à la Vue
        this->ui->connect->setText("Connect"); // Indique qu'une nouvelle connection est possible
    }
    else { // Sinon on veut faire une connection
        this->currentAction = CONNECT1; // 1ere phase enclenchée
        this->ui->connect->setText("Cancel"); // On indique qu'on peut annulé l'action en recliquant sur le meme bouton
        this->ui->Place->setText("Place"); // On annule l'action de placement si il y en avait une
    }

    this->ui->tableView->enableTracking(false); // On désactive la coloration des cases pour le placement
}

////////////////////////////////////////////////////////////////////////
// Name:       MApp::autoS_connect(Item* sender, Item* receiver)
// Purpose:    Implementation of MApp::autoS_connect()
// Return:     Item::s_connect*
////////////////////////////////////////////////////////////////////////

Item::s_connect* MApp::autoS_connect(Item* sender, Item* receiver) { // Affichage des options de connection
    Item::s_connect *conn = new Item::s_connect; // On crée une connection vide
    QDialog *wConnOpt = new QDialog(this); // On initialise une fenetre
    Ui::ConnOpt *uConnOpt = new Ui::ConnOpt; // On initialise une interface de fenetre

    QVector<Item::s_connect *> outputs = sender->getOutputs(); // On recupere les connections sortantes du 1er Item
    QVector<Item::s_connect *> inputs = receiver->getInputs(); // On recupere les connections entrantes du 2eme Item

    uConnOpt->setupUi(wConnOpt); // On indique à l'interface d'utiliser la fenetre des options
    uConnOpt->name_1->setText(sender->getName()); // On recupere les noms ...
    uConnOpt->name_2->setText(receiver->getName()); // ... et on les affiche

    for(int i = 0; i < outputs.size(); i++) // Ici ...
        if(outputs.at(i) == NULL) // ... on indique les sorties disponibles ...
            uConnOpt->chk_outputs->addItem(QString::number(i));  // ... pour le 1er Item (Emetteur)


    for(int i = 0; i < inputs.size(); i++) // Ici ...
        if(inputs.at(i) == NULL) // ... on indique les entrées disponibles ...
            uConnOpt->chk_inputs->addItem(QString::number(i)); // ... pour le 2eme Item (Récepteur)

    wConnOpt->exec(); // On affiche la fenetre (exec va bloquer l'application sur cette fenetre)

    if(uConnOpt->chk_inputs->currentText() == "" || uConnOpt->chk_outputs->currentText() == "")
        return NULL;

    conn->sender = sender; // On indique l'emetteur
    conn->output = uConnOpt->chk_outputs->currentText().toInt(); // la sortie
    conn->receiver = receiver; // le recepteur
    conn->input = uConnOpt->chk_inputs->currentText().toInt(); // l'entrée
    conn->value = NULL; // et la valeur

    delete uConnOpt; // On détruit l'interface ...
    delete wConnOpt; // et la fenetre

    return conn;
}

////////////////////////////////////////////////////////////////////////
// Name:       MApp::on_actionSettings_triggered()
// Purpose:    Implementation of MApp::on_actionSettings_triggered()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_actionSettings_triggered() // Fenetre des options pour l'application
{

    QDialog *wSettings = new QDialog(this); // On initialise la fenetre ...
    Ui::Settings *uSettings = new Ui::Settings; // ... l'interface ...
    uSettings->setupUi(wSettings); // ... et on les lie

    uSettings->grid->setChecked(this->ui->tableView->showGrid()); // si la grille est visible alors on coche la case
    uSettings->row_count->setValue(this->model->rowCount());
    uSettings->column_count->setValue(this->model->columnCount());

    if(wSettings->exec() == QDialog::Accepted) { // Fenetre bloquante

        this->ui->tableView->setShowGrid(uSettings->grid->isChecked()); // on active/désactive la grille en fonction de la case cochée

        if(uSettings->row_count->value() < this->model->rowCount())
            this->model->removeRows(0,this->model->rowCount() - uSettings->row_count->value());
        else
            this->model->insertRows(0, uSettings->row_count->value() - this->model->rowCount());

        if(uSettings->column_count->value() < this->model->columnCount())
            this->model->removeColumns(0,this->model->columnCount() - uSettings->column_count->value());
        else
            this->model->insertColumns(0, uSettings->column_count->value() - this->model->columnCount());

        this->ui->row_count->setText(QString::number(uSettings->row_count->value()));
        this->ui->column_count->setText(QString::number(uSettings->column_count->value()));
    }

    delete uSettings; // On détruit l'interface ...
    delete wSettings; // ... et la fenetre
}

////////////////////////////////////////////////////////////////////////
// Name:       MApp::on_actionCharger_un_Fichier_triggered()
// Purpose:    Implementation of MApp::on_actionCharger_Un_Fichier()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_actionCharger_un_Fichier_triggered()
{
    QString s = QFileDialog::getOpenFileName(this,tr("Choississez un Fichier"),QString(),tr("Fichiers Textes (*.txt);;Elec Files (*.elec)"));

    QFile file(s);

    if( !file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this,"Error","Fichier Inutilisable !!");
        return;
    }

    this->model->loadFromFile(&file);

    file.close();

}


////////////////////////////////////////////////////////////////////////
// Name:       MApp::on_actionSauvegarder_un_Fichier_triggered()
// Purpose:    Implementation of MApp::on_actionSauvegarder_Un_Circuit()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_actionSauvegarder_un_Fichier_triggered()
{
    QString s = QFileDialog::getSaveFileName(this,tr("Choississez un Fichier"),QString(),tr("Fichiers Textes (*.txt);;Elec Files (*.elec)"));

    QFile file(s);

    if( !file.open(QIODevice::Append))
    {
        QMessageBox::critical(this,"Error","Fichier Inutilisable !!");
        return;
    }
    this->model->saveInFile(&file);
    file.close();
}

////////////////////////////////////////////////////////////////////////
// Name:       void MApp::on_Place_clicked()
// Purpose:    Implementation of void MApp::on_Place_clicked()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_Place_clicked() // Si on clic sur le placement
{
    QModelIndex index = ui->listWidget->currentIndex(); // On recupere l'index de l'item dans la liste

    if(this->currentAction == PLACE) { // Si l'action est déjà le placement
        this->currentAction = VIEW; // On l'annule et on revient à la vue
        this->currentItem = NULL; // Pas d'item séléctionné
        this->ui->Place->setText("Place"); // On indique qu'on peut refaire un placement
        this->ui->tableView->enableTracking(false); // On désactive la coloration des cases pour le placemen
        return;
    }

    this->currentAction = PLACE; // On active le placement
    this->currentItem = NULL; // Pas d'item selectionné
    this->ui->Delete->setEnabled(false);
    this->ui->modify->setEnabled(false);
    this->ui->connect->setText("Connect"); // On indique que la connection est possible
    this->ui->Place->setText("Cancel"); // On indique qu'on peut annuler le placement
    this->ui->tableView->enableTracking(true); // On active la coloration des cases

    switch(index.row()) { // Selon la ligne séléctionné dans la liste
        case Item::Input0 : this->currentItem = new Input(); // Nouvelle Entrée
            break;
    case Item::Output1 : this->currentItem = new Output(); // Nouvelle Sortie
            break;
    case Item::Not2 : this->currentItem = new Not(); // Nouveau composant de type Not
          break;
    case Item::Or3 : this->currentItem = new Or();
        break;
    case Item::And4 : this->currentItem = new And();
        break;

        default : this->ui->tableView->enableTracking(false); // Sinon On annule ...
            this->currentAction = VIEW; // le placement
    }

    emit this->ui->tableView->setFocus(); // On met le focus sur la grille (provoque une mise a jour visuelle)
}

////////////////////////////////////////////////////////////////////////
// Name:       void MApp::on_Delete_clicked()
// Purpose:    Implementation of void MApp::on_Delete_clicked()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_Delete_clicked()
{
    if(this->currentIndex.isValid()) // On vérifie que l'index est valide
        this->model->removeItem(this->currentIndex); // Et on supprime l'item du modele

    this->on_tableView_clicked(this->currentIndex); // Mise à jour des infos ...
}

////////////////////////////////////////////////////////////////////////
// Name:       void MApp::on_actionQuit_triggered()
// Purpose:    Implementation of void MApp::on_actionQuit_triggered()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MApp::on_def_value_valueChanged(int arg1)
{
    this->model->setDefValueOnInput(this->model->at(this->currentIndex), arg1);
    emit this->ui->tableView->setFocus(); // On met le focus sur la grille (provoque une mise a jour visuelle)
}

void MApp::on_modify_clicked()
{
    QDialog *wModify = new QDialog(this); // On initialise la fenetre ...
    Ui::Modify *uModify = new Ui::Modify; // ... l'interface ...
    Item *it = this->currentItem;

    uModify->setupUi(wModify); // ... et on les lie
    wModify->setWindowTitle("Modifying "+it->getName());

    uModify->name->setText(it->getName());

    if(wModify->exec() == QDialog::Accepted) { // Fenetre bloquante
        it->setName(uModify->name->text());
    }

    delete uModify; // On détruit l'interface ...
    delete wModify; // ... et la fenetre
}

void MApp::on_TableDeVerite_clicked()
{
    QDialog *wVerite = new QDialog(this); // On initialise la fenetre ...
    Ui::Verite *uVerite = new Ui::Verite; // ... l'interface ...

    QPair <QVector < QString >, QVector< QVector < int > > > table_de_verite = this->model->verite();
    uVerite->setupUi(wVerite); // ... et on les lie

    int nb_lignes = table_de_verite.second.size();
    int nb_colonnes = table_de_verite.first.size();

    uVerite->tableWidget->setRowCount(nb_lignes);
    uVerite->tableWidget->setColumnCount(nb_colonnes);

    uVerite->tableWidget->setHorizontalHeaderLabels(table_de_verite.first.toList());

    for(int i = 0; i < nb_lignes; i++)
        for(int j = 0; j < nb_colonnes; j++)
            uVerite->tableWidget->setItem(i,j,new QTableWidgetItem(QString::number(table_de_verite.second.at(i).at(j))));

    wVerite->exec();

    delete uVerite;
    delete wVerite;
}
