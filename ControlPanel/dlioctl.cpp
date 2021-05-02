#include "dlioctl.h"

ProtectedDriverControl::ProtectedDriverControl()
	:hDevice(INVALID_HANDLE_VALUE)
{
}

ProtectedDriverControl::~ProtectedDriverControl()
{
	close();
}

bool ProtectedDriverControl::open(QString deviceName)
{
	hDevice = CreateFile(deviceName.toStdWString().c_str(),
		GENERIC_WRITE | GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		return false;
	}
}

void ProtectedDriverControl::close()
{
	if (hDevice != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hDevice);
	}
	hDevice = INVALID_HANDLE_VALUE;
}

QString ProtectedDriverControl::safeRead()
{
	QString result;
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		return result;
	}

	DWORD returnedBytes = 0;
	const int bufferSize = 16;
	char outputBuffer[bufferSize] = {};


	DeviceIoControl(hDevice, IOCTL_SAFE_READ, 0, 0, outputBuffer, bufferSize, &returnedBytes, 0);
	if (returnedBytes == 0)
	{
		return result;
	}
	for (int i = 0; i < bufferSize; ++i)
	{
		result += QString::number(outputBuffer[i], 16) + ' ';
	}
	return result;
}

QString ProtectedDriverControl::safeExec()
{
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		return QString();
	}

	DWORD returnedBytes = 0;
	const int bufferSize = 64;
	char outputBuffer[bufferSize] = {};


	DeviceIoControl(hDevice, IOCTL_SAFE_EXEC, 0, 0, outputBuffer, bufferSize, &returnedBytes, 0);
	if (returnedBytes == 0)
	{
		return QString();
	}
	return QString(outputBuffer);
}

QString ProtectedDriverControl::unsafeRead()
{
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		return QString();
	}
}

QString ProtectedDriverControl::unsafeExec()
{
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		return QString();
	}
}

MalwareDriverControl::MalwareDriverControl()
	:hDevice(INVALID_HANDLE_VALUE)
{
}

MalwareDriverControl::~MalwareDriverControl()
{
	close();
}

bool MalwareDriverControl::open(QString deviceName)
{
	hDevice = CreateFile(deviceName.toStdWString().c_str(),
		GENERIC_WRITE | GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		return false;
	}
}

void MalwareDriverControl::close()
{
	if (hDevice != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hDevice);
	}
	hDevice = INVALID_HANDLE_VALUE;
}

bool MalwareDriverControl::attack()
{
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		return false;
	}
}