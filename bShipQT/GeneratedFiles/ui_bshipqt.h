/********************************************************************************
** Form generated from reading UI file 'bshipqt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BSHIPQT_H
#define UI_BSHIPQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BShipQTClass
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BShipQTClass)
    {
        if (BShipQTClass->objectName().isEmpty())
            BShipQTClass->setObjectName(QStringLiteral("BShipQTClass"));
        BShipQTClass->resize(748, 421);
        centralWidget = new QWidget(BShipQTClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(-80, -40, 871, 441));
        graphicsView->setMinimumSize(QSize(256, 0));
        graphicsView->setStyleSheet(QLatin1String("background:url(:/BShipQT/Resources/genSplash_fortesting.jpg)\n"
""));
        BShipQTClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BShipQTClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 748, 21));
        BShipQTClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BShipQTClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BShipQTClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BShipQTClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BShipQTClass->setStatusBar(statusBar);

        retranslateUi(BShipQTClass);

        QMetaObject::connectSlotsByName(BShipQTClass);
    } // setupUi

    void retranslateUi(QMainWindow *BShipQTClass)
    {
        BShipQTClass->setWindowTitle(QApplication::translate("BShipQTClass", "BShipQT", 0));
    } // retranslateUi

};

namespace Ui {
    class BShipQTClass: public Ui_BShipQTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BSHIPQT_H
