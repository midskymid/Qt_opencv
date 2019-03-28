/********************************************************************************
** Form generated from reading UI file 'Qt_opencv.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_OPENCV_H
#define UI_QT_OPENCV_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Qt_opencvClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Qt_opencvClass)
    {
        if (Qt_opencvClass->objectName().isEmpty())
            Qt_opencvClass->setObjectName(QStringLiteral("Qt_opencvClass"));
        Qt_opencvClass->resize(600, 400);
        menuBar = new QMenuBar(Qt_opencvClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        Qt_opencvClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Qt_opencvClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Qt_opencvClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Qt_opencvClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Qt_opencvClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Qt_opencvClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Qt_opencvClass->setStatusBar(statusBar);

        retranslateUi(Qt_opencvClass);

        QMetaObject::connectSlotsByName(Qt_opencvClass);
    } // setupUi

    void retranslateUi(QMainWindow *Qt_opencvClass)
    {
        Qt_opencvClass->setWindowTitle(QApplication::translate("Qt_opencvClass", "Qt_opencv", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Qt_opencvClass: public Ui_Qt_opencvClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_OPENCV_H
