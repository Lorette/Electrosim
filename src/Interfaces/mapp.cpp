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
    model = new GridModel(9,14);

    ui->setupUi(this);

    ui->tableView->setModel(model);
    ui->tableView->setItemDelegate(new ImageDelegate(this));

    ui->listWidget->addItem(new QListWidgetItem("Input"));
    ui->listWidget->addItem(new QListWidgetItem("Output"));
    ui->listWidget->addItem(new QListWidgetItem("Not"));

    this->currentItem = NULL;
    this->currentAction = VIEW;
}

////////////////////////////////////////////////////////////////////////
// Name:       MApp::~MApp()
// Purpose:    Implementation of MApp::~MApp()
// Return:
////////////////////////////////////////////////////////////////////////

MApp::~MApp()
{
    delete ui;
}

////////////////////////////////////////////////////////////////////////
// Name:       MApp::on_tableView_clicked(const QModelIndex &index)
// Purpose:    Implementation of MApp::on_tableView_clicked()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_tableView_clicked(const QModelIndex &index)
{
    Item *aux = NULL;
    QString name;
    Item::s_connect *conn;
    this->currentIndex = index;

    switch(this->currentAction) {
    case VIEW :
        if((this->currentItem = this->model->at(index)) != NULL) {
            this->ui->name->setText(this->currentItem->getName());
            this->ui->spn_rotate->setEnabled(true);
            this->ui->spn_rotate->setValue(this->currentItem->getRotation());
        }
        else {
            this->ui->name->setText("");
            this->ui->spn_rotate->setEnabled(false);
            this->ui->spn_rotate->setValue(0);
        }
        break;
    case PLACE :
        if(this->currentItem != NULL) {
            if(this->model->at(index) != NULL)
                QMessageBox::critical(0,"Enculé","Hey, fils de pute, ta pas le droit ici");
            else if((name = QInputDialog::getText(this,"Entrez un nom","Entre un nom fils de pute", QLineEdit::Normal, "Item")) != "") {
                this->currentItem->setName(name);
                this->model->addItem(index, this->currentItem);
                if(this->currentItem->getClass() == Item::Input0)
                    QObject::connect(this, SIGNAL(launch(int*)), this->currentItem, SLOT(recvSignal(int*)));
                this->ui->tableView->enableTracking(false);
                this->currentItem = NULL;
                this->currentAction = VIEW;
                this->ui->Place->setText("Place");

            }
        }
        break;

    case CONNECT1 :
        if((this->currentItem = this->model->at(index)) == NULL)
            QMessageBox::critical(this,"Enculé","Vous devez selectionner un objet");
        else
            this->currentAction = CONNECT2;
        break;
    case CONNECT2 :
        if((aux = this->model->at(index)) != NULL && aux != this->currentItem) {
            conn = this->autoS_connect(this->currentItem, aux);

            if(conn != NULL) {
                if(this->model->connexion(conn)) {
                    this->ui->pushButton->setText("Connect");
                    this->currentAction = VIEW;
                }
                else
                    QMessageBox::critical(this,"Erreur","Impossible de connecter ces 2 objets");
            }
        }
        else
            QMessageBox::critical(this,"Enculé","Vous deevez selectionner au moins un objet différent");
        break;

    }

    this->ui->tableView->update(index);
}

////////////////////////////////////////////////////////////////////////
// Name:       MApp::on_connect_clicked()
// Purpose:    Implementation of MApp::on_connect_clicked()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_connect_clicked()
{
    this->currentItem = NULL;
    if(this->currentAction == CONNECT1 || this->currentAction == CONNECT2) {
        this->currentAction = VIEW;
        this->ui->pushButton->setText("Connect");
    }
    else {
        this->currentAction = CONNECT1;
        this->ui->pushButton->setText("Cancel");
        this->ui->Place->setText("Place");
    }

    this->ui->tableView->enableTracking(false);
}

////////////////////////////////////////////////////////////////////////
// Name:       MApp::autoS_connect(Item* sender, Item* receiver)
// Purpose:    Implementation of MApp::autoS_connect()
// Return:     Item::s_connect*
////////////////////////////////////////////////////////////////////////

Item::s_connect* MApp::autoS_connect(Item* sender, Item* receiver) {
    Item::s_connect *conn = new Item::s_connect;
    QDialog *wConnOpt = new QDialog(this);
    Ui::ConnOpt *uConnOpt = new Ui::ConnOpt;

    QVector<Item::s_connect *> outputs = sender->getOutputs();
    QVector<Item::s_connect *> inputs = receiver->getInputs();

    uConnOpt->setupUi(wConnOpt);
    uConnOpt->name_1->setText(sender->getName());
    uConnOpt->name_2->setText(receiver->getName());

    for(int i = 0; i < outputs.size(); i++)
        if(outputs.at(i) == NULL)
            uConnOpt->chk_outputs->addItem(QString::number(i));


    for(int i = 0; i < inputs.size(); i++)
        if(inputs.at(i) == NULL)
            uConnOpt->chk_inputs->addItem(QString::number(i));

    wConnOpt->exec();

    conn->sender = sender;
    conn->output = uConnOpt->chk_outputs->currentText().toInt();
    conn->receiver = receiver;
    conn->input = uConnOpt->chk_inputs->currentText().toInt();
    conn->value = NULL;

    delete uConnOpt;
    delete wConnOpt;

    return conn;
}

////////////////////////////////////////////////////////////////////////
// Name:       MApp::on_actionSettings_triggered()
// Purpose:    Implementation of MApp::on_actionSettings_triggered()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_actionSettings_triggered()
{

    QDialog *wSettings = new QDialog(this);
    Ui::Settings *uSettings = new Ui::Settings;
    uSettings->setupUi(wSettings);

    uSettings->grid->setChecked(this->ui->tableView->showGrid());

    wSettings->exec();

    this->ui->tableView->setShowGrid(uSettings->grid->isChecked());

    delete uSettings;
    delete wSettings;

}

////////////////////////////////////////////////////////////////////////
// Name:       MApp::on_Simulate_clicked()
// Purpose:    Implementation of MApp::on_Simulate_clicked()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_Simulate_clicked()
{
    int *value = new int;
    *value = 1;
    emit launch(value);
}

////////////////////////////////////////////////////////////////////////
// Name:       MApp::on_spn_rotate_valueChanged(int arg1)
// Purpose:    Implementation of MApp::on_spn_rotate_valueChanged()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_spn_rotate_valueChanged(int arg1)
{
    if(this->currentItem != NULL)
        this->currentItem->setRotation(arg1);
    this->ui->tableView->update(this->currentIndex);
}

////////////////////////////////////////////////////////////////////////
// Name:       void MApp::on_Place_clicked()
// Purpose:    Implementation of void MApp::on_Place_clicked()
// Return:     void
////////////////////////////////////////////////////////////////////////

void MApp::on_Place_clicked()
{
    QModelIndex index = ui->listWidget->currentIndex();

    if(this->currentAction == PLACE) {
        this->currentAction = VIEW;
        this->currentItem = NULL;
        this->ui->tableView->enableTracking(false);
        return;
    }

    this->currentAction = PLACE;
    this->currentItem = NULL;
    this->ui->pushButton->setText("Connect");
    this->ui->Place->setText("Cancel");
    this->ui->tableView->enableTracking(true);

    switch(index.row()) {
        case Item::Input0 : this->currentItem = new Input();
            break;
    case Item::Output1 : this->currentItem = new Output();
            break;
    case Item::Not2 : this->currentItem = new Not();
          break;

        default : this->ui->tableView->enableTracking(false);
            this->currentAction = VIEW;
    }

    emit this->ui->tableView->setFocus();
}
