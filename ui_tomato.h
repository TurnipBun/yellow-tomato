/********************************************************************************
** Form generated from reading UI file 'tomato.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOMATO_H
#define UI_TOMATO_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include "analogclock.h"

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    AnalogClock *analogClock;
    QProgressBar *progress30;
    QProgressBar *progress1440;
    QLCDNumber *lcdCount;
    QPushButton *pushDone;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(400, 100);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Dialog->sizePolicy().hasHeightForWidth());
        Dialog->setSizePolicy(sizePolicy);
        Dialog->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/favicon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        Dialog->setWindowIcon(icon);
        analogClock = new AnalogClock(Dialog);
        analogClock->setObjectName(QString::fromUtf8("analogClock"));
        analogClock->setGeometry(QRect(0, 0, 100, 100));
        sizePolicy.setHeightForWidth(analogClock->sizePolicy().hasHeightForWidth());
        analogClock->setSizePolicy(sizePolicy);
        analogClock->setContextMenuPolicy(Qt::NoContextMenu);
        progress30 = new QProgressBar(Dialog);
        progress30->setObjectName(QString::fromUtf8("progress30"));
        progress30->setGeometry(QRect(110, 20, 150, 20));
        sizePolicy.setHeightForWidth(progress30->sizePolicy().hasHeightForWidth());
        progress30->setSizePolicy(sizePolicy);
        progress30->setContextMenuPolicy(Qt::NoContextMenu);
        progress30->setMaximum(30);
        progress30->setValue(10);
        progress30->setTextVisible(false);
        progress1440 = new QProgressBar(Dialog);
        progress1440->setObjectName(QString::fromUtf8("progress1440"));
        progress1440->setGeometry(QRect(110, 60, 280, 20));
        sizePolicy.setHeightForWidth(progress1440->sizePolicy().hasHeightForWidth());
        progress1440->setSizePolicy(sizePolicy);
        progress1440->setContextMenuPolicy(Qt::NoContextMenu);
        progress1440->setMaximum(1440);
        progress1440->setValue(300);
        progress1440->setTextVisible(false);
        lcdCount = new QLCDNumber(Dialog);
        lcdCount->setObjectName(QString::fromUtf8("lcdCount"));
        lcdCount->setGeometry(QRect(270, 20, 50, 20));
        lcdCount->setContextMenuPolicy(Qt::NoContextMenu);
        pushDone = new QPushButton(Dialog);
        pushDone->setObjectName(QString::fromUtf8("pushDone"));
        pushDone->setGeometry(QRect(330, 20, 60, 20));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "yellow-tomato", nullptr));
#ifndef QT_NO_TOOLTIP
        analogClock->setToolTip(QApplication::translate("Dialog", "The current time", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        analogClock->setWhatsThis(QApplication::translate("Dialog", "The analog clock widget displays the current time.", nullptr));
#endif // QT_NO_WHATSTHIS
        pushDone->setText(QApplication::translate("Dialog", "\345\256\214\346\210\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOMATO_H
