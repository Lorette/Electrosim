/***********************************************************************
 * Module:  mapp.cpp
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: samedi 12 mai 2012 17:14:21
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
    model = new GridModel(13,14); // Initialise le model de 13x14 par defaut
    ui->setupUi(this); // Relie l'interface � cet objet

    this->on_actionFrench_triggered(); // On le traduit en francais
    this->ui->row_count->setText(QString::number(this->model->rowCount()));
    this->ui->column_count->setText(QString::number(this->model->columnCount()));

    ui->tableView->setModel(model); //Indique � la vue d'utiliserle model cr�e
    ui->tableView->setItemDelegate(new ImageDelegate(this)); // Cr�er un d�l�gu�

    ui->listWidget->addItem(new QListWidgetItem("Input")); // Rajoute une entr�e � la liste des composants
    ui->listWidget->addItem(new QListWidgetItem("Output")); // Idem
    ui->listWidget->addItem(new QListWidgetItem("Not")); // Idem
    ui->listWidget->addItem(new QListWidgetItem("Or")); // Idem
    ui->listWidget->addItem(new QListWidgetItem("Xor")); // Idem
    ui->listWidget->addItem(new QListWidgetItem("Equivalence")); // Idem
    ui->listWidget->addItem(new QListWidgetItem("And")); // Idem
    ui->listWidget->addItem(new QListWidgetItem("Multiplexer")); // Idem
    ui->listWidget->addItem(new QListWidgetItem("Demultiplexer")); // Idem

    ui->listWidget->addItem(new QListWidgetItem("IeO")); // Idem

    ui->listWidget->setCurrentRow(0);

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
    delete this->model;
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
        if((aux = this->model->at(index)) != NULL) { // Et que l'Item s�l�ctionn� dans la grille existe
            this->ui->name->setText(aux->getName()); // On met son nom dans la partie Informations
            this->ui->modify->setEnabled(true); // On active la modification
            this->ui->description->setText(aux->getDescription()); // On recup�re la description
            (aux->getClass() == Item::Input) ? this->ui->def_value->setValue(aux->getAuxValue()) : this->ui->def_value->setEnabled(false);
            this->ui->def_value->setEnabled(true);
        }
        else {
            this->ui->name->setText(""); // Sinon on ne met pas de nom ...
            this->ui->def_value->setEnabled(false); // D�sactivation valeur par default
            this->ui->description->setText(""); // Pas de description
            this->ui->modify->setEnabled(false);
        }
        break;
    case PLACE : // Si l'action est le placement d'un nouvel Item
        if((aux = this->getItemInList()) != NULL) {
            if(this->model->at(index) != NULL) // Et qu'il y a un Item � l'endroit s�l�ctionn�
                QMessageBox::critical(0,tr("Error"),tr("Position already used.")); // On indique que l'endroit est d�j� pris
            else {
                int i = 0;
                 while(!(this->model->nameIsCorrect("Item" +QString::number(i)))) { i++; }
                if((name = QInputDialog::getText(this,tr("Give a name"),tr("Give a name to this component."), QLineEdit::Normal, "Item" +QString::number(i))) != "") { // Sinon on demande un nom
                    aux->setName(name); // On met le nom � l'Item en cours de placement
                    if(!this->model->addItem(index, aux)) // On le rajoute au model
                        QMessageBox::critical(0,tr("Incorrect name"), tr("A name have to be unique and without space.")); //le nom doit etre unique
                    else
                        this->ui->statusBar->showMessage(tr("The component has been correctly place on the grid."));
                }
            }
        }
        break;

    case CONNECT1 : // SI c'est la premi�re fois qu'on clic sur la grille alors qu'on veut faire une connection
        if((this->currentItem = this->model->at(index)) == NULL) // Si il n'y a pas d'item � l'endroit s�l�ctionn� + on sauvegarde cet Item
            QMessageBox::critical(this,tr("Error"),tr("You have to select a component.")); // On l'indique
        else {
            this->currentAction = CONNECT2; // Sinon on peut passer  � la deuxi�me phase
            this->ui->statusBar->showMessage(tr("You have to click on the second component (receiver)."));
        }
        break;
    case CONNECT2 : // Si c'est la deuxi�me fois qu'on clic sur la grille alors qu'on veut faire une connection
        if((aux = this->model->at(index)) != NULL && aux != this->currentItem) { // Si le deuxi�me Item s�l�ctionn� existe et qu'il est diff�rent du premier
            conn = this->autoS_connect(this->currentItem, aux); // On cr�e une connection entre ces deux Items

            if(conn != NULL)  // Si la connection s'est correctement cr�e
                if(!this->model->connexion(conn))  // On le rajoute au model
                    QMessageBox::critical(this,tr("Error"),tr("Unable to connect those components.")); // On indique une erreur

        }
        else {
            QMessageBox::critical(this,tr("Error"),tr("You have to select a second component.")); // On indique une erreur
            break;
        }

        this->ui->statusBar->showMessage(tr("You have two click on the first component (sender)."));
        this->currentAction = CONNECT1;
        break; 
    case DELETE :
        if((aux = this->model->at(index)) != NULL)
            (this->model->removeItem(this->currentIndex)) ? this->ui->statusBar->showMessage(tr("The component has been deleted.")) : this->ui->statusBar->showMessage(tr("A problem occured during the deletion."));
        break;
    }

    this->model->setData(QModelIndex(), QVariant(), 0);
}

////////////////////////////////////////////////////////////////////////
// Name:       MApp::autoS_connect(Item* sender, Item* receiver)
// Purpose:    Implementation of MApp::autoS_connect()
// Return:     Item::s_connect*
////////////////////////////////////////////////////////////////////////

Item::s_connect* MApp::autoS_connect(Item* sender, Item* receiver) { // Affichage des options de connection
    Item::s_connect *conn = NULL; // On cr�e une connection vide
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

    if(wConnOpt->exec() == QDialog::Accepted) { // On affiche la fenetre (exec va bloquer l'application sur cette fenetre)

        if(uConnOpt->chk_inputs->currentText() == "" || uConnOpt->chk_outputs->currentText() == "")
            return NULL;

        conn = new Item::s_connect;
        conn->sender = sender; // On indique l'emetteur
        conn->output = uConnOpt->chk_outputs->currentText().toInt(); // la sortie
        conn->receiver = receiver; // le recepteur
        conn->input = uConnOpt->chk_inputs->currentText().toInt(); // l'entr�e
        conn->value = NULL; // et la valeur
    }
    else
        return NULL;


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
// Name:       MApp::on_actionCharger_un_Fichier_triggered()
// Purpose:    Implementation of MApp::on_actionCharger_Un_Fichier()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_actionCharger_un_Fichier_triggered()
{
    QString s = QFileDialog::getOpenFileName(this,tr("Choose a file"),QString(),tr("Elec Files (*.elec);;Texts Files (*.txt)"));
    GridModel *gModel;

    if(s == "") //cancel
        return;

    QFile file(s);

    if( !file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this,tr("Error"),tr("Unable to open this file."));
        return;
    }

    if((gModel = GridModel::loadFromFile(&file)) != NULL) {
        delete this->model;
        this->ui->tableView->setModel(this->model = gModel);
        this->ui->row_count->setText(QString::number(model->rowCount()));
        this->ui->column_count->setText(QString::number(model->columnCount()));
        this->ui->statusBar->showMessage(tr("The grid has been correctly loaded."));
    }
    else
        QMessageBox::critical(0, tr("Error"), tr("Corrupted file."));

    file.close();

}


////////////////////////////////////////////////////////////////////////
// Name:       MApp::on_actionSauvegarder_un_Fichier_triggered()
// Purpose:    Implementation of MApp::on_actionSauvegarder_Un_Circuit()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_actionSauvegarder_un_Fichier_triggered()
{
    QString s = QFileDialog::getSaveFileName(this,tr("Choose a file"),QString(),tr("Elec Files (*.elec);;Texts Files (*.txt)"));

    if(s == "") //cancel
        return;

    QFile file(s);

    if( !file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this,tr("Error"),tr("Unable to open this file."));
        return;
    }
    if(this->model->saveInFile(&file))
        this->ui->statusBar->showMessage(tr("The grid has been correctly saved into ") +s +".");
    else
        this->ui->statusBar->showMessage(tr("A problem occured during the save."));

    file.close();
}

////////////////////////////////////////////////////////////////////////
// Name:       Item* MApp::getItemInList()
// Purpose:    Implementation of MApp::getItemInList()
// Return:     Item*
////////////////////////////////////////////////////////////////////////

Item* MApp::getItemInList() // Si on clic sur le placement
{
    QModelIndex index = ui->listWidget->currentIndex(); // On recupere l'index de l'item dans la liste
    Item *it;

    switch(index.row()) { // Selon la ligne s�l�ctionn� dans la liste
    case Item::Input : it = new Input(); // Nouvelle Entr�e
        break;
    case Item::Output : it = new Output(); // Nouvelle Sortie
            break;
    case Item::Not : it = new Not(); // Nouveau composant de type Not
          break;
    case Item::Or : it = new Or(); // Type Or
        break;
    case Item::Xor : it = new Xor();
        break;
    case Item::XNOr : it = new XNOr(); // Co�ncidence
        break;
    case Item::And : it = new And(); // And
        break;
    case Item::Mux : it = new Multiplexer(2); // Multiplexeur avec n = 2 par defaut
        break;
    case Item::Demux : it = new Demultiplexer(2); // Demultiplexeur avec n = 2 par defaut
        break;
    case Item::IeO : it = new IeO(2);
        break;
    default: it = NULL;
    }

    return it;
}

////////////////////////////////////////////////////////////////////////
// Name:       void MApp::on_actionQuit_triggered()
// Purpose:    Implementation of void MApp::on_actionQuit_triggered()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_actionQuit_triggered()
{
    qApp->quit();
}

////////////////////////////////////////////////////////////////////////
// Name:       void MApp::on_def_value_valueChanged(int arg1)
// Purpose:    Implementation of MApp::on_def_value_valueChanged()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_def_value_valueChanged(int arg1)
{
    this->model->setDefValueOnInput(this->model->at(this->currentIndex), this->ui->def_value->value());
    emit this->ui->tableView->setFocus(); // On met le focus sur la grille (provoque une mise a jour visuelle)
}

////////////////////////////////////////////////////////////////////////
// Name:       void MApp::on_modify_clicked()
// Purpose:    Implementation of MApp::on_modify_clicked()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_modify_clicked()
{
    QDialog *wModify = new QDialog(this); // On initialise la fenetre ...
    Ui::Modify *uModify = new Ui::Modify; // ... l'interface ...
    QVector <QCheckBox *> box_i;
    QVector <QCheckBox *> box_o;
    Item *it;
    int plc;

    if((it = this->model->at(this->currentIndex)) == NULL)
            return;

    QVector<Item::s_connect *> outputs = it->getOutputs(); // On recupere les connections sortantes
    QVector<Item::s_connect *> inputs = it->getInputs(); // On recupere les connections entrantes
    box_i.resize(inputs.size());
    box_o.resize(outputs.size());

    uModify->setupUi(wModify); // ... et on les lie
    wModify->setWindowTitle(tr("Modifying") +" " +it->getName());

    uModify->name->setText(it->getName());
    if(it->getClass() == Item::Mux || it->getClass() == Item::Demux || it->getClass() == Item::IeO)
        uModify->Inputs->setVisible(true);
    else
        uModify->Inputs->setVisible(false);

    if(it->getClass() == Item::IeO)
        uModify->Inputs->setSuffix(tr(" Outputs"));

    uModify->Inputs->setValue(it->getAuxValue());

    plc = 0;
    for(QVector<Item::s_connect *>::iterator it = inputs.begin(); it != inputs.end(); it++) {
        if(*(it) != NULL) {
            QCheckBox *chkbox = new QCheckBox(uModify->scrollAreaWidgetContents_3);
            chkbox->setChecked(true);
            QLabel *lbl = new QLabel((*(it))->sender->getName() +"  ---->  " +(*(it))->receiver->getName(),uModify->scrollAreaWidgetContents_3);
            uModify->formLayout_2->setWidget(plc, QFormLayout::LabelRole, chkbox);
            uModify->formLayout_2->setWidget(plc, QFormLayout::FieldRole, lbl);
            box_i[(*it)->input] = chkbox;
            plc++;
        }
    }

    plc = 0;
    for(QVector<Item::s_connect *>::iterator it = outputs.begin(); it != outputs.end(); it++) {
        if(*(it) != NULL) {
            QCheckBox *chkbox = new QCheckBox(uModify->scrollAreaWidgetContents_4);
            chkbox->setChecked(true);
            QLabel *lbl = new QLabel((*(it))->sender->getName() +"  ---->  " +(*(it))->receiver->getName(),uModify->scrollAreaWidgetContents_4);
            uModify->formLayout->setWidget(plc, QFormLayout::LabelRole, chkbox);
            uModify->formLayout->setWidget(plc, QFormLayout::FieldRole, lbl);
            box_o[(*it)->output] = chkbox;
            plc++;

        }
    }

    if(wModify->exec() == QDialog::Accepted) { // Fenetre bloquante
        if(uModify->name->text() != it->getName())
        {
            if(!(this->model->nameIsCorrect(uModify->name->text())))
                QMessageBox::critical(0,tr("Incorrect name"), tr("A name have to be unique and without space."));
            else
                it->setName(uModify->name->text());
        }

        for(int i = 0; i < box_i.size(); i++)
            if(box_i.at(i) != NULL && !box_i.at(i)->isChecked())
                this->model->removeConnexion(inputs.at(i));

        for(int i = 0; i < box_o.size(); i++)
            if(box_o.at(i) != NULL && !box_o.at(i)->isChecked())
                this->model->removeConnexion(outputs.at(i));

        if(it->getClass() == Item::Mux && uModify->Inputs->value() < it->getAuxValue())
            for(int i = uModify->Inputs->value() +1; i < it->getAuxValue() + log2(it->getAuxValue()); i++)
                this->model->removeConnexion(inputs.at(i));

        if(it->getClass() == Item::Demux && uModify->Inputs->value() < it->getAuxValue()) {
            for(int i = uModify->Inputs->value(); i < it->getAuxValue(); i++)
                this->model->removeConnexion(inputs.at(i));
            for(int i = qPow(2,uModify->Inputs->value()); i < qPow(2,it->getAuxValue()); i++)
                this->model->removeConnexion(outputs.at(i));
        }

        if(it->getClass() == Item::IeO && uModify->Inputs->value() < it->getAuxValue())
            for(int i = uModify->Inputs->value(); i < it->getAuxValue(); i++)
                this->model->removeConnexion(outputs.at(i));

         this->model->setDefValueOnInput(it, uModify->Inputs->value());
    }

    delete uModify; // On d�truit l'interface ...
    delete wModify; // ... et la fenetre
    this->on_tableView_clicked(this->currentIndex);
}

////////////////////////////////////////////////////////////////////////
// Name:       void MApp::on_TableDeVerite_clicked()
// Purpose:    Implementation of MApp::on_TableDeVerite_clicked()
// Return:     void
////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////
// Name:       void MApp::on_actionFrench_triggered()
// Purpose:    Implementation of MApp::on_actionFrench_triggered()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_actionFrench_triggered()
{
    QTranslator* translator = new QTranslator();
    translator->load(":/Translations/fr"); // On charge le fichier francais
    qApp->installTranslator(translator); // On installe la nouvelle traduction
    ui->actionFrench->setChecked(true);
    ui->actionEnglish->setChecked(false);

    this->ui->retranslateUi(this); // On retraduit tout !!
}

////////////////////////////////////////////////////////////////////////
// Name:       void MApp::on_actionEnglish_triggered()
// Purpose:    Implementation of MApp::on_actionEnglish_triggered()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_actionEnglish_triggered()
{
    QTranslator* translator = new QTranslator();
    translator->load(":/Translations/en"); // On charge le fichier anglais
    qApp->installTranslator(translator); // On installe la nouvelle traduction
    ui->actionFrench->setChecked(false);
    ui->actionEnglish->setChecked(true);

    this->ui->retranslateUi(this); // On retraduit tout !!
}

////////////////////////////////////////////////////////////////////////
// Name:       void MApp::on_actionNew_triggered()
// Purpose:    Implementation of MApp::on_actionNew_triggered()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_actionNew_triggered()
{
    delete this->model;
    model = new GridModel(13,14); // Initialise le model de 14x14 par defaut
    this->ui->row_count->setText(QString::number(this->model->rowCount()));
    this->ui->column_count->setText(QString::number(this->model->columnCount()));

    ui->tableView->setModel(model); //Indique � la vue d'utiliserle model cr�e
}

////////////////////////////////////////////////////////////////////////
// Name:       void MApp::on_mode_activated(int index)
// Purpose:    Implementation of MApp::on_mode_activated()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_mode_activated(int index)
{
    switch(index) {
    case VIEW : this->currentAction = VIEW;
        this->ui->tableView->enableTracking(false); // On desactive la coloration des cases
        this->ui->statusBar->showMessage(tr("Select a component on the grid."));
        break;
    case PLACE : this->currentAction = PLACE;
        this->ui->modify->setEnabled(false);
        this->ui->tableView->enableTracking(true); // On active la coloration des cases
        this->ui->statusBar->showMessage(tr("You have to select a position on the grid to place this component."));
        break;

    case CONNECT1 : this->currentAction = CONNECT1;
        this->ui->modify->setEnabled(false);
        this->ui->tableView->enableTracking(false); // On d�sactive la coloration des cases pour le placement
        this->ui->statusBar->showMessage(tr("You have two click on the first component (sender)."));
        break;
    case DELETE : this->currentAction = DELETE;
        this->ui->modify->setEnabled(false);
        this->ui->tableView->enableTracking(false); // On d�sactive la coloration des cases pour le placement
        this->ui->statusBar->showMessage(tr("Click one of the component in the grid to delete it."));
        break;
    }
}
