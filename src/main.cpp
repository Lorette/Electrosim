/***********************************************************************
 * Module:  main.cpp
 * Author:  SALMON PAUL
 *          MONLOUIS Kevyn
 *          DUREUIL Brice
 * Modified: lundi 30 avril 2012 22:05:33
 * Purpose: Implementation of the function main
 ***********************************************************************/

#include <QApplication>
#include "mapp.h"

////////////////////////////////////////////////////////////////////////
// Name:       int main(int argc, char *argv[])
// Purpose:    Implementation of main()
// Return:     int
////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MApp w;

    a.setStyle("plastique");
    w.show();
    
    return a.exec();
}
