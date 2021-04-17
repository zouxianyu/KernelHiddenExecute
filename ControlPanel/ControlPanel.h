#pragma once

#include <QtWidgets/QWidget>
#include <QPushButton>
#include <QDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include "ui_ControlPanel.h"

class ControlPanel : public QWidget
{
	Q_OBJECT

public:
	ControlPanel(QWidget *parent = Q_NULLPTR);

public slots:
	void initialize();
	void attack();
	void normalProcedure();
	void protectedProcedure();

protected:
	void closeEvent(QCloseEvent * event);
private:
	Ui::ControlPanelClass ui;
	bool initialized;
	bool isSafeProcExecuted1;
	bool isUnsafeProcExecuted1;
	bool isAttacked;
	bool isSafeProcExecuted2;
	bool isUnsafeProcExecuted2;
	


};
