/********************************************************************************
** Form generated from reading UI file 'Cppturep14224.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CPPTUREP14224_H
#define CPPTUREP14224_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CpptureClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CpptureClass)
    {
        if (CpptureClass->objectName().isEmpty())
            CpptureClass->setObjectName(QStringLiteral("CpptureClass"));
        CpptureClass->resize(600, 400);
        centralWidget = new QWidget(CpptureClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CpptureClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CpptureClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        CpptureClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CpptureClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CpptureClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CpptureClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CpptureClass->setStatusBar(statusBar);

        retranslateUi(CpptureClass);

        QMetaObject::connectSlotsByName(CpptureClass);
    } // setupUi

    void retranslateUi(QMainWindow *CpptureClass)
    {
        CpptureClass->setWindowTitle(QApplication::translate("CpptureClass", "Cppture", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CpptureClass: public Ui_CpptureClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CPPTUREP14224_H
