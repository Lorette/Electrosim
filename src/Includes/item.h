#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QVector>
#include <QObject>
#include <QModelIndex>
#include <QList>
#include <QLine>
#include <QVariant>


class Item : public QObject
{
    Q_OBJECT
public:
    typedef struct {int c; int r; int num_max_input; } s_index;
    typedef struct {Item* sender; int output; Item* receiver; int input; int* value; } s_connect;
    enum Items { Input0, Output1, Not2, Or3, And4, Mux5, Demux6, XNOr7, IeO8};

public:
    explicit Item(QObject *parent = 0);
    virtual ~Item();

    virtual inline QString getName() { return this->name; }
    virtual inline QString getImage() { return this->image; }
    virtual QString getDescription() { return this->description; }
    virtual inline int getClass() { return this->classe; }
    virtual int getAuxValue() { return this->aux; }
    virtual inline QVector<s_connect *> getOutputs() { return this->outputs; }
    virtual inline QVector<s_connect *> getInputs() { return this->inputs; }


    virtual inline void setName(QString name) { this->name = name; }
    virtual bool setAuxValue(int value);

    virtual inline bool addNext(s_connect* conn) { if((conn->output > this->outputs.size()) || (this->outputs.at(conn->output) != NULL) || (!conn->receiver->askForConnection(conn))) return false; this->outputs[conn->output] = conn; QObject::connect(this, SIGNAL(sendSignal()), conn->receiver, SLOT(recvSignal())); this->deleted = false; return true; }
    virtual inline bool askForConnection(s_connect* conn) { if((conn->input > this->inputs.size()) || this->inputs.at(conn->input) != NULL) return false; this->inputs[conn->input] = conn; this->deleted = false; return true;}
    virtual inline bool checkAllValueReceived() { for(int i = 0; i < this->inputs.size(); ++i) if(this->inputs.at(i) == NULL || this->inputs.at(i)->value == NULL ) return false; return true; }
    virtual inline s_connect* deleteInput(int input) { s_connect *conn; if(input < 0 || input > inputs.size()) return NULL; conn = inputs.at(input); inputs[input] = NULL; return conn; }
    virtual inline s_connect* deleteOutput(int output) { s_connect *conn; if(output < 0 || output > outputs.size()) return NULL; conn = outputs.at(output); outputs[output] = NULL; return conn; }
    QList<Item::s_connect *> * getOutputsConnexions();

protected :
    virtual bool _do() = 0;

signals :
    void sendSignal();

public slots:
    virtual inline void recvSignal() { if(this->checkAllValueReceived()) if(this->_do()) emit sendSignal(); }

protected :
    int aux;
    int classe;
    QString name;
    QString description;
    QString image;
    QVector<s_connect *> outputs;
    QVector<s_connect *> inputs;

private :
    bool deleted; // Cette variable �vite de reparcourir toutes les entr�es et les sorties pour la suppression des connections

};

#endif // ITEM_H
