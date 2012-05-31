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

////////////////////////////////////////////////////////////////////////
// Name:       MApp::MApp(QWidget *parent) : QMainWindow(parent),ui(new Ui::MApp)
// Purpose:    Implementation of MApp::MApp()
// Return:
////////////////////////////////////////////////////////////////////////

MApp::MApp(QWidget *parent) : QMainWindow(parent),ui(new Ui::MApp)
{
    model = new GridModel(0,0); // Initialise le model de 9x14 par defaut

    ui->setupUi(this); // Relie l'interface � cet objet

    ui->tableView->setModel(model); //Indique � la vue d'utiliserle model cr�e
    ui->tableView->setItemDelegate(new ImageDelegate(this)); // Cr�er un d�l�gu�

    ui->listWidget->addItem(new QListWidgetItem("Input")); // Rajoute une entr�e � la liste des composants
    ui->listWidget->addItem(new QListWidgetItem("Output")); // Idem
    ui->listWidget->addItem(new QListWidgetItem("Not")); // Idem
    ui->listWidget->addItem(new QListWidgetItem("And")); // Idem

    this->currentItem = NULL; // Indique qu'aucune s�lection n'est faite ...
    this->currentAction = VIEW; // Indique que l'action est la vue simple
}

////////////////////////////////////////////////////////////////////////
// Name:       MApp::~MApp()
// Purpose:    Implementation of MApp::~MApp()
// Return:
////////////////////////////////////////////////////////////////////////

MApp::~MApp()
{
    delete ui; // D�truit l'interface
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
        if((this->currentItem = this->model->at(index)) != NULL) { // Et que l'Item s�l�ctionn� dans la grille existe
            this->ui->name->setText(this->currentItem->getName()); // On met son nom dans la partie Informations
            this->ui->Delete->setEnabled(true); // On active la suppression
            (this->currentItem->getClass() == Item::Input0) ? this->ui->def_value->setEnabled(true) : this->ui->def_value->setEnabled(false);
            this->ui->def_value->setValue(this->currentItem->getDefaultValue());
        }
        else {
            this->ui->name->setText(""); // Sinon on ne met pas de nom ...
            this->ui->Delete->setEnabled(false); // On d�sactive la suppression
            this->ui->def_value->setEnabled(false);
        }
        break;
    case PLACE : // Si l'action est le placement d'un nouvel Item
        if(this->currentItem != NULL) { // Si il y a un Item en cours de placement
            if(this->model->at(index) != NULL) // Et qu'il y a un Item � l'endroit s�l�ctionn�
                QMessageBox::critical(0,"Encul�","Hey, fils de pute, ta pas le droit ici"); // On indique que l'endroit est d�j� pris
            else if((name = QInputDialog::getText(this,"Entrez un nom","Entre un nom fils de pute", QLineEdit::Normal, "Item")) != "") { // Sinon on demande un nom
                this->currentItem->setName(name); // On met le nom � l'Item en cours de placement
                this->model->addItem(index, this->currentItem); // On le rajoute ua model
                if(this->currentItem->getClass() == Item::Input0) // Si l'item est une entr�e
                    QObject::connect(this, SIGNAL(launch()), this->currentItem, SLOT(recvSignal())); // On cr�e une connexion entre lui et le controlleur pour la simulation
                if(this->currentItem->getClass() == Item::Output1) // Si l'item est une entr�e
                    QObject::connect(this->currentItem, SIGNAL(sendSignal(int*)), this, SLOT(finish(int*))); // On cr�e une connexion entre lui et le controlleur pour la simulation
                this->ui->tableView->enableTracking(false); // On d�sactive la coloration des cases pour le placement
                this->currentItem = NULL; // Plus d'item en cours de placement
                this->currentAction = VIEW; // Action remise par defaut � la vue
                this->ui->Place->setText("Place"); // On remet le text du bouton par defaut pour un nouveau placement

            }
        }
        break;

    case CONNECT1 : // SI c'est la premi�re fois qu'on clic sur la grille alors qu'on veut faire une connection
        if((this->currentItem = this->model->at(index)) == NULL) // Si il n'y a pas d'item � l'endroit s�l�ctionn� + on sauvegarde cet Item
            QMessageBox::critical(this,"Encul�","Vous devez selectionner un objet"); // On l'indique
        else
            this->currentAction = CONNECT2; // Sinon on peut passer  � la deuxi�me phase
        break;
    case CONNECT2 : // Si c'est la deuxi�me fois qu'on clic sur la grille alors qu'on veut faire une connection
        if((aux = this->model->at(index)) != NULL && aux != this->currentItem) { // Si le deuxi�me Item s�l�ctionn� existe et qu'il est diff�rent du premier
            conn = this->autoS_connect(this->currentItem, aux); // On cr�e une connection entre ces deux Items

            if(conn != NULL) { // Si la connection s'est correctement cr�e
                if(this->model->connexion(conn)) { // On le rajoute au model
                    this->ui->connect->setText("Connect"); // On reinitialise le bouton pour une nouvelle connection
                    this->currentAction = VIEW; // On remet l'action par defaut � la vue
                }
                else // Sinon
                    QMessageBox::critical(this,"Erreur","Impossible de connecter ces 2 objets"); // On indique une erreur
            }
        }
        else
            QMessageBox::critical(this,"Encul�","Vous deevez selectionner au moins un objet diff�rent");
        break;

    }

    this->ui->tableView->update(index); // On met � jour la grille
}

////////////////////////////////////////////////////////////////////////
// Name:       MApp::on_connect_clicked()
// Purpose:    Implementation of MApp::on_connect_clicked()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_connect_clicked() // SI on clic sur le bouton connect
{
    this->currentItem = NULL; // On reinitialise l'Item courant
    if(this->currentAction == CONNECT1 || this->currentAction == CONNECT2) { // Si l'action courante est une connection de n'importe quel phase
        this->currentAction = VIEW; // On annule l'action de connection et on remet l'action � la Vue
        this->ui->connect->setText("Connect"); // Indique qu'une nouvelle connection est possible
    }
    else { // Sinon on veut faire une connection
        this->currentAction = CONNECT1; // 1ere phase enclench�e
        this->ui->connect->setText("Cancel"); // On indique qu'on peut annul� l'action en recliquant sur le meme bouton
        this->ui->Place->setText("Place"); // On annule l'action de placement si il y en avait une
    }

    this->ui->tableView->enableTracking(false); // On d�sactive la coloration des cases pour le placemen
}

////////////////////////////////////////////////////////////////////////
// Name:       MApp::autoS_connect(Item* sender, Item* receiver)
// Purpose:    Implementation of MApp::autoS_connect()
// Return:     Item::s_connect*
////////////////////////////////////////////////////////////////////////

Item::s_connect* MApp::autoS_connect(Item* sender, Item* receiver) { // Affichage des options de connection
    Item::s_connect *conn = new Item::s_connect; // On cr�e une connection vide
    QDialog *wConnOpt = new QDialog(this); // On initialise une fenetre
    Ui::ConnOpt *uConnOpt = new Ui::ConnOpt; // On initialise une interface de fenetre

    QVector<Item::s_connect *> outputs = sender->getOutputs(); // On recupere les connections sortantes du 1er Item
    QVector<Item::s_connect *> inputs = receiver->getInputs(); // On recupere les connections entrantes du 2eme Item

    uConnOpt->setupUi(wConnOpt); // On indique � l'interface d'utiliser la fenetre des options
    uConnOpt->name_1->setText(sender->getName()); // On recupere les noms ...
    uConnOpt->name_2->setText(receiver->getName()); // ... et on les affiche

    for(int i = 0; i < outputs.size(); i++) // Ici ...
        if(outputs.at(i) == NULL) // ... on indique les sorties disponibles ...
            uConnOpt->chk_outputs->addItem(QString::number(i));  // ... pour le 1er Item (Emetteur)


    for(int i = 0; i < inputs.size(); i++) // Ici ...
        if(inputs.at(i) == NULL) // ... on indique les entr�es disponibles ...
            uConnOpt->chk_inputs->addItem(QString::number(i)); // ... pour le 2eme Item (R�cepteur)

    wConnOpt->exec(); // On affiche la fenetre (exec va bloquer l'application sur cette fenetre)

    conn->sender = sender; // On indique l'emetteur
    conn->output = uConnOpt->chk_outputs->currentText().toInt(); // la sortie
    conn->receiver = receiver; // le recepteur
    conn->input = uConnOpt->chk_inputs->currentText().toInt(); // l'entr�e
    conn->value = NULL; // et la valeur

    delete uConnOpt; // On d�truit l'interface ...
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

        this->ui->tableView->setShowGrid(uSettings->grid->isChecked()); // on active/d�sactive la grille en fonction de la case coch�e

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

    delete uSettings; // On d�truit l'interface ...
    delete wSettings; // ... et la fenetre
}

////////////////////////////////////////////////////////////////////////
// Name:       MApp::on_Simulate_clicked()
// Purpose:    Implementation of MApp::on_Simulate_clicked()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_Simulate_clicked() // Si on clic sur le bouton simulate
{
    emit launch(); // On execute les fonctions des Inputs avec la valeur par default
}

////////////////////////////////////////////////////////////////////////
// Name:       void MApp::on_Place_clicked()
// Purpose:    Implementation of void MApp::on_Place_clicked()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_Place_clicked() // Si on clic sur le placement
{
    QModelIndex index = ui->listWidget->currentIndex(); // On recupere l'index de l'item dans la liste

    if(this->currentAction == PLACE) { // Si l'action est d�j� le placement
        this->currentAction = VIEW; // On l'annule et on revient � la vue
        this->currentItem = NULL; // Pas d'item s�l�ctionn�
        this->ui->Place->setText("Place"); // On indique qu'on peut refaire un placement
        this->ui->tableView->enableTracking(false); // On d�sactive la coloration des cases pour le placemen
        return;
    }

    this->currentAction = PLACE; // On active le placement
    this->currentItem = NULL; // Pas d'item selectionn�
    this->ui->connect->setText("Connect"); // On indique que la connection est possible
    this->ui->Place->setText("Cancel"); // On indique qu'on peut annuler le placement
    this->ui->tableView->enableTracking(true); // On active la coloration des cases

    switch(index.row()) { // Selon la ligne s�l�ctionn� dans la liste
        case Item::Input0 : this->currentItem = new Input(); // Nouvelle Entr�e
            break;
    case Item::Output1 : this->currentItem = new Output(); // Nouvelle Sortie
            break;
    case Item::Not2 : this->currentItem = new Not(); // Nouveau composant de type Not
          break;
    case Item::And3 : this->currentItem = new And();
        break;

        default : this->ui->tableView->enableTracking(false); // Sinon On annule ...
            this->currentAction = VIEW; // le placement
    }

    emit this->ui->tableView->setFocus(); // On met le focus sur la grille (provoque une mise a jour visuelle)
}

////////////////////////////////////////////////////////////////////////
// Name:       void MApp::finish(int *value)
// Purpose:    Implementation of void MApp::finish()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::finish(int *value) {
    if(value == NULL)
        return;

    QMessageBox::critical(this,"Result",QString::number(*value));
}

////////////////////////////////////////////////////////////////////////
// Name:       void MApp::on_Delete_clicked()
// Purpose:    Implementation of void MApp::on_Delete_clicked()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_Delete_clicked()
{
    if(this->currentIndex.isValid()) // On v�rifie que l'index est valide
        this->model->removeItem(this->currentIndex); // Et on supprime l'item du modele

    this->on_tableView_clicked(this->currentIndex); // Mise � jour des infos ...
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
    this->model->at(this->currentIndex)->setDefaultValue(arg1);
}
