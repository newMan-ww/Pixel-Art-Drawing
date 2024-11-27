/********************************************************************************
** Form generated from reading UI file 'DialogPixelSetting.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGPIXELSETTING_H
#define UI_DIALOGPIXELSETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_DialogPixelSetting
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_row;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_column;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_cancel;

    void setupUi(QDialog *DialogPixelSetting)
    {
        if (DialogPixelSetting->objectName().isEmpty())
            DialogPixelSetting->setObjectName(QString::fromUtf8("DialogPixelSetting"));
        DialogPixelSetting->resize(202, 134);
        DialogPixelSetting->setMinimumSize(QSize(202, 134));
        gridLayout = new QGridLayout(DialogPixelSetting);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(DialogPixelSetting);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(11);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        lineEdit_row = new QLineEdit(DialogPixelSetting);
        lineEdit_row->setObjectName(QString::fromUtf8("lineEdit_row"));
        lineEdit_row->setFont(font);

        horizontalLayout->addWidget(lineEdit_row);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 3);

        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(DialogPixelSetting);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_2);

        lineEdit_column = new QLineEdit(DialogPixelSetting);
        lineEdit_column->setObjectName(QString::fromUtf8("lineEdit_column"));
        lineEdit_column->setFont(font);

        horizontalLayout_2->addWidget(lineEdit_column);

        horizontalLayout_2->setStretch(0, 2);
        horizontalLayout_2->setStretch(1, 3);

        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(81, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButton_ok = new QPushButton(DialogPixelSetting);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));
        pushButton_ok->setMinimumSize(QSize(40, 23));
        pushButton_ok->setFont(font);

        horizontalLayout_3->addWidget(pushButton_ok);

        pushButton_cancel = new QPushButton(DialogPixelSetting);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));
        pushButton_cancel->setMinimumSize(QSize(40, 23));
        pushButton_cancel->setFont(font);

        horizontalLayout_3->addWidget(pushButton_cancel);

        horizontalLayout_3->setStretch(0, 4);
        horizontalLayout_3->setStretch(1, 1);
        horizontalLayout_3->setStretch(2, 1);

        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);


        retranslateUi(DialogPixelSetting);

        QMetaObject::connectSlotsByName(DialogPixelSetting);
    } // setupUi

    void retranslateUi(QDialog *DialogPixelSetting)
    {
        DialogPixelSetting->setWindowTitle(QApplication::translate("DialogPixelSetting", "Dialog", nullptr));
        label->setText(QApplication::translate("DialogPixelSetting", "\346\250\252\345\220\221\346\225\260\351\207\217", nullptr));
        label_2->setText(QApplication::translate("DialogPixelSetting", "\347\272\265\345\220\221\346\225\260\351\207\217", nullptr));
        pushButton_ok->setText(QApplication::translate("DialogPixelSetting", "\342\210\232", nullptr));
        pushButton_cancel->setText(QApplication::translate("DialogPixelSetting", "\303\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogPixelSetting: public Ui_DialogPixelSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGPIXELSETTING_H
