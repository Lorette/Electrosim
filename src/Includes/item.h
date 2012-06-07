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
 * \brief Fichier de la classe m�re des composants Item
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
  *  Classe m�re des composants de type Item.
  */

class Item : public QObject
{
    Q_OBJECT
public:
    typedef struct {Item* sender; int output; Item* receiver; int input; int* value; } s_connect; /*!< Structure d'une connexion*/
    enum Items { Input, Output, Not, Or, Xor, XNOr, And, Mux, Demux, IeO }; /*!< Enum�ration de la liste des composants*/

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
     *  \brief R�cup�re le nom de l'item.
     *
     *  \return Renvoie le nom de l'item courant
     */
    inline QString getName() { return this->name; }

    /*!
     *  \brief R�cup�re l'image de l'item.
     *
     *  \return Renvoie le lien de l'image de l'item courant
     */
    inline QString getImage() { return this->image; }

    /*!
     *  \brief R�cup�re la description de l'item.
     *
     *  \return Renvoie la description de l'item courant
     */
    QString getDescription() { return this->description; }

    /*!
     *  \brief R�cup�re la classe de l'item.
     *
     *  \return Renvoie la classe de l'item courant
     */
    inline int getClass() { return this->classe; }

    /*!
     *  \brief R�cup�re la valeur auxiliaire de l'item.
     *
     *  \return Renvoie la valeur auxiliaire de l'item courant
     */
    int getAuxValue() { return this->aux; }

    /*!
     *  \brief R�cup�re la liste des connexions sortantes de l'item.
     *
     *  \return Renvoie un vecteur compos�s des connexions sortantes de l'item courant
     */
    inline QVector<s_connect *> getOutputs() { return this->outputs; }

    /*!
     *  \brief R�cup�re la liste des connexions entrantes de l'item.
     *
     *  \return Renvoie un vecteur compos�s des connexions entrantes de l'item courant
     */
    inline QVector<s_connect *> getInputs() { return this->inputs; }

    /*!
     *  \brief Affecte le nom � un item.
     *  \param name : nouveau nom pour l'item courant
     *
     */
    inline void setName(QString name) { this->name = name; }

    /*!
     *  \brief Fonction d'application de la valeur auxiliaire.
     *  \param value : nouvelle valeur pour la variable auxiliaire
     *
     */
    virtual void setAuxValue(int value);

    /*!
     *  \brief Rajoute une connexion � l'item courant et s'occupe de l'indiquer � l'item suivant.
     *  \param conn : connexion � rajouter
     *
     *  \return true si la connexion est r�ussi sinon false
     */
    inline bool addNext(s_connect* conn) { if((conn->output > this->outputs.size()) || (this->outputs.at(conn->output) != NULL) || (!conn->receiver->askForConnection(conn))) return false; this->outputs[conn->output] = conn; QObject::connect(this, SIGNAL(sendSignal()), conn->receiver, SLOT(recvSignal())); this->deleted = false; return true; }

    /*!
     *  \brief Rajoute une connexion � l'item courant en entr�e.
     *  \param conn : connexion � rajouter
     *
     *  \return true si la connexion est r�ussi sinon false
     */
    inline bool askForConnection(s_connect* conn) { if((conn->input > this->inputs.size()) || this->inputs.at(conn->input) != NULL) return false; this->inputs[conn->input] = conn; this->deleted = false; return true;}

    /*!
     *  \brief V�rifie si toutes les connexions en entr�e sont faites et qu'elles poss�dent une valeur.
     *
     *  \return true si toutes les connexions poss�dent une valeur sinon false
     */
    inline bool checkAllValueReceived() { for(int i = 0; i < this->inputs.size(); ++i) if(this->inputs.at(i) == NULL || this->inputs.at(i)->value == NULL ) return false; return true; }

    /*!
     *  \brief Retire mais ne supprime pas une connexion en entr�e, renvoie cette derni�re.
     *  \param input : entr�e sur laquelle retirer la connexion
     *
     *  \return la connexion retir�e
     */
    inline s_connect* deleteInput(int input) { s_connect *conn; if(input < 0 || input > inputs.size()) return NULL; conn = inputs.at(input); inputs[input] = NULL; return conn; }

    /*!
     *  \brief Retire mais ne supprime pas une connexion en sortie, renvoie cette derni�re.
     *  \param output : sortie sur laquelle retirer la connexion
     *
     *  \return la connexion retir�e
     */
    inline s_connect* deleteOutput(int output) { s_connect *conn; if(output < 0 || output > outputs.size()) return NULL; conn = outputs.at(output); outputs[output] = NULL; return conn; }

protected :
    /*!
     *  \brief Fonction de traitement des donn�es.
     *
     *  \return true si les donn�es ont �t� correctement trait�es sinon false
     */
    virtual bool _do() = 0;

signals :
    /*!
     *  \brief Signal �mis.
     *
     *  Signal �mis lorsque le composant courant a effectu� son traitement
     *
     */
    void sendSignal();

public slots:
    /*!
     *  \brief Slot execut� lorsque un signal est �mis.
     *
     *  Slot execut� lorsque un item pr�c�dent a envoyer son signal provoquant le traitement du composant courant
     *
     */
    inline void recvSignal() { if(this->checkAllValueReceived()) if(this->_do()) emit sendSignal(); }

protected :
    int aux; /*!< Variable auxiliaire*/
    int classe; /*!< Classe de l'item*/
    QString name; /*!< Nom de l'item*/
    QString description; /*!< Description de l'item*/
    QString image; /*!< Image de l'item*/
    QVector<s_connect *> outputs; /*!< Vecteur des connexions en sortie*/
    QVector<s_connect *> inputs; /*!< Vecteur des connexions en entr�es*/

private :
    bool deleted; /*!< Variable indiquant que les connexions entrantes et sortantes sont supprim�es*/

};

#endif // ITEM_H
