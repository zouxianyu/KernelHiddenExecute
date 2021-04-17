#pragma once

#include <Windows.h>
#include <QString>

#define IOCTL_SAFE_READ	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SAFE_EXEC	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_UNSAFE_READ	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_UNSAFE_EXEC	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x803, METHOD_BUFFERED, FILE_ANY_ACCESS)

class ProtectedDriverControl
{
public:
	ProtectedDriverControl();
	~ProtectedDriverControl();

	bool open(QString deviceName);
	void close();
	QString safeRead();
	QString safeExec();

	QString unsafeRead();
	QString unsafeExec();

private:
	HANDLE hDevice;
};

#define IOCTL_ATTACK	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x810, METHOD_BUFFERED, FILE_ANY_ACCESS)

class MalwareDriverControl
{
public:
	MalwareDriverControl();
	~MalwareDriverControl();

	bool open(QString deviceName);
	void close();
	bool attack();

private:
	HANDLE hDevice;
};