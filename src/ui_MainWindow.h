/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "myopenglwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_pixelSetting;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    MyOpenGLWidget *openGLWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_hide_show;
    QSpacerItem *verticalSpacer;
    QWidget *widget_control;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_color;
    QGridLayout *gridLayout_colors;
    QSpacerItem *verticalSpacer_2;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(831, 575);
        action_pixelSetting = new QAction(MainWindow);
        action_pixelSetting->setObjectName(QString::fromUtf8("action_pixelSetting"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        openGLWidget = new MyOpenGLWidget(centralwidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));

        horizontalLayout->addWidget(openGLWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton_hide_show = new QPushButton(centralwidget);
        pushButton_hide_show->setObjectName(QString::fromUtf8("pushButton_hide_show"));
        pushButton_hide_show->setMinimumSize(QSize(21, 20));
        pushButton_hide_show->setMaximumSize(QSize(21, 20));

        horizontalLayout_2->addWidget(pushButton_hide_show);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        widget_control = new QWidget(centralwidget);
        widget_control->setObjectName(QString::fromUtf8("widget_control"));
        gridLayout_2 = new QGridLayout(widget_control);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(6, 6, 6, 6);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_color = new QLabel(widget_control);
        label_color->setObjectName(QString::fromUtf8("label_color"));
        label_color->setMinimumSize(QSize(0, 15));
        label_color->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_color);

        gridLayout_colors = new QGridLayout();
        gridLayout_colors->setObjectName(QString::fromUtf8("gridLayout_colors"));

        verticalLayout_2->addLayout(gridLayout_colors);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 1, 0, 1, 1);


        verticalLayout->addWidget(widget_control);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(2, 15);

        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(0, 7);
        horizontalLayout->setStretch(1, 2);

        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 831, 21));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());
        menu->addAction(action_pixelSetting);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        action_pixelSetting->setText(QApplication::translate("MainWindow", "\345\203\217\347\264\240\347\202\271\346\225\260\351\207\217", nullptr));
        pushButton_hide_show->setText(QApplication::translate("MainWindow", ">>", nullptr));
        label_color->setText(QApplication::translate("MainWindow", "\351\242\234\350\211\262", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
