/***********************************************************************
 * Module:  mapp.h
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: samedi 12 mai 2012 17:14:21
 * Purpose: Declaration of the class MApp
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
 * \date 12 mai 2012
 */

#include <QMainWindow>
#include <QModelIndex>
#include <QStandardItemModel>
#include <QListWidgetItem>
#include <QObject>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QTranslator>
#include <QLabel>
#include <QVector>
#include <QCheckBox>
#include <QMenu>

#include "item.h"
#include "input.h"
#include "output.h"
#include "not.h"
#include "or.h"
#include "and.h"
#include "multiplexer.h"
#include "demultiplexer.h"
#include "xnor.h"
#include "ieo.h"
#include "xor.h"
#include "gridmodel.h"
#include "imagedelegate.h"

namespace Ui {
    class MApp;
    class ConnOpt;
    class Settings;
    class Modify;
    class Verite;
} /*!< Espace de nom pour les interfaces*/

/*! \class MApp
  * \brief Classe MApp :
  *
  *  Classe maitresse, interface avec l'utilisateur.
  */

class MApp : public QMainWindow
{
    Q_OBJECT

public:
    enum Modes {VIEW, PLACE, CONNECT1, DELETE, CONNECT2}; /*!< Enumération des actions*/

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

    /*!
     *  \brief Récupère un item en fonction de la sélection dans la liste.
     *
     *  \return Un item instancié prêt à être placé.
     */
    Item* getItemInList();

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
     *  \brief Slot pour un clic sur le bouton connect'entrée Settings.
     *
     *  Ouvre une fenêtre de configuration.
     */
    void on_actionSettings_triggered();

    /*!
    *  \brief Slot pour un clic sur l'entrée "Charger Un Fichier du menu File.
    *
    *  Ouvre une fenêtre de configuration.
    */
    void on_actionCharger_un_Fichier_triggered();
    /*!
    *  \brief Slot pour un clic sur l'entrée "Sauvegarder Un Circuit" du menu File.
    *
    *  Ouvre une fenêtre de configuration.
    */
    void on_actionSauvegarder_un_Fichier_triggered();

    /*!
     *  \brief Slot pour un clic sur l'entrée Quit.
     *
     *  Quitte l'application.
     */
    void on_actionQuit_triggered();

    /*!
     *  \brief Slot de changement de valeur par défaut.
     *  \param arg1 : Nouvelle valeur
     *
     *  Applique la nouvelle valeur par defaut à l'item courant.
     */
    void def_value_valueChanged();

    /*!
     *  \brief Slot lors d'un clic sur l'icone de modification.
     *
     *  Affiche la fenêtre de modification de l'objet courant.
     */
    void modify_clicked();

    /*!
     *  \brief Slot lors d'un clic sur le bouton de la table de vérité.
     *
     *  Affiche la fenêtre de la table de vérité.
     */
    void on_TableDeVerite_clicked();

    /*!
     *  \brief Slot lors d'un clic sur l'action Francais dans le menu langues.
     *
     *  Change la langue du programme en Francais.
     */
    void on_actionFrench_triggered();

    /*!
     *  \brief Slot lors d'un clic sur l'action Anglais dans le menu langues.
     *
     *  Change la langue du programme en Anglais.
     */
    void on_actionEnglish_triggered();

    /*!
     *  \brief Slot lors d'un clic sur l'action Nouveau dans le menu Fichier.
     *
     *  Crée une nouvelle grille.
     */
    void on_actionNew_triggered();

    /*!
     *  \brief Slot lors d'un changement du mode.
     *
     *  Change l'action courante et applique les modifications associées.
     */
    void on_mode_activated(int index);

    /*!
     *  \brief Slot pour afficher le menu contextuel.
     *  \param pos : position de la souris
     *
     */
    void on_tableView_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MApp *ui; /*!< Interface de la classe*/
    GridModel *model; /*!< Instance du modele courant*/
    Item *currentItem; /*!< Instance du composant séléctionné dans la liste*/
    QModelIndex currentIndex; /*!< Instance de la case dans la grille sélectionné*/
    Modes currentAction; /*!< Action courante*/

};

#endif // MAPP_H
