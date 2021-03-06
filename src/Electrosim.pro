######################################################################
# Automatically generated by qmake (2.01a) sam. 7. avr. 22:16:16 2012
######################################################################

QT += core gui widgets

TEMPLATE = app
TARGET = Electrosim

DEPENDPATH += . \
              Models \
              Views \
              Forms \
              Interfaces \
              Items
			  
INCLUDEPATH += Includes

HEADERS += Includes/gridmodel.h \
           Includes/input.h \
           Includes/output.h \
           Includes/mapp.h \
           Includes/gridview.h \
           Includes/not.h \
           Includes/imagedelegate.h \
           Includes/item.h \
           Includes/or.h \
           Includes/and.h \
           Includes/multiplexer.h \
           Includes/demultiplexer.h \
           Includes/xnor.h \
           Includes/node.h \
           Includes/xor.h
		   
FORMS += Forms/mapp.ui \
         Forms/conn_option.ui \
         Forms/settings.ui \
         Forms/modify.ui \
         Forms/verite.ui \
         Forms/about_component.ui

SOURCES += main.cpp \
           Interfaces/mapp.cpp \
           Models/gridmodel.cpp \
           Views/gridview.cpp \
           Views/imagedelegate.cpp \
           Items/or.cpp \
           Items/not.cpp \
           Items/and.cpp \
           Items/multiplexer.cpp \
           Items/demultiplexer.cpp \
           Items/xnor.cpp \
           Items/node.cpp \
           Items/xor.cpp \
           Items/item.cpp \
           Items/input.cpp \
           Items/output.cpp


RESOURCES += Ressources/bn.qrc

win32:RC_FILE += Ressources/ico.rc

TRANSLATIONS = Ressources/Translations/en.ts \
               Ressources/Translations/fr.ts
