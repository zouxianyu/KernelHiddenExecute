/********************************************************************************
** Form generated from reading UI file 'ControlPanel.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLPANEL_H
#define UI_CONTROLPANEL_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlPanelClass
{
public:
    QVBoxLayout *verticalLayout_3;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QStackedWidget *controlStackedWidget;
    QWidget *loaderPage;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *initBtn;
    QSpacerItem *horizontalSpacer_2;
    QWidget *procedurePage;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *safeProcBtn;
    QToolButton *unsafeProcBtn;
    QWidget *attackPage;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *attackBtn;
    QSpacerItem *horizontalSpacer_4;
    QWidget *helperWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *helperLabel;
    QTextBrowser *helperTextBrowser;
    QWidget *outputWidget;
    QVBoxLayout *verticalLayout;
    QLabel *outputLabel;
    QTextBrowser *outputTextBrowser;

    void setupUi(QWidget *ControlPanelClass)
    {
        if (ControlPanelClass->objectName().isEmpty())
            ControlPanelClass->setObjectName(QString::fromUtf8("ControlPanelClass"));
        ControlPanelClass->resize(846, 540);
        verticalLayout_3 = new QVBoxLayout(ControlPanelClass);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        widget = new QWidget(ControlPanelClass);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        controlStackedWidget = new QStackedWidget(widget);
        controlStackedWidget->setObjectName(QString::fromUtf8("controlStackedWidget"));
        loaderPage = new QWidget();
        loaderPage->setObjectName(QString::fromUtf8("loaderPage"));
        horizontalLayout = new QHBoxLayout(loaderPage);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        initBtn = new QToolButton(loaderPage);
        initBtn->setObjectName(QString::fromUtf8("initBtn"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        initBtn->setIcon(icon);
        initBtn->setIconSize(QSize(72, 72));
        initBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        initBtn->setAutoRaise(true);

        horizontalLayout->addWidget(initBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        controlStackedWidget->addWidget(loaderPage);
        procedurePage = new QWidget();
        procedurePage->setObjectName(QString::fromUtf8("procedurePage"));
        horizontalLayout_4 = new QHBoxLayout(procedurePage);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        safeProcBtn = new QToolButton(procedurePage);
        safeProcBtn->setObjectName(QString::fromUtf8("safeProcBtn"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/safeProcedure.png"), QSize(), QIcon::Normal, QIcon::Off);
        safeProcBtn->setIcon(icon1);
        safeProcBtn->setIconSize(QSize(72, 72));
        safeProcBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        safeProcBtn->setAutoRaise(true);

        horizontalLayout_4->addWidget(safeProcBtn);

        unsafeProcBtn = new QToolButton(procedurePage);
        unsafeProcBtn->setObjectName(QString::fromUtf8("unsafeProcBtn"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/unsafeProcedure.png"), QSize(), QIcon::Normal, QIcon::Off);
        unsafeProcBtn->setIcon(icon2);
        unsafeProcBtn->setIconSize(QSize(72, 72));
        unsafeProcBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        unsafeProcBtn->setAutoRaise(true);

        horizontalLayout_4->addWidget(unsafeProcBtn);

        controlStackedWidget->addWidget(procedurePage);
        attackPage = new QWidget();
        attackPage->setObjectName(QString::fromUtf8("attackPage"));
        horizontalLayout_2 = new QHBoxLayout(attackPage);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        attackBtn = new QToolButton(attackPage);
        attackBtn->setObjectName(QString::fromUtf8("attackBtn"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resources/malware.png"), QSize(), QIcon::Normal, QIcon::Off);
        attackBtn->setIcon(icon3);
        attackBtn->setIconSize(QSize(72, 72));
        attackBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        attackBtn->setAutoRaise(true);

        horizontalLayout_2->addWidget(attackBtn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        controlStackedWidget->addWidget(attackPage);

        horizontalLayout_3->addWidget(controlStackedWidget);

        helperWidget = new QWidget(widget);
        helperWidget->setObjectName(QString::fromUtf8("helperWidget"));
        verticalLayout_2 = new QVBoxLayout(helperWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        helperLabel = new QLabel(helperWidget);
        helperLabel->setObjectName(QString::fromUtf8("helperLabel"));

        verticalLayout_2->addWidget(helperLabel);

        helperTextBrowser = new QTextBrowser(helperWidget);
        helperTextBrowser->setObjectName(QString::fromUtf8("helperTextBrowser"));

        verticalLayout_2->addWidget(helperTextBrowser);


        horizontalLayout_3->addWidget(helperWidget);


        verticalLayout_3->addWidget(widget);

        outputWidget = new QWidget(ControlPanelClass);
        outputWidget->setObjectName(QString::fromUtf8("outputWidget"));
        verticalLayout = new QVBoxLayout(outputWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        outputLabel = new QLabel(outputWidget);
        outputLabel->setObjectName(QString::fromUtf8("outputLabel"));

        verticalLayout->addWidget(outputLabel);

        outputTextBrowser = new QTextBrowser(outputWidget);
        outputTextBrowser->setObjectName(QString::fromUtf8("outputTextBrowser"));

        verticalLayout->addWidget(outputTextBrowser);


        verticalLayout_3->addWidget(outputWidget);


        retranslateUi(ControlPanelClass);

        controlStackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ControlPanelClass);
    } // setupUi

    void retranslateUi(QWidget *ControlPanelClass)
    {
        ControlPanelClass->setWindowTitle(QApplication::translate("ControlPanelClass", "ControlPanel", nullptr));
        initBtn->setText(QApplication::translate("ControlPanelClass", "\345\210\235\345\247\213\345\214\226", nullptr));
        safeProcBtn->setText(QApplication::translate("ControlPanelClass", "\345\256\211\345\205\250\347\232\204\350\277\207\347\250\213", nullptr));
        unsafeProcBtn->setText(QApplication::translate("ControlPanelClass", "\344\270\215\345\256\211\345\205\250\347\232\204\350\277\207\347\250\213", nullptr));
        attackBtn->setText(QApplication::translate("ControlPanelClass", "\345\274\200\345\247\213\346\224\273\345\207\273", nullptr));
        helperLabel->setText(QApplication::translate("ControlPanelClass", "\345\270\256\345\212\251\357\274\232", nullptr));
        outputLabel->setText(QApplication::translate("ControlPanelClass", "\347\212\266\346\200\201\350\276\223\345\207\272\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ControlPanelClass: public Ui_ControlPanelClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLPANEL_H
