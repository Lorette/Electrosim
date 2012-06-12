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
#include "ui_about_component.h"

////////////////////////////////////////////////////////////////////////
// Name:       MApp::MApp(QWidget *parent) : QMainWindow(parent),ui(new Ui::MApp)
// Purpose:    Implementation of MApp::MApp()
// Return:
////////////////////////////////////////////////////////////////////////

MApp::MApp(QWidget *parent) : QMainWindow(parent),ui(new Ui::MApp)
{
    model = new GridModel(13,20); // Initialise le model de 13x14 par defaut
    ui->setupUi(this); // Relie l'interface a cet objet

    this->on_actionFrench_triggered(); // On le traduit en francais et charge la liste
    this->ui->row_count->setText(QString::number(this->model->rowCount()));
    this->ui->column_count->setText(QString::number(this->model->columnCount()));

    ui->tableView->setModel(model); //Indique a la vue d'utiliserle model cree
    ui->tableView->setItemDelegate(new ImageDelegate(this)); // Creer un delegue

    this->currentItem = NULL; // Indique qu'aucune selection n'est faite ...
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
    delete ui; // Detruit l'interface
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
    case VIEW :
        break;
    case PLACE : // Si l'action est le placement d'un nouvel Item
        if((aux = this->getItemInList()) != NULL) {
            if(this->model->at(index) != NULL) // Et qu'il y a un Item a l'endroit selectionne
                QMessageBox::critical(0,tr("Error"),tr("Position already used.")); // On indique que l'endroit est deja pris
            else {
                int i = 0;
                QString default_name;

                //Choisi un bon nom par defaut
                switch (aux->getClass())
                {
                    case Item::Input :
                        default_name = "In";
                        break;
                    case Item::Output :
                        default_name = "Out";
                        break;
                    default :
                        default_name = "Item";
                }

                 while(!(this->model->nameIsCorrect(default_name +QString::number(i)))) { i++; }
                if((name = QInputDialog::getText(this,tr("Give a name"),tr("Give a name to this component."), QLineEdit::Normal, default_name +QString::number(i))) != "") { // Sinon on demande un nom
                    aux->setName(name); // On met le nom a l'Item en cours de placement
                    if(!this->model->addItem(index, aux)) // On le rajoute au model
                        QMessageBox::critical(0,tr("Incorrect name"), tr("A name have to be unique and without space.")); //le nom doit etre unique
                    else
                        this->ui->statusBar->showMessage(tr("The component has been correctly place on the grid."));
                }
            }
        }
        break;
    case CONNECT1 : // SI c'est la premiere fois qu'on clic sur la grille alors qu'on veut faire une connection
        if((this->currentItem = this->model->at(index)) == NULL) // Si il n'y a pas d'item a l'endroit selectionne + on sauvegarde cet Item
            QMessageBox::critical(this,tr("Error"),tr("You have to select a component.")); // On l'indique
        else {
            this->currentAction = CONNECT2; // Sinon on peut passer  a la deuxieme phase
            this->ui->statusBar->showMessage(tr("You have to click on the second component (receiver)."));
        }
        break;
    case CONNECT2 : // Si c'est la deuxieme fois qu'on clic sur la grille alors qu'on veut faire une connection
        if((aux = this->model->at(index)) != NULL && aux != this->currentItem) { // Si le deuxieme Item selectionne existe et qu'il est different du premier
            if((conn = this->autoS_connect(this->currentItem, aux)) != NULL)  // Si la connection s'est correctement cree
                if(!this->model->connexion(conn))  // On le rajoute au model
                    QMessageBox::critical(this,tr("Error"),tr("Unable to connect those components.")); // On indique une erreur
        }
        else {
            QMessageBox::critical(this,tr("Error"),tr("You have to select a second component.")); // On indique une erreur
            break;
        }
        this->ui->statusBar->showMessage(tr("You have to click on the first component (sender)."));
        this->currentAction = CONNECT1;
        break; 
    case DELETE :
        if((aux = this->model->at(index)) != NULL)
            (this->model->removeItem(this->currentIndex)) ? this->ui->statusBar->showMessage(tr("The component has been deleted.")) : this->ui->statusBar->showMessage(tr("A problem occured during the deletion."));
        break;
    }

    this->model->setData(QModelIndex(), QVariant(),0);
}

////////////////////////////////////////////////////////////////////////
// Name:       MApp::autoS_connect(Item* sender, Item* receiver)
// Purpose:    Implementation of MApp::autoS_connect()
// Return:     Item::s_connect*
////////////////////////////////////////////////////////////////////////

Item::s_connect* MApp::autoS_connect(Item* sender, Item* receiver) { // Affichage des options de connection
    Item::s_connect *conn = NULL; // On cree une connection vide
    QDialog *wConnOpt = new QDialog(this); // On initialise une fenetre
    Ui::ConnOpt *uConnOpt = new Ui::ConnOpt; // On initialise une interface de fenetre

    QVector<Item::s_connect *> outputs = sender->getOutputs(); // On recupere les connections sortantes du 1er Item
    QVector<Item::s_connect *> inputs = receiver->getInputs(); // On recupere les connections entrantes du 2eme Item

    uConnOpt->setupUi(wConnOpt); // On indique a l'interface d'utiliser la fenetre des options
    uConnOpt->name_1->setText(sender->getName()); // On recupere les noms ...
    uConnOpt->name_2->setText(receiver->getName()); // ... et on les affiche


    if(receiver->getClass() == Item::Mux || receiver->getClass() == Item::Demux) {
        int i;
        for(i = 0; i < receiver->getAuxValue(); i++) // Ici ...
            if(inputs.at(i) == NULL) // ... on indique les entrees disponibles ...
                uConnOpt->chk_inputs->addItem(tr("Adress") +" " +(QString::number(i))); // ... pour le 2eme Item (Recepteur)
        for(i = i; i < inputs.size();i++ )
            if(inputs.at(i) == NULL)
                uConnOpt->chk_inputs->addItem(tr("Input") +" " +(QString::number(i))); // ... pour le 2eme Item (Recepteur)
    }
    else
        for(int i = 0; i < inputs.size(); i++) // Ici ...
            if(inputs.at(i) == NULL) // ... on indique les entrees disponibles ...
                uConnOpt->chk_inputs->addItem(tr("Input") +" " +(QString::number(i))); // ... pour le 2eme Item (Recepteur)

    for(int i = 0; i < outputs.size(); i++) // Ici ...
        if(outputs.at(i) == NULL) // ... on indique les sorties disponibles ...
            uConnOpt->chk_outputs->addItem(tr("Output") +" " +(QString::number(i)));  // ... pour le 1er Item (Emetteur)


    if(wConnOpt->exec() == QDialog::Accepted) { // On affiche la fenetre (exec va bloquer l'application sur cette fenetre)

        if(uConnOpt->chk_inputs->currentText() == "" || uConnOpt->chk_outputs->currentText() == "")
            return NULL;

        conn = new Item::s_connect;
        conn->sender = sender; // On indique l'emetteur
        conn->output = uConnOpt->chk_outputs->currentText().split(" ").last().toInt(); // la sortie
        conn->receiver = receiver; // le recepteur
        conn->input = uConnOpt->chk_inputs->currentText().split(" ").last().toInt(); // l'entree
        conn->value = NULL; // et la valeur
    }
    else
        return NULL;


    delete uConnOpt; // On detruit l'interface ...
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

        this->ui->tableView->setShowGrid(uSettings->grid->isChecked()); // on active/desactive la grille en fonction de la case cochee

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

    delete uSettings; // On detruit l'interface ...
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

    switch(index.row()) { // Selon la ligne selectionne dans la liste
    case Item::Input : it = new Input(); // Nouvelle Entree
        break;
    case Item::Output : it = new Output(); // Nouvelle Sortie
            break;
    case Item::Not : it = new Not(); // Nouveau composant de type Not
          break;
    case Item::Or : it = new Or(); // Type Or
        break;
    case Item::Xor : it = new Xor();
        break;
    case Item::XNOr : it = new XNOr(); // Coïncidence
        break;
    case Item::And : it = new And(); // And
        break;
    case Item::Mux : it = new Multiplexer(1); // Multiplexeur avec n = 1 par defaut
        break;
    case Item::Demux : it = new Demultiplexer(1); // Demultiplexeur avec n = 1 par defaut
        break;
    case Item::Node : it = new Node(2);
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
// Name:       void MApp::def_value_valueChanged()
// Purpose:    Implementation of MApp::def_value_valueChanged()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::def_value_valueChanged()
{
    Item *item = this->model->at(this->currentIndex);
    this->model->setDefValueOnInput(item, 1 - item->getAuxValue());
}

////////////////////////////////////////////////////////////////////////
// Name:       void MApp::modify_clicked()
// Purpose:    Implementation of MApp::modify_clicked()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::modify_clicked()
{
    QDialog *wModify = new QDialog(this); // On initialise la fenetre ...
    Ui::Modify *uModify = new Ui::Modify; // ... l'interface ...
    QVector <QCheckBox *> box_i;
    QVector <QCheckBox *> box_o;
    Item *item;
    int plc;

    if((item = this->model->at(this->currentIndex)) == NULL)
            return;

    QVector<Item::s_connect *> outputs = item->getOutputs(); // On recupere les connections sortantes
    QVector<Item::s_connect *> inputs = item->getInputs(); // On recupere les connections entrantes
    box_i.resize(inputs.size());
    box_o.resize(outputs.size());

    uModify->setupUi(wModify); // ... et on les lie
    wModify->setWindowTitle(tr("Modifying") +" " +item->getName());

    uModify->name->setText(item->getName());
    if(item->getClass() == Item::Mux || item->getClass() == Item::Demux || item->getClass() == Item::Node)
        uModify->Inputs->setVisible(true);
    else
        uModify->Inputs->setVisible(false);

    if(item->getClass() == Item::Node)
        uModify->Inputs->setSuffix(" " +tr("Outputs"));
    else
        uModify->Inputs->setSuffix(" " +tr("Adress"));
    uModify->Inputs->setValue(item->getAuxValue());

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
        if(uModify->name->text() != item->getName())
        {
            if(!(this->model->nameIsCorrect(uModify->name->text())))
                QMessageBox::critical(0,tr("Incorrect name"), tr("A name have to be unique and without space."));
            else
                item->setName(uModify->name->text());
        }

        for(int i = 0; i < box_i.size(); i++)
            if(box_i.at(i) != NULL && !box_i.at(i)->isChecked())
                this->model->removeConnexion(inputs.at(i));

        for(int i = 0; i < box_o.size(); i++)
            if(box_o.at(i) != NULL && !box_o.at(i)->isChecked())
                this->model->removeConnexion(outputs.at(i));

        if(item->getClass() == Item::Mux && uModify->Inputs->value() < item->getAuxValue())
            for(int i = uModify->Inputs->value() +1; i < item->getAuxValue() + log2(item->getAuxValue()); i++)
                this->model->removeConnexion(inputs.at(i));

        if(item->getClass() == Item::Demux && uModify->Inputs->value() < item->getAuxValue()) {
            for(int i = uModify->Inputs->value(); i < item->getAuxValue(); i++)
                this->model->removeConnexion(inputs.at(i));
            for(int i = qPow(2,uModify->Inputs->value()); i < qPow(2,item->getAuxValue()); i++)
                this->model->removeConnexion(outputs.at(i));
        }

        if(item->getClass() == Item::Node && uModify->Inputs->value() < item->getAuxValue())
            for(int i = uModify->Inputs->value(); i < item->getAuxValue(); i++)
                this->model->removeConnexion(outputs.at(i));

         this->model->setDefValueOnInput(item, uModify->Inputs->value());
    }

    delete uModify; // On detruit l'interface ...
    delete wModify; // ... et la fenetre
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
    this->loadList();
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
    this->loadList();
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

    ui->tableView->setModel(model); //Indique a la vue d'utiliserle model cree
}

////////////////////////////////////////////////////////////////////////
// Name:       void MApp::on_mode_activated(int index)
// Purpose:    Implementation of MApp::on_mode_activated()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_mode_activated(int index)
{
    this->ui->tableView->enableTracking(false); // On desactive la coloration des cases

    switch(index) {
    case VIEW : this->currentAction = VIEW;
        this->ui->statusBar->showMessage(tr("Select a component on the grid."));
        break;
    case PLACE : this->currentAction = PLACE;
        this->ui->tableView->enableTracking(true); // On active la coloration des cases
        this->ui->statusBar->showMessage(tr("You have to select a position on the grid to place this component."));
        break;

    case CONNECT1 : this->currentAction = CONNECT1;
        this->ui->statusBar->showMessage(tr("You have two click on the first component (sender)."));
        break;
    case DELETE : this->currentAction = DELETE;
        this->ui->statusBar->showMessage(tr("Click one of the component in the grid to delete it."));
        break;
    }

}

////////////////////////////////////////////////////////////////////////
// Name:       void MApp::on_tableView_customContextMenuRequested(const QPoint &pos)
// Purpose:    Implementation of MApp::on_tableView_customContextMenuRequested()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_tableView_customContextMenuRequested(const QPoint &pos)
{
    if(this->currentAction != VIEW) // Si le mode Vue n'est pas active, on annule
        return;

    QMenu *menu = new QMenu(tr("Menu"), this); // On cree un nouveau menu
    this->currentIndex = this->ui->tableView->indexAt(pos); // On recupere l'index dans la grille par rapport a la position de la souris
    Item *item = this->model->at(this->currentIndex); // On recupere le composant par rapport a cet index
    if(item != NULL && item->getClass() == Item::Input) // Si le composant est un Input
        QObject::connect(menu->addAction(tr("Change value to ") +QString::number(1 - item->getAuxValue())), SIGNAL(triggered()), this, SLOT(def_value_valueChanged())); // On offre la possibilite de changer la valeur par defaut

    menu->addAction(tr("Edit"), this, SLOT(modify_clicked()))->setEnabled((item == NULL) ? false : true); // On offre la possibilite d'acceder a la fen^etre d'edition
    menu->move(this->ui->tableView->mapToGlobal(pos)); // On deplace le menu contexuel a la position de la souris
    menu->show(); // On l'affiche
}

////////////////////////////////////////////////////////////////////////
// Name:       void MApp::on_actionAbout_us_triggered()
// Purpose:    Implementation of MApp::on_actionAbout_us_triggered()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_actionAbout_us_triggered()
{
    QDialog* wApropos = new QDialog (this);
    QVBoxLayout *layout = new QVBoxLayout;
    QString propos = "<strong>"+QObject::tr("Electrosim project")+"</strong>:<br/><br/><u><i>"+QObject::tr("Made by")+"</i></u>:<ul><li>Kevyn MONLOUIS</li><li>Paul SALMON</li><li>Brice DUREUIL</li></ul><br/><u><i>"+QObject::tr("Programming language used")+"</u></i>:<ul><li>"+QObject::tr("C++ Language")+"</li></ul><br/><u><i>"+QObject::tr("Framework used")+"</u></i>:<ul><li>Qt 4.8</li></ul><br/><br/>"+QObject::tr("For more informations, visit our")+" <a href=\"http://lorette.github.com/electrosim\">"+QObject::tr("website")+"</a>.";
    QLabel *text = new QLabel(propos);
    text->setOpenExternalLinks(true);
    layout->addWidget(text);
    wApropos->setLayout(layout);
    wApropos->setFixedSize(300,350);
    wApropos->exec();

    delete wApropos;
}

////////////////////////////////////////////////////////////////////////
// Name:       void MApp::on_listWidget_customContextMenuRequested(const QPoint&)
// Purpose:    Implementation of MApp::on_listWidget_customContextMenuRequested()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_listWidget_customContextMenuRequested(const QPoint&)
{
    QDialog *wAcomponent = new QDialog(this); // On initialise la fenetre ...
    Ui::About_component *uAcomponent = new Ui::About_component; // ... l'interface ...
    Item *item = this->getItemInList(); // On recupere un element de la liste

    uAcomponent->setupUi(wAcomponent); // ... on lie la fenetre et l'interface
    uAcomponent->image->setPixmap(QPixmap(item->getImage())); // On affiche l'image

    switch(item->getClass()) { // Selon la classe, on affiche des informations
    case Item::Input : uAcomponent->name->setText(tr("Input"));
        uAcomponent->text->setText("<center><strong>" +tr("Input") +"</strong></center><br /><p>" +tr("An input is where comes from the power supply. The component has only one output but you can place all the inputs you want on the circuit.") +"</p>");
        break;
    case Item::Output : uAcomponent->name->setText(tr("Output"));
        uAcomponent->text->setText("<center><strong>" +tr("Output") +"</strong></center><br /><p>" +tr("An output is where comes out a value of the circuit. The component has only one input but you can place all the outputs you want.") +"</p>");
        break;
    case Item::Not : uAcomponent->name->setText(tr("Not"));
        uAcomponent->text->setText("<center><strong>" +tr("Not") +"</strong></center><br /><p>" +tr("A not gate is a component taking a value as an input and puts the invert of this value on the only one output it has.") +"<br /><br />" +tr("It's the implementation of the logical negation.") +"</p>");
        break;
    case Item::Or : uAcomponent->name->setText(tr("Or"));
        uAcomponent->text->setText("<center><strong>" +tr("Or") +"</strong></center><br /><p>" +tr("A or gate is a component taking 2 values as inputs and puts on its output 1 if one of its inputs is 1 else 0.") +"<br /><br />" +tr("It's the implementation of a type of logical disjunction.") +"</p>");
        break;
    case Item::Xor : uAcomponent->name->setText(tr("Exclusive Or"));
        uAcomponent->text->setText("<center><strong>" +tr("Exclusive Or") +"</strong></center><br /><p>" +tr("A exclusive or gate (or XOr gate) is a component taking 2 values as inputs and puts on its output 1 if only one of its inputs is 1 else 0.") +"<br /><br />" +tr("It's the implementation of a type of logical disjunction.") +"</p>");
        break;
    case Item::XNOr : uAcomponent->name->setText(tr("XNor"));
        uAcomponent->text->setText("<center><strong>" +tr("XNor") +"</strong></center><br /><p>" +tr("A xnor gate (or enor gate) is a component taking 2 values as inputs and puts on its output 1 if the two inputs have the same value else 0.") +"<br /><br />" +tr("It's the implementation of the logical equivalence.") +"</p>");
        break;
    case Item::And : uAcomponent->name->setText(tr("And"));
        uAcomponent->text->setText("<center><strong>" +tr("And") +"</strong></center><br /><p>" +tr("A and gate is a component taking 2 values as inputs and puts on its output 1 if the two inputs have 1 else 0.") +"<br /><br />" +tr("It's the implementation of the logical conjunction.") +"</p>");
        break;
    case Item::Mux : uAcomponent->name->setText(tr("Multiplexer"));
        uAcomponent->text->setText("<center><strong>" +tr("Multiplexer") +"</strong></center><br /><p>" +tr("A multiplexer (or mux) is component selecting one or several inputs and forward to his output the correct value of the input selected by the adress inputs.") +"</p>");
        break;
    case Item::Demux : uAcomponent->name->setText(tr("Demultiplexer"));
        uAcomponent->text->setText("<center><strong>" +tr("Demultiplexer") +"</strong></center><br /><p>" +tr("A demultiplexer (or demux) is component selecting one input and forward it value to the selected output by the adress inputs.") +"</p>");
        break;
    case Item::Node : uAcomponent->name->setText(tr("Node"));
        uAcomponent->text->setText("<center><strong>" +tr("Node") +"</strong></center><br /><p>" +tr("A node is a component taking only one input and forward it value to one or more outputs.") +"</p>");
        break;
    }

    wAcomponent->exec(); // On affiche le tout

    delete item; // On supprime ...
    delete uAcomponent; // ... tout ...
    delete wAcomponent; // ...

}

////////////////////////////////////////////////////////////////////////
// Name:       void MApp::loadList()
// Purpose:    Implementation of MApp::loadList()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::loadList()
{
    this->ui->listWidget->clear();

    ui->listWidget->addItem(new QListWidgetItem(tr("Input"))); // Rajoute une entree a la liste des composants
    ui->listWidget->addItem(new QListWidgetItem(tr("Output"))); // Idem
    ui->listWidget->addItem(new QListWidgetItem(tr("Not"))); // Idem
    ui->listWidget->addItem(new QListWidgetItem(tr("Or"))); // Idem
    ui->listWidget->addItem(new QListWidgetItem(tr("Xor"))); // Idem
    ui->listWidget->addItem(new QListWidgetItem(tr("Equivalence"))); // Idem
    ui->listWidget->addItem(new QListWidgetItem(tr("And"))); // Idem
    ui->listWidget->addItem(new QListWidgetItem(tr("Multiplexer"))); // Idem
    ui->listWidget->addItem(new QListWidgetItem(tr("Demultiplexer"))); // Idem
    ui->listWidget->addItem(new QListWidgetItem(tr("Node"))); // Idem

    this->ui->listWidget->setCurrentRow(0);
}
