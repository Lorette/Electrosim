/***********************************************************************
 * Module:  mapp.h
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: samedi 12 mai 2012 17:14:21
 * Purpose: Declaration of the class Ihm
 ***********************************************************************/

#ifndef MAPP_H
#define MAPP_H

/*!
 * \file mapp.h
 * \brief Interface Homme Machine, Contrôleur
 * \author SALMON PAUL
 *         MONLOUIS Kevyn
 *         DUREUIL Brice
 * \version 1.0
 * \date 12 mai 2011
 */

#include <QMainWindow>
#include <QModelIndex>
#include <QStandardItemModel>
#include <QListWidgetItem>
#include <QObject>
#include <QMessageBox>
#include <QInputDialog>

#include "item.h"
#include "input.h"
#include "output.h"
#include "not.h"
#include "gridmodel.h"
#include "imagedelegate.h"



enum Actions {
    VIEW,
    PLACE,
    CONNECT1,
    CONNECT2
};


namespace Ui {
    class MApp;
    class ConnOpt;
    class Settings;
}

/*! \class MApp
  * \brief Classe MApp :
  *
  *  Classe maitresse, interface avec l'utilisateur.
  */

class MApp : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     *  \brief Constructeur.
     *
     *  Constructeur de la classe MApp.
     *  \param parent : pointeur sur un widget parent
     */
    explicit MApp(QWidget *parent = 0);

    /*!
     *  \brief Destructeur.
     *
     *  Destructeur de la classe MApp
     */
    ~MApp();

private:
    /*!
     *  \brief Crée une connexion de type s_connect entre 2 Items.
     *  \param sender : pointeur sur l'Item qui envoie le signal
     *  \param receiver : pointeur sur l'Item qui reçoit le signal
     *
     *  \return la connexion de type s_connect ou NULL si erreur.
     */
    Item::s_connect* autoS_connect(Item *sender, Item *receiver);

private slots:
    /*!
     *  \brief Slot pour un clic sur la grille.
     *
     *  Effectue une suite d'actions en fonction de l'action courante et de la position du clic.
     */
    void on_tableView_clicked(const QModelIndex &index);
    /*!
     *  \brief Slot pour un clic sur le bouton connect.
     *
     *  Active une action de connexion.
     */
    void on_connect_clicked();
    /*!
     *  \brief Slot pour un clic sur le bouton connect'entrée Settings.
     *
     *  Ouvre une fenêtre de configuration.
     */
    void on_actionSettings_triggered();
    /*!
     *  \brief Slot pour un clic sur le bouton Simulate.
     *
     *  Lance la simulation du circuit.
     */
    void on_Simulate_clicked();
    /*!
     *  \brief Slot pour un clic sur le bouton Place.
     *
     *  Place (ou annule l'action) un item selectionné dans la liste.
     */
    void on_Place_clicked();



private:
    Ui::MApp *ui; /*!< Interface de la classe*/
    GridModel *model; /*!< Instance du modele courant*/
    Item *currentItem; /*!< Instance du composant séléctionné dans la liste*/
    QModelIndex currentIndex; /*!< Instance de la case dans la grille sélectionné*/
    int currentAction; /*!< Action courante*/

signals:
    /*!
     *  \brief Signal émis pour lancer la simulation.
     *  \param value : valeur de départ.
     *
     *  Lance la simulation.
     */
    void launch(int *value);
};

#endif // MAPP_H
