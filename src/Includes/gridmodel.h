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
 * \brief Modèle de la grille
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
#include "item.h"

/*! \class GridModel
  * \brief Classe GridModel :
  *
  *  Classe du modèle de la grille.
  */

class GridModel : public QAbstractItemModel
{

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
     *  \brief Crée un index.
     *  \param row : numéro de la ligne
     *  \param column : numéro de la colonne
     *  \param parent : index parent
     *
     *  \return l'index crée.
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
     *  \param parent : index par défaut
     *
     *  \return le nombre de ligne.
     */
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

    /*!
     *  \brief Renvoie le nombre de colonne.
     *  \param parent : index par défaut
     *
     *  \return le nombre de colonne.
     */
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    /*!
     *  \brief Renvoie une information en fonction d'un index et d'un rôle.
     *  \param index : index
     *  \parem role : role
     *
     *  \return l'information.
     */
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    /*!
     *  \brief Ajoute une valeur au modèle en fonction d'un index et d'un rôle
     *  \param index : index
     *  \parem value : valeur
     *  \parem role : role
     *
     *  \return true si l'action s'est correctement terminée sinon false.
     */
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);

    /*!
     *  \brief Insert une colonne à partir d'une position
     *  \param column : position où insérer une colonne
     *  \parem parent : index du parent
     *
     *  \return true si l'action s'est correctement terminée sinon false.
     */
    bool insertColumn(int column, const QModelIndex &parent = QModelIndex());

    /*!
     *  \brief Insert une ligne à partir d'une position
     *  \param row : position où insérer une ligne
     *  \parem parent : index du parent
     *
     *  \return true si l'action s'est correctement terminée sinon false.
     */
    bool insertRow(int row, const QModelIndex &parent = QModelIndex());

    /*!
     *  \brief Insert des colonnes à partir d'une position
     *  \param column : position où insérer les colonnes
     *  \param count : nombre de colonnes
     *  \parem parent : index du parent
     *
     *  \return true si l'action s'est correctement terminée sinon false.
     */
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex());

    /*!
     *  \brief Insert des lignes à partir d'une position
     *  \param rows : position où insérer les lignes
     *  \param count : nombre de lignes
     *  \parem parent : index du parent
     *
     *  \return true si l'action s'est correctement terminée sinon false.
     */
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());

    /*!
     *  \brief Renvoie l'item situé dans le modèle
     *  \parem index : index
     *
     *  \return l'item ou NULL.
     */
    Item* at(const QModelIndex &index);

    /*!
     *  \brief Rajoute un item à un index donné
     *  \parem index : index
     *  \item : item à rajouter
     *
     *  \return true si l'action s'est correctement terminée sinon false.
     */
    bool addItem(const QModelIndex &index, Item* item);

    /*!
     *  \brief Rajoute une connexion
     *  \parem conn : connexion
     *
     *  \return true si l'action s'est correctement terminée sinon false.
     */
    bool connexion(Item::s_connect* conn);

private :
    int column_count; /*!< Nombre de colonnes*/
    int row_count; /*!< Nombre de lignes*/
    QVector< QVector<Item*> > items; /*!< Données du modèle*/
    QModelIndex current_modelIndex; /*!< Index courant*/

};

#endif // GRIDMODEL_H
