#pragma once

#include <ntddk.h>
#include <ntimage.h>
#include <windef.h>

#include "DebugPrintEx.h"

//////////////////////////////////////////////////////////////////////////
//types

typedef struct _LDR_DATA_TABLE_ENTRY64
{
	LIST_ENTRY64    InLoadOrderLinks;
	LIST_ENTRY64    InMemoryOrderLinks;
	LIST_ENTRY64    InInitializationOrderLinks;
	PVOID            DllBase;
	PVOID            EntryPoint;
	ULONG            SizeOfImage;
	UNICODE_STRING    FullDllName;
	UNICODE_STRING     BaseDllName;
	ULONG            Flags;
	USHORT            LoadCount;
	USHORT            TlsIndex;
	PVOID            SectionPointer;
	ULONG            CheckSum;
	PVOID            LoadedImports;
	PVOID            EntryPointActivationContext;
	PVOID            PatchInformation;
	LIST_ENTRY64    ForwarderLinks;
	LIST_ENTRY64    ServiceTagLinks;
	LIST_ENTRY64    StaticLinks;
	PVOID            ContextInformation;
	ULONG64            OriginalBase;
	LARGE_INTEGER    LoadTime;
} LDR_DATA_TABLE_ENTRY64, * PLDR_DATA_TABLE_ENTRY64;


//////////////////////////////////////////////////////////////////////////
//prototypes

PIMAGE_SECTION_HEADER GetSegmentHeadPointer(PDRIVER_OBJECT pDriverObj, PCHAR pSegName);
ULONG64 GetDriverBaseAddress(PDRIVER_OBJECT pDriverObj, PCHAR pSegName);
ULONG64 GetSegmentAddressPointer(PDRIVER_OBJECT pDriverObj, PCHAR pSegName);
ULONG64 GetSegmentLengthPointer(PDRIVER_OBJECT pDriverObj, PCHAR pSegName);
ULONG64 GetSegmentRawDataAddressPointer(PDRIVER_OBJECT pDriverObj, PCHAR pSegName);
ULONG64 GetSegmentRawDataLengthPointer(PDRIVER_OBJECT pDriverObj, PCHAR pSegName);
ULONG64 GetSegmentStartAddress(PDRIVER_OBJECT pDriverObj, PCHAR pSegName);
ULONG64 GetSegmentEndAddress(PDRIVER_OBJECT pDriverObj, PCHAR pSegName);
ULONG64 GetSegmentLength(PDRIVER_OBJECT pDriverObj, PCHAR pSegName);