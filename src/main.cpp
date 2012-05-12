#include <QtGui/QApplication>
#include "mapp.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MApp w;

    a.setStyle("plastique");
    w.show();
    
    return a.exec();
}
