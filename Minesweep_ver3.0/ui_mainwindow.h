/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.1.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionJunior;
    QAction *actionMiddle;
    QAction *actionSenior;
    QAction *actionCreators;
    QAction *actionCustom;
    QAction *actionCHEAT;
    QAction *actionRanking;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuMap;
    QMenu *menuAbout;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionJunior = new QAction(MainWindow);
        actionJunior->setObjectName(QString::fromUtf8("actionJunior"));
        actionMiddle = new QAction(MainWindow);
        actionMiddle->setObjectName(QString::fromUtf8("actionMiddle"));
        actionSenior = new QAction(MainWindow);
        actionSenior->setObjectName(QString::fromUtf8("actionSenior"));
        actionCreators = new QAction(MainWindow);
        actionCreators->setObjectName(QString::fromUtf8("actionCreators"));
        actionCustom = new QAction(MainWindow);
        actionCustom->setObjectName(QString::fromUtf8("actionCustom"));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("Customize");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        actionCustom->setIcon(icon);
        actionCHEAT = new QAction(MainWindow);
        actionCHEAT->setObjectName(QString::fromUtf8("actionCHEAT"));
        actionRanking = new QAction(MainWindow);
        actionRanking->setObjectName(QString::fromUtf8("actionRanking"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuMap = new QMenu(menubar);
        menuMap->setObjectName(QString::fromUtf8("menuMap"));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuMap->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuMap->addAction(actionJunior);
        menuMap->addAction(actionMiddle);
        menuMap->addAction(actionSenior);
        menuMap->addAction(actionCustom);
        menuAbout->addAction(actionCHEAT);
        menuAbout->addAction(actionRanking);
        menuAbout->addAction(actionCreators);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionJunior->setText(QCoreApplication::translate("MainWindow", "Junior", nullptr));
        actionMiddle->setText(QCoreApplication::translate("MainWindow", "Middle", nullptr));
        actionSenior->setText(QCoreApplication::translate("MainWindow", "Senior", nullptr));
        actionCreators->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionCustom->setText(QCoreApplication::translate("MainWindow", "Customize", nullptr));
#if QT_CONFIG(tooltip)
        actionCustom->setToolTip(QCoreApplication::translate("MainWindow", "Customize", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCHEAT->setText(QCoreApplication::translate("MainWindow", "Cheat", nullptr));
#if QT_CONFIG(tooltip)
        actionCHEAT->setToolTip(QCoreApplication::translate("MainWindow", "Cheat", nullptr));
#endif // QT_CONFIG(tooltip)
        actionRanking->setText(QCoreApplication::translate("MainWindow", "Rank", nullptr));
        menuMap->setTitle(QCoreApplication::translate("MainWindow", "Map", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("MainWindow", "Other", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
