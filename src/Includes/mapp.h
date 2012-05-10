#ifndef MAPP_H
#define MAPP_H

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

class MApp : public QMainWindow
{
    Q_OBJECT

public:
    explicit MApp(QWidget *parent = 0);
    ~MApp();

private:
    Item::s_connect* autoS_connect(Item *sender, Item *receiver);

private slots:
    void on_tableView_clicked(const QModelIndex &index);
    void on_pushButton_clicked();

    void on_actionSettings_triggered();

    void on_Simulate_clicked();

    void on_spn_rotate_valueChanged(int arg1);

    void on_Place_clicked();

    void on_tableView_viewportEntered();

    void on_tableView_activated(const QModelIndex &index);

    void on_listWidget_activated(const QModelIndex &index);

private:
    Ui::MApp *ui;
    GridModel *model;
    Item *currentItem;
    QModelIndex currentIndex;
    int currentAction;

signals:
    void launch(int *value);
};

#endif // MAPP_H
