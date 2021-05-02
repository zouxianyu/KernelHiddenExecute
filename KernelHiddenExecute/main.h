#pragma once

#include <ntifs.h>
#include <ntddk.h>
#include <stdlib.h>
#include <windef.h>
#include <ntimage.h>
#include <intrin.h>

#include "DebugPrintEx.h"
#include "HiddenExecute.h"
#include "HiddenCallApiTransfer.h"
#include "HiddenFunctions.h"


//////////////////////////////////////////////////////////////////////////
//constants and macros

#define	DEVICE_NAME	L"\\Device\\KernelHiddenExecute"
#define LINK_NAME	L"\\DosDevices\\Global\\KernelHiddenExecute"

#define IOCTL_SAFE_READ	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SAFE_EXEC	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_UNSAFE_READ	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_UNSAFE_EXEC	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x803, METHOD_BUFFERED, FILE_ANY_ACCESS)


//////////////////////////////////////////////////////////////////////////
//prototypes

//modify WD bit in the CR0
//VOID WriteEnable();
//VOID WriteDisable();

//dispatch functions
NTSTATUS DispatchCreate(PDEVICE_OBJECT pDevObj, PIRP pIrp);
NTSTATUS DispatchClose(PDEVICE_OBJECT pDevObj, PIRP pIrp);
NTSTATUS DispatchIoctl(PDEVICE_OBJECT pDevObj, PIRP pIrp);
VOID DriverUnload(PDRIVER_OBJECT pDriverObj);

//driver entry
NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObj, PUNICODE_STRING pRegistryString);


//////////////////////////////////////////////////////////////////////////
//global variables

extern char HiddenData[4096];
extern char UnsafeData[4096];

