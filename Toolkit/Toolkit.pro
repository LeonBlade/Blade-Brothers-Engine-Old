#-------------------------------------------------
#
# Project created by QtCreator 2011-05-25T07:37:49
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = Toolkit
TEMPLATE = app

INCLUDEPATH += ../Engine/inclue

LIBS += -framework libpng -framework SDL -lSDLmain -framework Cocoa -L../Engine/Debug/source/ -lgraphics/Sprite.o -lcore/Map.o -lcore/Vector2.o

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    ../resources/resources.qrc
