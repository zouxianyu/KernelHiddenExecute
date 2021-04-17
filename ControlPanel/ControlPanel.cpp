#include "ControlPanel.h"

ControlPanel::ControlPanel(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    //initialize buttons connection
    connect(ui.initBtn, &QPushButton::clicked, this, &ControlPanel::initialize);
    connect(ui.attackBtn, &QPushButton::clicked, this, &ControlPanel::attack);
    connect(ui.unsafeProcBtn, &QPushButton::clicked, this, &ControlPanel::normalProcedure);
    connect(ui.safeProcBtn, &QPushButton::clicked, this, &ControlPanel::protectedProcedure);
}

void ControlPanel::initialize()
{
    qDebug()<<"initialize";
    ui.controlStackedWidget->setCurrentIndex(1);
}

void ControlPanel::attack()
{
    qDebug() << "attack";
}

void ControlPanel::normalProcedure()
{
    qDebug() << "normalProcedure";
}

void ControlPanel::protectedProcedure()
{
    qDebug() << "protectedProcedure";
}

void ControlPanel::closeEvent(QCloseEvent* event)
{
    qDebug() << "closeEvent";
	if (QMessageBox::question(this,
		"退出",
		"确定要退出吗？",
		QMessageBox::Yes, QMessageBox::No)
		== QMessageBox::Yes) 
    {
        //TODO:uninitialize drivers

		event->accept();
	}
    else
    {
        event->ignore();
    }
		
}
