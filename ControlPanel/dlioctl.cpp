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
	return true;
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
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		return QString("INVALID_HANDLE_VALUE");
	}

	DWORD returnedBytes = 0;
	const int bufferSize = 64;
	char outputBuffer[bufferSize] = {};

	if (!DeviceIoControl(hDevice, IOCTL_SAFE_READ, NULL, 0, outputBuffer, bufferSize, &returnedBytes, 0))
	{
		return QString("DeviceIoControl failed");
	}
	return QString(outputBuffer);
}

QString ProtectedDriverControl::safeExec()
{
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		return QString("INVALID_HANDLE_VALUE");
	}

	DWORD returnedBytes = 0;
	const int bufferSize = 64;
	char inputBuffer[bufferSize] = "wrongPassword";
	char outputBuffer[bufferSize] = {};


	if (!DeviceIoControl(hDevice, IOCTL_SAFE_EXEC, inputBuffer, bufferSize, outputBuffer, bufferSize, &returnedBytes, 0))
	{
		return QString("DeviceIoControl failed");
	}
	return QString(*(int*)outputBuffer ? "verification success" : "verification failed");
}

QString ProtectedDriverControl::unsafeRead()
{
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		return QString("INVALID_HANDLE_VALUE");
	}

	DWORD returnedBytes = 0;
	const int bufferSize = 64;
	char outputBuffer[bufferSize] = {};

	if (!DeviceIoControl(hDevice, IOCTL_UNSAFE_READ, NULL, 0, outputBuffer, bufferSize, &returnedBytes, 0))
	{
		return QString("DeviceIoControl failed");
	}
	return QString(outputBuffer);
}

QString ProtectedDriverControl::unsafeExec()
{
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		return QString("INVALID_HANDLE_VALUE");
	}

	DWORD returnedBytes = 0;
	const int bufferSize = 64;
	char inputBuffer[bufferSize] = "wrongPassword";
	char outputBuffer[bufferSize] = {};


	if (!DeviceIoControl(hDevice, IOCTL_UNSAFE_EXEC, inputBuffer, bufferSize, outputBuffer, bufferSize, &returnedBytes, 0))
	{
		return QString("DeviceIoControl failed");
	}
	return QString(*(int*)outputBuffer ? "verification success" : "verification failed");
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
	return true;
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

	DWORD returnedBytes = 0;
	const int bufferSize = 64;
	char outputBuffer[bufferSize] = {};

	if (!DeviceIoControl(hDevice, IOCTL_ATTACK, NULL, 0, outputBuffer, bufferSize, &returnedBytes, 0))
	{
		return false;
	}
	return (bool)*(int*)outputBuffer;
}
