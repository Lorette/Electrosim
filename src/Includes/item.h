/***********************************************************************
 * Module:  item.h
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: lundi 7 mai 2012 22:45:20
 * Purpose: Declaration of the class Item
 ***********************************************************************/

#ifndef ITEM_H
#define ITEM_H

/*!
 * \file item.h
 * \brief Fichier de la classe mre des composants Item
 * \author SALMON PAUL
 *         MONLOUIS Kevyn
 *         DUREUIL Brice
 * \version 1.0
 * \date 7 mai 2012
 */

#include <QString>
#include <QVector>
#include <QObject>
#include <QModelIndex>
#include <QList>
#include <QLine>
#include <QVariant>

/*! \class Item
  * \brief Classe Item :
  *
  *  Classe mere des différents composants electroniques disponibles dans le logiciel.
  *  Elle implemente les acceusseurs communs a tous les composants et declare les outils
  *  necessaires pour toutes ses classes filles (structure s_connect et fonction de comportement _do).
  *  Elle implemente egalement le slot recvSign et le signal sendSign qui permettent le transfert d'information
  *  des entrees vers les sorties quand une valeur d'entree change (commun a tous les composants).
  */

class Item : public QObject
{
    Q_OBJECT
public:
    /**
     * \struct s_connect item.h
     * \brief Structure d'une connexion
     *
     */
    typedef struct {Item* sender; int output; Item* receiver; int input; int* value; } s_connect;

    /**
     * \enum Items
     * \brief Enumeration de la liste des composants
     *
     */
    enum Items { Input, Output, Not, Or, Xor, XNOr, And, Mux, Demux, Node };

public:
    /*!
     *  \brief Constructeur.
     *
     *  Constructeur de la classe Item.
     *
     *  \param parent : objet parent
     */
    explicit Item(QObject *parent = 0);

    /*!
     *  \brief Recupere le nom de l'item.
     *
     *  \return Renvoie le nom de l'item courant
     */
    QString getName();

    /*!
     *  \brief Recupere l'image de l'item.
     *
     *  \return Renvoie le lien de l'image de l'item courant
     */
    QString getImage();

    /*!
     *  \brief Recupere la description de l'item.
     *
     *  \return Renvoie la classe de l'item courant
     */
    Items getClass();

    /*!
     *  \brief Recupere la valeur auxiliaire de l'item.
     *
     *  \return Renvoie la valeur auxiliaire de l'item courant
     */
    int getAuxValue();

    /*!
     *  \brief Recupere la liste des connexions sortantes de l'item.
     *
     *  \return Renvoie un vecteur composes des connexions sortantes de l'item courant
     */
    QVector<s_connect *> getOutputs();

    /*!
     *  \brief Recupere la liste des connexions entrantes de l'item.
     *
     *  \return Renvoie un vecteur composes des connexions entrantes de l'item courant
     */
    QVector<s_connect *> getInputs();

    /*!
     *  \brief Affecte le nom a un item.
     *  \param name : nouveau nom pour l'item courant
     *
     */
    void setName(QString name);

    /*!
     *  \brief Fonction d'application de la valeur auxiliaire.
     *  \param value : nouvelle valeur pour la variable auxiliaire
     *
     */
    virtual void setAuxValue(int value);

    /*!
     *  \brief Rajoute une connexion a l'item courant et s'occupe de l'indiquer a l'item suivant.
     *  \param conn : connexion a rajouter
     *
     *  \return true si la connexion est reussi sinon false
     */
     bool addNext(s_connect* conn);

    /*!
     *  \brief Rajoute une connexion a l'item courant en entree.
     *  \param conn : connexion a rajouter
     *
     *  \return true si la connexion est reussi sinon false
     */
     bool askForConnection(s_connect* conn);

    /*!
     *  \brief Verifie si toutes les connexions en entree sont faites et qu'elles possedent une valeur.
     *
     *  \return true si toutes les connexions possedent une valeur sinon false
     */
     bool checkAllValueReceived();

    /*!
     *  \brief Retire mais ne supprime pas une connexion en entree, renvoie cette derniere.
     *  \param input : entree sur laquelle retirer la connexion
     *
     *  \return la connexion retiree
     */
     s_connect* deleteInput(int input);

    /*!
     *  \brief Retire mais ne supprime pas une connexion en sortie, renvoie cette derniere.
     *  \param output : sortie sur laquelle retirer la connexion
     *
     *  \return la connexion retiree
     */
     s_connect* deleteOutput(int output);

protected :
    /*!
     *  \brief Fonction de traitement des donnees.
     *
     *  \return true si les donnees ont ete correctement traitees sinon false
     */
    virtual bool _do() = 0;

signals :
    /*!
     *  \brief Signal emis.
     *
     *  Signal emis lorsque le composant courant a effectue son traitement
     *
     */
    void sendSignal();

public slots:
    /*!
     *  \brief Slot execute lorsque un signal est emis.
     *
     *  Slot execute lorsque un item precedent a envoyer son signal provoquant le traitement du composant courant
     *
     */
     void recvSignal();

protected :
    int aux; /*!< Variable auxiliaire*/
    Items classe; /*!< Classe de l'item*/
    QString name; /*!< Nom de l'item*/
    QString image; /*!< Image de l'item*/
    QVector<s_connect *> outputs; /*!< Vecteur des connexions en sortie*/
    QVector<s_connect *> inputs; /*!< Vecteur des connexions en entrees*/

private :
    bool deleted; /*!< Variable indiquant que les connexions entrantes et sortantes sont supprimes*/

};

#endif // ITEM_H
