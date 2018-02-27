/********************************************************************************
** Form generated from reading UI file 'secdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECDIALOG_H
#define UI_SECDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SECDIALG
{
public:
    QWidget *centralWidget;
    QTimeEdit *timeEdit;
    QDateTimeEdit *dateTimeEdit;
    QLabel *label;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;
    QMenuBar *menuBar;
    QMenu *menuLog_In;

    void setupUi(QMainWindow *SECDIALG)
    {
        if (SECDIALG->objectName().isEmpty())
            SECDIALG->setObjectName(QStringLiteral("SECDIALG"));
        SECDIALG->resize(401, 310);
        centralWidget = new QWidget(SECDIALG);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        timeEdit = new QTimeEdit(centralWidget);
        timeEdit->setObjectName(QStringLiteral("timeEdit"));
        timeEdit->setGeometry(QRect(20, 20, 118, 26));
        dateTimeEdit = new QDateTimeEdit(centralWidget);
        dateTimeEdit->setObjectName(QStringLiteral("dateTimeEdit"));
        dateTimeEdit->setGeometry(QRect(20, 50, 194, 26));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 80, 231, 21));
        SECDIALG->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SECDIALG);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SECDIALG->setStatusBar(statusBar);
        mainToolBar = new QToolBar(SECDIALG);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SECDIALG->addToolBar(Qt::TopToolBarArea, mainToolBar);
        menuBar = new QMenuBar(SECDIALG);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 401, 22));
        menuLog_In = new QMenu(menuBar);
        menuLog_In->setObjectName(QStringLiteral("menuLog_In"));
        SECDIALG->setMenuBar(menuBar);

        menuBar->addAction(menuLog_In->menuAction());

        retranslateUi(SECDIALG);

        QMetaObject::connectSlotsByName(SECDIALG);
    } // setupUi

    void retranslateUi(QMainWindow *SECDIALG)
    {
        SECDIALG->setWindowTitle(QApplication::translate("SECDIALG", "MainWindow", nullptr));
        label->setText(QApplication::translate("SECDIALG", "Log In is successful!!", nullptr));
        menuLog_In->setTitle(QApplication::translate("SECDIALG", "Log In", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SECDIALG: public Ui_SECDIALG {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECDIALOG_H
