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
 * \brief Mod�le de la grille
 * \author SALMON PAUL
 *         MONLOUIS Kevyn
 *         DUREUIL Brice
 * \version 1.0
 * \date 12 mai 2011
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

/*! \class GridModel
  * \brief Classe GridModel :
  *
  *  Classe du mod�le de la grille.
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
     *  \param rows : nombre de lignes
     *  \param columns : nombre de colonnes
     */
    ~GridModel();

    /*!
     *  \brief Cr�e un index.
     *  \param row : num�ro de la ligne
     *  \param column : num�ro de la colonne
     *  \param parent : index parent
     *
     *  \return l'index cr�e.
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
     *  \param parent : index par d�faut
     *
     *  \return le nombre de ligne.
     */
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

    /*!
     *  \brief Renvoie le nombre de colonne.
     *  \param parent : index par d�faut
     *
     *  \return le nombre de colonne.
     */
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    /*!
     *  \brief Renvoie une information en fonction d'un index et d'un r�le.
     *  \param index : index
     *  \param role : role
     *
     *  \return l'information.
     */
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    /*!
     *  \brief Ajoute une valeur au mod�le en fonction d'un index et d'un r�le
     *  \param index : index
     *  \param value : valeur
     *  \param role : role
     *
     *  \return true si l'action s'est correctement termin�e sinon false.
     */
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);

    /*!
     *  \brief Insert une colonne � partir d'une position
     *  \param column : position o� ins�rer une colonne
     *  \param parent : index du parent
     *
     *  \return true si l'action s'est correctement termin�e sinon false.
     */
    bool insertColumn(int column, const QModelIndex &parent = QModelIndex());

    /*!
     *  \brief Supprime une colonne � partir d'une position
     *  \param column : position o� supprimer la colonne
     *  \param parent : index du parent
     *
     *  \return true si l'action s'est correctement termin�e sinon false.
     */
    bool removeColumn(int column, const QModelIndex &parent = QModelIndex());

    /*!
     *  \brief Insert une ligne � partir d'une position
     *  \param row : position o� ins�rer une ligne
     *  \param parent : index du parent
     *
     *  \return true si l'action s'est correctement termin�e sinon false.
     */
    bool insertRow(int row, const QModelIndex &parent = QModelIndex());

    /*!
     *  \brief Supprime une ligne � partir d'une position
     *  \param row : position o� supprimer la ligne
     *  \param parent : index du parent
     *
     *  \return true si l'action s'est correctement termin�e sinon false.
     */
    bool removeRow(int row, const QModelIndex &parent = QModelIndex());

    /*!
     *  \brief Insert des colonnes � partir d'une position
     *  \param column : position o� ins�rer les colonnes
     *  \param count : nombre de colonnes
     *  \param parent : index du parent
     *
     *  \return true si l'action s'est correctement termin�e sinon false.
     */
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex());

    /*!
     *  \brief Supprime des colonnes � partir d'une position
     *  \param column : position o� supprimer les colonnes
     *  \param count : nombre de colonnes
     *  \param parent : index du parent
     *
     *  \return true si l'action s'est correctement termin�e sinon false.
     */
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex());

    /*!
     *  \brief Insert des lignes � partir d'une position
     *  \param rows : position o� ins�rer les lignes
     *  \param count : nombre de lignes
     *  \param parent : index du parent
     *
     *  \return true si l'action s'est correctement termin�e sinon false.
     */
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());

    /*!
     *  \brief Supprime des lignes � partir d'une position
     *  \param rows : position o� supprimer les lignes
     *  \param count : nombre de lignes
     *  \param parent : index du parent
     *
     *  \return true si l'action s'est correctement termin�e sinon false.
     */
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

    /*!
     *  \brief Renvoie l'item situ� dans le mod�le
     *  \param index : index
     *
     *  \return l'item ou NULL.
     */
    Item* at(const QModelIndex &index);

    /*!
     *  \brief Rajoute un item � un index donn�
     *  \param index : index
     *  \item : item � rajouter
     *
     *  \return true si l'action s'est correctement termin�e sinon false.
     */
    bool addItem(const QModelIndex &index, Item* item);

    /*!
     *  \brief Rajoute une connexion
     *  \param conn : connexion
     *
     *  \return true si l'action s'est correctement termin�e sinon false.
     */
    bool connexion(Item::s_connect* conn);

    /*!
     *  \brief Supprime un item � un index donn�
     *  \param index : index
     *
     *  \return true si l'action s'est correctement termin�e sinon false.
     */
    bool removeItem(const QModelIndex &index);

    /*!
     *  \brief R�initialise toutes les connexions � NULL
     *
     *  \return true si l'action s'est correctement termin�e sinon false.
     */
    bool resetAllConnexions();

    /*!
     *  \brief Lance la simulation
     *
     */
    void simulate();

    /*! \brief Donne la table de v�rit� du circuit.
     *
     *  \return une paire dont le premier �l�ment est la l�gende
     *          (un tableau donnant pour chaque colonne le nom du
     *          composant correspondant) et le deuxi�me �l�ment est
     *          la table de v�rit� du circuit.
     */
    QPair <QVector < QString >, QVector< QVector < int > > >  verite();

    bool setDefValueOnInput(Item *item, int value);

    /*!
    *  \brief Sauvegarde le circuit dans le fichier file
    *  \param file : fichier de sauvegarde
    *
    *  \return true si la sauvegarde a eu lieu false sinon
    */
    bool saveInFile(QFile* file);

    /*!
    *  \brief Charge le circuit � partir le fichier file
    *  \param file : fichier elec ou txt
    *
    *  \return le modele du fichier
    */
    static GridModel* loadFromFile(QFile* file);

    /*!
    *  \brief Renvoi l'item � partir d'un nom
    *  \param name : nom de l'item recherch�
    *
    *  \return l'item recherch�, NULL si l'item n'existe pas
    */
    Item* findChildByName(QString name);

    /*!
     *  \brief Indique si un nom est d�j� utilis� par un composant.
     *
     *  \param name : nom � tester.
     *
     *  \return true si le nom est d�j� utilis�, false sinon.
     */
    bool nameIsUsed(QString& name) const;


signals:
    /*!
     *  \brief Signal �mis pour lancer la simulation.
     *
     *  Lance la simulation.
     */
    void launch();

private :
    int column_count; /*!< Nombre de colonnes*/
    int row_count; /*!< Nombre de lignes*/
    QVector< QVector<Item*> > items; /*!< Donn�es du mod�le*/
    QList <Item *> inputs;
    QList <Item *> outputs;
    QModelIndex current_modelIndex; /*!< Index courant*/
    QList <Item::s_connect *> connexions; /*!< Connexions du mod�le*/
};

#endif // GRIDMODEL_H
