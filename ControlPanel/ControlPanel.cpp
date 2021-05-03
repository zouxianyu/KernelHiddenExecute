#include "ControlPanel.h"

ControlPanel::ControlPanel(QWidget* parent)
	: QWidget(parent),
	//initialize strings
	protectedServiceName("KernelHiddenExecute"),
	protectedServiceDisplayName("Kernel Hidden Execute"),
	//protectedDriverPath(".\\sys\\protected.sys"),
	protectedDeviceName("\\\\.\\KernelHiddenExecute"),
	protectedDriverControl(),
	malwareServiceName("KernelHiddenExecuteMalware"),
	malwareServiceDisplayName("Kernel Hidden Execute Malware"),
	//malwareDriverPath(".\\sys\\malware.sys"),
	malwareDeviceName("\\\\.\\KernelHiddenExecuteMalware"),
	malwareDriverControl(),
	//initialize bool variables
	initialized(false),
	isSafeProcExecuted1(false),
	isUnsafeProcExecuted1(false),
	isAttacked(false),
	isSafeProcExecuted2(false),
	isUnsafeProcExecuted2(false)
{
	ui.setupUi(this);

	//initialize buttons connection
	connect(ui.initBtn, &QPushButton::clicked, this, &ControlPanel::initialize);
	connect(ui.attackBtn, &QPushButton::clicked, this, &ControlPanel::attack);
	connect(ui.unsafeProcBtn, &QPushButton::clicked, this, &ControlPanel::normalProcedure);
	connect(ui.safeProcBtn, &QPushButton::clicked, this, &ControlPanel::protectedProcedure);

	//fix relative path
	QDir protectedDriverDir("./sys/KernelHiddenExecute.sys");
	protectedDriverPath = protectedDriverDir.absolutePath().replace(QString("/"), QString("\\"));

	QDir malwareDriverDir("./sys/KernelHiddenExecuteMalware.sys");
	malwareDriverPath = malwareDriverDir.absolutePath().replace(QString("/"), QString("\\"));
	//qDebug() << protectedDriverPath.toStdString().c_str();
	//qDebug() << malwareDriverPath.toStdString().c_str();
}

void ControlPanel::initialize()
{
	qDebug() << "initialize";
	if (initialized)
	{
		return;
	}
	//initialize service control manager
	ui.outputTextBrowser->append("��ʼ��ʼ��SCM");
	if (Services::init() == false)
	{
		ui.outputTextBrowser->append("SCM��ʼ��ʧ��");
		return;
	}
	ui.outputTextBrowser->append("SCM��ʼ���ɹ�");

	//load protected driver
	//TODO:FIX ABSOLUTE PATH
	ui.outputTextBrowser->append("��ʼ���ر������ĳ���");
	if (!loadDriver(protectedDriverPath, protectedServiceName, protectedServiceDisplayName))
	{
		return;
	}

	//load malware driver
	ui.outputTextBrowser->append("��ʼ���ض������");
	if (!loadDriver(malwareDriverPath, malwareServiceName, malwareServiceDisplayName))
	{
		return;
	}

	//open drivers handle
	ui.outputTextBrowser->append("��ʼ���ӵ��������ĳ���");
	if (!protectedDriverControl.open(protectedDeviceName))
	{
		ui.outputTextBrowser->append("��ʧ��");
		return;
	}
	ui.outputTextBrowser->append("�򿪳ɹ�");

	ui.outputTextBrowser->append("��ʼ���ӵ��������");
	if (!malwareDriverControl.open(malwareDeviceName))
	{
		ui.outputTextBrowser->append("��ʧ��");
		return;
	}
	ui.outputTextBrowser->append("�򿪳ɹ�");

	initialized = true;

	//scroll to next page
	ui.controlStackedWidget->setCurrentIndex(1);
}

void ControlPanel::attack()
{
	qDebug() << "attack";
	if (!malwareDriverControl.attack())
	{
		ui.outputTextBrowser->append("����ʧ��");
	}
	ui.outputTextBrowser->append("�����ɹ�");
}

void ControlPanel::normalProcedure()
{
	qDebug() << "normalProcedure";
	ui.outputTextBrowser->append("��ʼ��ʾδ�ܱ����Ĺ���");
	ui.outputTextBrowser->append(QString("��ȡ�����ݣ�") + protectedDriverControl.unsafeRead());
	ui.outputTextBrowser->append(QString("ִ�еĽ����") + protectedDriverControl.unsafeExec());
}

void ControlPanel::protectedProcedure()
{
	qDebug() << "protectedProcedure";
	ui.outputTextBrowser->append("��ʼ��ʾ�ܱ����Ĺ���");
	ui.outputTextBrowser->append(QString("��ȡ�����ݣ�") + protectedDriverControl.safeRead());
	ui.outputTextBrowser->append(QString("ִ�еĽ����") + protectedDriverControl.safeExec());
}

void ControlPanel::closeEvent(QCloseEvent* event)
{
	qDebug() << "closeEvent";
	if (QMessageBox::question(this, "�˳�", "ȷ��Ҫ�˳���", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
	{
		//unload drivers
		malwareDriverControl.close();
		protectedDriverControl.close();
		unloadDriver(malwareServiceName);
		unloadDriver(protectedServiceName);

		//ui.outputTextBrowser->append("ж����");
		//QThread::sleep(2);


		//uninitialize SCM
		Services::uninit();

		event->accept();
	}
	else
	{
		event->ignore();
	}

}

bool ControlPanel::loadDriver(QString driverPath, QString serviceName, QString serviceDisplayName)
{
	unsigned long registrationResult = Services::Register(driverPath,
		serviceName,
		serviceDisplayName,
		"Demand",
		"Normal");
	switch (registrationResult) {
	case ERROR_SERVICE_EXISTS:
		ui.outputTextBrowser->append("Service registration failed. The service already exists.");
		break;

	case 1:
		ui.outputTextBrowser->append("Service registration failed. Empty or invalid parameters have been provided.");
		return false;

	case 0:
		ui.outputTextBrowser->append("Service registration succeeded.");
		break;

	default:
		ui.outputTextBrowser->append(QString("Service registration failed. Error code %1.").arg(registrationResult));
		return false;
	}

	unsigned long startResult = Services::Start(serviceName);

	switch (startResult) {
	case 1:
		ui.outputTextBrowser->append("Starting service failed.");
		return false;

	case ERROR_SHARING_VIOLATION:
		ui.outputTextBrowser->append("The process cannot access the file because it is being used by another process.");
		return false;

	case ERROR_SERVICE_DOES_NOT_EXIST:
		ui.outputTextBrowser->append("The specified service does not exist as an installed service.");
		return false;

	case ERROR_SERVICE_ALREADY_RUNNING:
		ui.outputTextBrowser->append("An instance of the service is already running.");
		break;

	case 0:
		ui.outputTextBrowser->append("Service started.");
		break;

	default:
		ui.outputTextBrowser->append(QString("Starting service failed. Error code %1.").arg(startResult));
		return false;
	}

	return true;
}

bool ControlPanel::unloadDriver(QString serviceName)
{
	//if (!initialized)
	//{
	//	return false;
	//}

	unsigned long stopResult = Services::Stop(serviceName);

	switch (stopResult) {
	case 1:
		ui.outputTextBrowser->append("Stopping service failed.");
		break;

	case ERROR_SERVICE_NOT_ACTIVE:
		ui.outputTextBrowser->append("The service has not been started.");
		break;

	case ERROR_SERVICE_DOES_NOT_EXIST:
		ui.outputTextBrowser->append("The specified service does not exist as an installed service.");
		break;

	case 0:
		ui.outputTextBrowser->append("Service stopped.");
		break;

	default:
		ui.outputTextBrowser->append(QString("Stopping service failed. Error code %1.").arg(stopResult));
		break;
	}

	unsigned long unregistrationResult = Services::Unregister(serviceName);
	bool unregResult = false;

	switch (unregistrationResult) {
	case 1:
		ui.outputTextBrowser->append("Service unregistration failed.");
		unregResult = false;
		break;

	case ERROR_SERVICE_DOES_NOT_EXIST:
		ui.outputTextBrowser->append("The specified service does not exist as an installed service.");
		unregResult = false;
		break;

	case 0:
		ui.outputTextBrowser->append("Service unregistration succeeded.");
		unregResult = true;
		break;

	default:
		ui.outputTextBrowser->append(QString("Service unregistration failed. Error code %1.").arg(unregistrationResult));
		unregResult = false;
		break;
	}
	//initialized = false;
	return unregResult;
}
