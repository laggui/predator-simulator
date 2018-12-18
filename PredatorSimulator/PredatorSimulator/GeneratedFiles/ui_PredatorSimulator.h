/********************************************************************************
** Form generated from reading UI file 'PredatorSimulator.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREDATORSIMULATOR_H
#define UI_PREDATORSIMULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PredatorSimulatorClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PredatorSimulatorClass)
    {
        if (PredatorSimulatorClass->objectName().isEmpty())
            PredatorSimulatorClass->setObjectName(QStringLiteral("PredatorSimulatorClass"));
        PredatorSimulatorClass->resize(600, 400);
        centralWidget = new QWidget(PredatorSimulatorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        PredatorSimulatorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PredatorSimulatorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 26));
        PredatorSimulatorClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(PredatorSimulatorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PredatorSimulatorClass->setStatusBar(statusBar);

        retranslateUi(PredatorSimulatorClass);

        QMetaObject::connectSlotsByName(PredatorSimulatorClass);
    } // setupUi

    void retranslateUi(QMainWindow *PredatorSimulatorClass)
    {
        PredatorSimulatorClass->setWindowTitle(QApplication::translate("PredatorSimulatorClass", "PredatorSimulator", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PredatorSimulatorClass: public Ui_PredatorSimulatorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREDATORSIMULATOR_H
