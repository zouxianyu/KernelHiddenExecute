#pragma once

/*********************************************************
description:
notice!!!	run in IRQL >= DPC_LEVEL
			call apis maybe due to lower irql

in order to hidden real code in the non-mapped physical pages,and clear original codes
before call the hidden functions,we should map the physical pages to correct position.
if we have to call windows api in our hidden functions,we should call the transfer functions(not hidden)

features of transfer functions:check & change irql,restore & rewrite page table(pte),call specific apis

reserve the physical pages by Api:MmMarkPhysicalMemoryAsBad,prevent the allocation of our physical pages space

**********************************************************/

#include <ntddk.h>
#include <windef.h>

#include "DebugPrintEx.h"
#include "PhysicalMemoryOperation.h"
#include "SectionOperation.h"


//////////////////////////////////////////////////////////////////////////
//macro utilities

#define ChangeIrql(x)				WriteCR8(x)
#define ClearPageTableFlag(x)		ClearCR3Flag(x)


//////////////////////////////////////////////////////////////////////////
//constants and macros

#define SECTION_NAME_HIDDEN_INSTRUCTIONS	".hi"
#define SECTION_NAME_HIDDEN_DATA			".hd"
#define HIDDEN_IRQL							DISPATCH_LEVEL
#define HIDDEN_PAGE_RECORD_LENGTH			0x1000
#define MAX_HIDDEN_PAGE_COUNT				126					//      (4096 - 40) / (4 * 8) = 126.75


//////////////////////////////////////////////////////////////////////////
//types

typedef struct _MMPTE
{
	struct /* bitfield */
	{
		/* 0x0000 */ unsigned __int64 Valid : 1; /* bit position: 0 */
		/* 0x0000 */ unsigned __int64 Dirty1 : 1; /* bit position: 1 */
		/* 0x0000 */ unsigned __int64 Owner : 1; /* bit position: 2 */
		/* 0x0000 */ unsigned __int64 WriteThrough : 1; /* bit position: 3 */
		/* 0x0000 */ unsigned __int64 CacheDisable : 1; /* bit position: 4 */
		/* 0x0000 */ unsigned __int64 Accessed : 1; /* bit position: 5 */
		/* 0x0000 */ unsigned __int64 Dirty : 1; /* bit position: 6 */
		/* 0x0000 */ unsigned __int64 LargePage : 1; /* bit position: 7 */
		/* 0x0000 */ unsigned __int64 Global : 1; /* bit position: 8 */
		/* 0x0000 */ unsigned __int64 CopyOnWrite : 1; /* bit position: 9 */
		/* 0x0000 */ unsigned __int64 Unused : 1; /* bit position: 10 */
		/* 0x0000 */ unsigned __int64 Write : 1; /* bit position: 11 */
		/* 0x0000 */ unsigned __int64 PageFrameNumber : 36; /* bit position: 12 */
		/* 0x0000 */ unsigned __int64 reserved1 : 4; /* bit position: 48 */
		/* 0x0000 */ unsigned __int64 SoftwareWsIndex : 11; /* bit position: 52 */
		/* 0x0000 */ unsigned __int64 NoExecute : 1; /* bit position: 63 */
	}; /* bitfield */
} MMPTE, * PMMPTE; /* size: 0x0008 */

typedef struct _SPECIFIC_HIDDEN_PAGE_RECORD
{
	PVOID		pHiddenBase;
	PMMPTE		pPTE;
	ULONG64		OriginalPfn;
	ULONG64		HiddenPfn;
}SPECIFIC_HIDDEN_PAGE_RECORD, * PSPECIFIC_HIDDEN_PAGE_RECORD;

typedef struct _HIDDEN_PAGE_RECORD
{
	BOOL							IsHidden;
	KIRQL							OriginalIrql;
	BOOL							IsIrqlChanged;
	KSPIN_LOCK						SpinLock;
	ULONG64							Count;
	SPECIFIC_HIDDEN_PAGE_RECORD		Record[MAX_HIDDEN_PAGE_COUNT - 1];
}HIDDEN_PAGE_RECORD, * PHIDDEN_PAGE_RECORD;


//////////////////////////////////////////////////////////////////////////
//prototypes

//undocumented kernel functions
NTSYSAPI NTSTATUS MmMarkPhysicalMemoryAsBad(IN PPHYSICAL_ADDRESS, IN OUT PLARGE_INTEGER);
NTSYSAPI NTSTATUS MmMarkPhysicalMemoryAsGood(IN PPHYSICAL_ADDRESS, IN OUT PLARGE_INTEGER);

//functions
NTSTATUS InitializeHiddenPageRecordStructure(PHIDDEN_PAGE_RECORD* ppHiddenPageRecord);
NTSTATUS FreeHiddenPageRecordStructure(PHIDDEN_PAGE_RECORD pHiddenPageRecord);

//private functions
PVOID pPTEPFNtoPhysicalAddress(ULONG64 PFN);
ULONG64 pPhysicalAddresstoPTEPFN(PVOID PhysicalAddressBase);
PMMPTE pGetSpecificAddresspPTEPhysical(ULONG64 CR3, PVOID pPageBase);
PVOID pGetSpecificAddressPhysicalForR3(ULONG64 CR3, PVOID pVirtual);
ULONG64 GetPagesCountByLength(ULONG64 Length);

//public functions
//add page(s) to the hidden records
NTSTATUS AddHiddenPageRecord(ULONG64 CR3, PVOID pHiddenPageBase, PHIDDEN_PAGE_RECORD pHiddenPageRecord);
NTSTATUS AddHiddenSection(ULONG64 SystemCR3, PDRIVER_OBJECT pDriverObj, PCHAR pSegName, PHIDDEN_PAGE_RECORD pHiddenPageRecord);
NTSTATUS RemoveAndRestoreAllHiddenPageRecord(PHIDDEN_PAGE_RECORD pHiddenPageRecord);
//context swap
NTSTATUS ContextOriginalToHidden(PHIDDEN_PAGE_RECORD pHiddenPageRecord);
NTSTATUS ContextHiddenToOriginal(PHIDDEN_PAGE_RECORD pHiddenPageRecord);