/***********************************************************************
 * Module:  gridmodel.h
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: samedi 12 mai 2012 17:15:14
 * Purpose: Declaration of the class GridModel
 ***********************************************************************/

#ifndef GRIDMODEL_H
#define GRIDMODEL_H

/*!
 * \file gridmodel.h
 * \brief Modele de la grille
 * \author SALMON PAUL
 *         MONLOUIS Kevyn
 *         DUREUIL Brice
 * \version 1.0
 * \date 12 mai 2012
 */

#include <QAbstractItemModel>
#include <QVector>
#include <QMessageBox>
#include <QIcon>
#include <QPair>
#include <qmath.h>
#include <QFile>
#include <QTextStream>

#include "input.h"
#include "output.h"
#include "item.h"
#include "not.h"
#include "and.h"
#include "or.h"
#include "multiplexer.h"
#include "demultiplexer.h"
#include "xnor.h"
#include "node.h"
#include "xor.h"

/*! \class GridModel
  * \brief Classe GridModel :
  *
  *  Classe du modele de la grille.
  */

class GridModel : public QAbstractItemModel
{

    Q_OBJECT
public:
    /*!
     *  \brief Constructeur.
     *
     *  Constructeur de la classe GridModel.
     *  \param rows : nombre de lignes
     *  \param columns : nombre de colonnes
     */
    explicit GridModel(int rows = 0, int columns = 0);

    /*!
     *  \brief Destructeur.
     *
     *  Destructeur de la classe GridModel.
     */
    ~GridModel();

    /*!
     *  \brief Cree un index.
     *  \param row : numero de la ligne
     *  \param column : numero de la colonne
     *  \param parent : index parent
     *
     *  \return l'index cree.
     */
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

    /*!
     *  \brief Renvoie l'index du parent.
     *  \param child : index du file
     *
     *  \return l'index du parent.
     */
    virtual QModelIndex parent(const QModelIndex &child) const;

    /*!
     *  \brief Renvoie le nombre de ligne.
     *  \param parent : index par defaut
     *
     *  \return le nombre de ligne.
     */
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

    /*!
     *  \brief Renvoie le nombre de colonne.
     *  \param parent : index par defaut
     *
     *  \return le nombre de colonne.
     */
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    /*!
     *  \brief Renvoie une information en fonction d'un index et d'un rôle.
     *  \param index : index
     *  \param role : role
     *
     *  \return l'information.
     */
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    /*!
     *  \brief Ajoute une valeur au modele en fonction d'un index et d'un rôle
     *  \param index : index
     *  \param value : valeur
     *  \param role : role
     *
     *  \return true si l'action s'est correctement terminee sinon false.
     */
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);

    /*!
     *  \brief Insert une colonne a partir d'une position
     *  \param column : position où inserer une colonne
     *  \param parent : index du parent
     *
     *  \return true si l'action s'est correctement terminee sinon false.
     */
    bool insertColumn(int column, const QModelIndex &parent = QModelIndex());

    /*!
     *  \brief Supprime une colonne a partir d'une position
     *  \param column : position où supprimer la colonne
     *  \param parent : index du parent
     *
     *  \return true si l'action s'est correctement terminee sinon false.
     */
    bool removeColumn(int column, const QModelIndex &parent = QModelIndex());

    /*!
     *  \brief Insert une ligne a partir d'une position
     *  \param row : position où inserer une ligne
     *  \param parent : index du parent
     *
     *  \return true si l'action s'est correctement terminee sinon false.
     */
    bool insertRow(int row, const QModelIndex &parent = QModelIndex());

    /*!
     *  \brief Supprime une ligne a partir d'une position
     *  \param row : position où supprimer la ligne
     *  \param parent : index du parent
     *
     *  \return true si l'action s'est correctement terminee sinon false.
     */
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());

    /*!
     *  \brief Insert des colonnes a partir d'une position
     *  \param column : position où inserer les colonnes
     *  \param count : nombre de colonnes
     *  \param parent : index du parent
     *
     *  \return true si l'action s'est correctement terminee sinon false.
     */
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex());

    /*!
     *  \brief Supprime des colonnes a partir d'une position
     *  \param column : position où supprimer les colonnes
     *  \param count : nombre de colonnes
     *  \param parent : index du parent
     *
     *  \return true si l'action s'est correctement terminee sinon false.
     */
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex());

    /*!
     *  \brief Insert des lignes a partir d'une position
     *  \param row : position où inserer les lignes
     *  \param count : nombre de lignes
     *  \param parent : index du parent
     *
     *  \return true si l'action s'est correctement terminee sinon false.
     */
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());

    /*!
     *  \brief Supprime des lignes a partir d'une position
     *  \param row : position où supprimer les lignes
     *  \param count : nombre de lignes
     *  \param parent : index du parent
     *
     *  \return true si l'action s'est correctement terminee sinon false.
     */
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

    /*!
     *  \brief Renvoie l'item situe dans le modele
     *  \param index : index
     *
     *  \return l'item ou NULL.
     */
    Item* at(const QModelIndex &index);

    /*!
     *  \brief Rajoute un item a un index donne
     *  \param index : index
     *  \param item : item a rajouter
     *
     *  \return true si l'action s'est correctement terminee sinon false.
     */
    bool addItem(const QModelIndex &index, Item* item);

    /*!
     *  \brief Rajoute une connexion
     *  \param conn : connexion
     *
     *  \return true si l'action s'est correctement terminee sinon false.
     */
    bool connexion(Item::s_connect* conn);

    /*!
     *  \brief Supprime un item a un index donne
     *  \param index : index
     *
     *  \return true si l'action s'est correctement terminee sinon false.
     */
    bool removeItem(const QModelIndex &index);

    /*!
     *  \brief Reinitialise toutes les connexions a NULL
     *
     *  \return true si l'action s'est correctement terminee sinon false.
     */
    bool resetAllConnexions();

    /*!
     *  \brief Lance la simulation
     *
     */
    void simulate();

    /*! \brief Donne la table de verite du circuit.
     *
     *  \return une paire dont le premier element est la legende
     *          (un tableau donnant pour chaque colonne le nom du
     *          composant correspondant) et le deuxieme element est
     *          la table de verite du circuit.
     */
    QPair <QVector < QString >, QVector< QVector < int > > >  verite();

    /*! \brief Applique une variable auxiliaire a un element.
     *  \param item : l'element auquel donnee la valeur
     *  \param value : la valeur a appliquee
     *  \return true si la valeur auxiliaire a bien ete appliquee sinon false
     */
    bool setDefValueOnInput(Item *item, int value);

    /*!
    *  \brief Sauvegarde le circuit dans le fichier file
    *  \param file : fichier de sauvegarde
    *
    *  \return true si la sauvegarde a eu lieu false sinon
    */
    bool saveInFile(QFile* file);

    /*!
    *  \brief Charge le circuit a partir le fichier file
    *  \param file : fichier elec ou txt
    *
    *  \return le modele du fichier
    */
    static GridModel* loadFromFile(QFile* file);

    /*!
    *  \brief Renvoi l'item a partir d'un nom
    *  \param name : nom de l'item recherche
    *
    *  \return l'item recherche, NULL si l'item n'existe pas
    */
    Item* findChildByName(QString name);

    /*!
     *  \brief Indique si un nom est correcte.
     *  Un nom est considere correcte s'il n'est pas deja utilise et ne contient aucun espace.
     *
     *  \param name : nom a tester.
     *
     *  \return true si le nom est correcte, false sinon.
     */
    bool nameIsCorrect(const QString& name) const;

    /*!
     *  \brief Supprime une connexion.
     *  \param conn : connexion a supprimer
     *
     *  Supprime une connexion et informe l'emetteur et le recepteur de la suppression.
     *
     *  \return true si la connexion a bien ete supprimer, false sinon.
     */
    bool removeConnexion(Item::s_connect* conn);

    /*!
     *  \brief Recupere les connexions d'un item et les transforment en ligne.
     *  \param it : Item cible.
     *
     *  \return une liste de ligne cast en type variable.
     */
    QList<QVariant> getConnexions(Item *it) const ;

    /*!
     *  \brief Recupere la position d'un item donnee dans la grille.
     *  \param item : item cibl"
     *
     *  \return les positions sous forme d'index.
     */
    QModelIndex getIndex(Item *item) const;
signals:
    /*!
     *  \brief Signal emis pour lancer la simulation.
     *
     *  Lance la simulation.
     */
    void launch();

private :
    int column_count; /*!< Nombre de colonnes*/
    int row_count; /*!< Nombre de lignes*/
    QVector< QVector<Item*> > items; /*!< Donnees du modele*/
    QList <Item *> inputs; /*!< Entrees du modele*/
    QList <Item *> outputs; /*!< Sorties du modele*/
    QModelIndex current_modelIndex; /*!< Index courant*/
    QList <Item::s_connect *> connexions; /*!< Connexions du modele*/
};

#endif // GRIDMODEL_H
