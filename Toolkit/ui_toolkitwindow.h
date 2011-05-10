/********************************************************************************
** Form generated from reading UI file 'toolkitwindow.ui'
**
** Created: Tue May 10 07:29:11 2011
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOLKITWINDOW_H
#define UI_TOOLKITWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QScrollArea>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include "mapwidget.h"

QT_BEGIN_NAMESPACE

class Ui_ToolkitWindow
{
public:
    QAction *actionNew_Map;
    QAction *actionOpen_Map;
    QAction *actionSave_Map;
    QAction *actionSave_as;
    QAction *actionQuit;
    QAction *actionProperties;
    QAction *actionGround;
    QAction *actionMiddle;
    QAction *actionTop;
    QAction *actionCollision;
    QAction *actionRun;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QScrollArea *mapScrollArea;
    MapWidget *mapWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuMap;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *tilesetDockWidget;
    QWidget *dockWidgetContents;

    void setupUi(QMainWindow *ToolkitWindow)
    {
        if (ToolkitWindow->objectName().isEmpty())
            ToolkitWindow->setObjectName(QString::fromUtf8("ToolkitWindow"));
        ToolkitWindow->resize(897, 594);
        actionNew_Map = new QAction(ToolkitWindow);
        actionNew_Map->setObjectName(QString::fromUtf8("actionNew_Map"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/toolkit_icons/icons/new_button.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew_Map->setIcon(icon);
        actionOpen_Map = new QAction(ToolkitWindow);
        actionOpen_Map->setObjectName(QString::fromUtf8("actionOpen_Map"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/toolkit_icons/icons/open_button.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_Map->setIcon(icon1);
        actionSave_Map = new QAction(ToolkitWindow);
        actionSave_Map->setObjectName(QString::fromUtf8("actionSave_Map"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/toolkit_icons/icons/save_button.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_Map->setIcon(icon2);
        actionSave_as = new QAction(ToolkitWindow);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        actionQuit = new QAction(ToolkitWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionProperties = new QAction(ToolkitWindow);
        actionProperties->setObjectName(QString::fromUtf8("actionProperties"));
        actionGround = new QAction(ToolkitWindow);
        actionGround->setObjectName(QString::fromUtf8("actionGround"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/toolkit_icons/icons/bottom_layer_button.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGround->setIcon(icon3);
        actionMiddle = new QAction(ToolkitWindow);
        actionMiddle->setObjectName(QString::fromUtf8("actionMiddle"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/toolkit_icons/icons/middle_layer_button.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMiddle->setIcon(icon4);
        actionTop = new QAction(ToolkitWindow);
        actionTop->setObjectName(QString::fromUtf8("actionTop"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/toolkit_icons/icons/top_layer_button.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTop->setIcon(icon5);
        actionCollision = new QAction(ToolkitWindow);
        actionCollision->setObjectName(QString::fromUtf8("actionCollision"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/toolkit_icons/icons/collision_layer_button.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCollision->setIcon(icon6);
        actionRun = new QAction(ToolkitWindow);
        actionRun->setObjectName(QString::fromUtf8("actionRun"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/toolkit_icons/icons/run_button.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRun->setIcon(icon7);
        centralWidget = new QWidget(ToolkitWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        mapScrollArea = new QScrollArea(centralWidget);
        mapScrollArea->setObjectName(QString::fromUtf8("mapScrollArea"));
        mapScrollArea->setAutoFillBackground(false);
        mapScrollArea->setFrameShape(QFrame::NoFrame);
        mapScrollArea->setFrameShadow(QFrame::Plain);
        mapScrollArea->setLineWidth(0);
        mapScrollArea->setWidgetResizable(true);
        mapScrollArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        mapWidget = new MapWidget();
        mapWidget->setObjectName(QString::fromUtf8("mapWidget"));
        mapWidget->setGeometry(QRect(0, 0, 16, 16));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mapWidget->sizePolicy().hasHeightForWidth());
        mapWidget->setSizePolicy(sizePolicy);
        mapScrollArea->setWidget(mapWidget);

        horizontalLayout->addWidget(mapScrollArea);

        ToolkitWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ToolkitWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 897, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuMap = new QMenu(menuBar);
        menuMap->setObjectName(QString::fromUtf8("menuMap"));
        ToolkitWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ToolkitWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ToolkitWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ToolkitWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ToolkitWindow->setStatusBar(statusBar);
        tilesetDockWidget = new QDockWidget(ToolkitWindow);
        tilesetDockWidget->setObjectName(QString::fromUtf8("tilesetDockWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tilesetDockWidget->sizePolicy().hasHeightForWidth());
        tilesetDockWidget->setSizePolicy(sizePolicy1);
        tilesetDockWidget->setMinimumSize(QSize(160, 42));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        tilesetDockWidget->setWidget(dockWidgetContents);
        ToolkitWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), tilesetDockWidget);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuMap->menuAction());
        menuFile->addAction(actionNew_Map);
        menuFile->addAction(actionOpen_Map);
        menuFile->addSeparator();
        menuFile->addAction(actionSave_Map);
        menuFile->addAction(actionSave_as);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuMap->addAction(actionProperties);
        menuMap->addSeparator();
        menuMap->addAction(actionGround);
        menuMap->addAction(actionMiddle);
        menuMap->addAction(actionTop);
        menuMap->addAction(actionCollision);
        menuMap->addSeparator();
        menuMap->addAction(actionRun);
        mainToolBar->addAction(actionNew_Map);
        mainToolBar->addAction(actionOpen_Map);
        mainToolBar->addAction(actionSave_Map);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionGround);
        mainToolBar->addAction(actionMiddle);
        mainToolBar->addAction(actionTop);
        mainToolBar->addAction(actionCollision);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionRun);

        retranslateUi(ToolkitWindow);

        QMetaObject::connectSlotsByName(ToolkitWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ToolkitWindow)
    {
        ToolkitWindow->setWindowTitle(QApplication::translate("ToolkitWindow", "Blade Brothers Engine Toolkit", 0, QApplication::UnicodeUTF8));
        actionNew_Map->setText(QApplication::translate("ToolkitWindow", "New", 0, QApplication::UnicodeUTF8));
        actionOpen_Map->setText(QApplication::translate("ToolkitWindow", "Open", 0, QApplication::UnicodeUTF8));
        actionSave_Map->setText(QApplication::translate("ToolkitWindow", "Save", 0, QApplication::UnicodeUTF8));
        actionSave_as->setText(QApplication::translate("ToolkitWindow", "Save as ...", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("ToolkitWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionProperties->setText(QApplication::translate("ToolkitWindow", "Properties", 0, QApplication::UnicodeUTF8));
        actionGround->setText(QApplication::translate("ToolkitWindow", "Ground", 0, QApplication::UnicodeUTF8));
        actionMiddle->setText(QApplication::translate("ToolkitWindow", "Middle", 0, QApplication::UnicodeUTF8));
        actionTop->setText(QApplication::translate("ToolkitWindow", "Top", 0, QApplication::UnicodeUTF8));
        actionCollision->setText(QApplication::translate("ToolkitWindow", "Collision", 0, QApplication::UnicodeUTF8));
        actionRun->setText(QApplication::translate("ToolkitWindow", "Run", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("ToolkitWindow", "File", 0, QApplication::UnicodeUTF8));
        menuMap->setTitle(QApplication::translate("ToolkitWindow", "Map", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        tilesetDockWidget->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        tilesetDockWidget->setWindowTitle(QApplication::translate("ToolkitWindow", "Tileset", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ToolkitWindow: public Ui_ToolkitWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLKITWINDOW_H
