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

#define IOCTL_TEST	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)


//////////////////////////////////////////////////////////////////////////
//prototypes

//modify WD bit in the CR0
VOID WriteEnable();
VOID WriteDisable();

//dispatch functions
NTSTATUS DispatchCreate(PDEVICE_OBJECT pDevObj, PIRP pIrp);
NTSTATUS DispatchClose(PDEVICE_OBJECT pDevObj, PIRP pIrp);
NTSTATUS DispatchIoctl(PDEVICE_OBJECT pDevObj, PIRP pIrp);
VOID DriverUnload(PDRIVER_OBJECT pDriverObj);

//driver entry
NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObj, PUNICODE_STRING pRegistryString);


