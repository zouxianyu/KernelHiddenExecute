#pragma once
#pragma execution_character_set("utf-8")

#include <QtWidgets/QWidget>
#include <QPushButton>
#include <QDebug>
#include <QCloseEvent>
#include <QMessageBox>
#include <QDir>
#include "ui_ControlPanel.h"
#include "dlcommon.h"
#include "dlservices.h"
#include "dldrivers.h"
#include "dlioctl.h"

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
	//bool isSafeProcExecuted1;
	//bool isUnsafeProcExecuted1;
	//bool isAttacked;
	//bool isSafeProcExecuted2;
	//bool isUnsafeProcExecuted2;
	QString protectedServiceName;
	QString protectedServiceDisplayName;
	QString protectedDriverPath;
	QString protectedDeviceName;
	ProtectedDriverControl protectedDriverControl;
	QString malwareServiceName;
	QString malwareServiceDisplayName;
	QString malwareDriverPath;
	QString malwareDeviceName;
	MalwareDriverControl malwareDriverControl;

	bool loadDriver(QString driverPath, QString serviceName, QString serviceDisplayName);
	bool unloadDriver(QString serviceName);
};
