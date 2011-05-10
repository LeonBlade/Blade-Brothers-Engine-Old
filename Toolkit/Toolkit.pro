#-------------------------------------------------
#
# Project created by QtCreator 2011-05-10T05:15:46
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = Toolkit
TEMPLATE = app

LIBS += -framework OpenGL


SOURCES += main.cpp\
        toolkitwindow.cpp \
    mapwidget.cpp

HEADERS  += toolkitwindow.h \
    mapwidget.h

INCLUDEPATH += ../Engine/include

FORMS    += toolkitwindow.ui

RESOURCES += \
    ../resources/BBEToolkitResources.qrc
