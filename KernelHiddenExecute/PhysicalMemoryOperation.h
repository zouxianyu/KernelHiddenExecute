#pragma once

#include <ntddk.h>
//#include <ntifs.h>
#include <windef.h>
#include <intrin.h>

#include "DebugPrintEx.h"


//////////////////////////////////////////////////////////////////////////
//constants and macros

#define	PAGE_TABLE_SIZE			0x1000
#define	CR3_FLAG_ALL_BITS			0xFFF0000000000FFF
#define	PAGE_TABLE_PML4T_FLAG	0x867	//1000 0110 0111
#define	PAGE_TABLE_PDPT_FLAG	0x9E7	//1001 1110 0111
#define VA_SYSTEM_START			0xFFFF080000000000 //IA64
#define MAX_ENTRY_COUNT			512
#define ENTRY_SIZE				sizeof(ULONG64)


//////////////////////////////////////////////////////////////////////////
//types

typedef struct _PHYSICAL_OP_CR3
{
	PVOID	pAllocVA_PML4T;
	PVOID	pAllocPA_PML4T;

	PVOID	pAllocVA_PDPT;
	PVOID	pAllocPA_PDPT;

	PVOID	pSystemPML4TMap;

	ULONG64	CR3Generated;
	ULONG64 CR3System;

	ULONG64 CR3BeforeSwitch;
	BOOL	IsContextSwitched;
	BOOL	IsIrqlChanged;
	KIRQL	OriginalIrql;//available if the IsIrqlChanged is true
}PHYSICAL_OP_CR3, * PPHYSICAL_OP_CR3;

typedef struct _MMPDPTE
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
		/* 0x0000 */ unsigned __int64 reserved0 : 18; /* bit position: 12 */
		/* 0x0000 */ unsigned __int64 PageFrameNumber : 18; /* bit position: 30 */
		/* 0x0000 */ unsigned __int64 reserved1 : 4; /* bit position: 48 */
		/* 0x0000 */ unsigned __int64 SoftwareWsIndex : 11; /* bit position: 52 */
		/* 0x0000 */ unsigned __int64 NoExecute : 1; /* bit position: 63 */
	}; /* bitfield */
} MMPDPTE, * PMMPDPTE; /* size: 0x0008 */

typedef struct _MMPDE
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
		/* 0x0000 */ unsigned __int64 reserved0 : 9; /* bit position: 12 */
		/* 0x0000 */ unsigned __int64 PageFrameNumber : 27; /* bit position: 21 */
		/* 0x0000 */ unsigned __int64 reserved1 : 4; /* bit position: 48 */
		/* 0x0000 */ unsigned __int64 SoftwareWsIndex : 11; /* bit position: 52 */
		/* 0x0000 */ unsigned __int64 NoExecute : 1; /* bit position: 63 */
	}; /* bitfield */
} MMPDE, * PMMPDE; /* size: 0x0008 */

typedef struct _MMVA
{
	struct /* bitfield */
	{
		/* 0x0000 */ unsigned __int64 Offset : 12;
		/* 0x0000 */ unsigned __int64 PT : 9;
		/* 0x0000 */ unsigned __int64 PDT : 9;
		/* 0x0000 */ unsigned __int64 PDPT : 9;
		/* 0x0000 */ unsigned __int64 PML4T : 9;
		/* 0x0000 */ unsigned __int64 Partition : 16; //User:0x0000 System:0xFFFF
	}; /* bitfield */
} MMVA, * PMMVA; /* size: 0x0008 */

typedef struct _MMVA_PDPTE_LARGE
{
	struct /* bitfield */
	{
		/* 0x0000 */ unsigned __int64 Offset : 30;
		/* 0x0000 */ unsigned __int64 PDPT : 9;
		/* 0x0000 */ unsigned __int64 PML4T : 9;
		/* 0x0000 */ unsigned __int64 Partition : 16; //User:0x0000 System:0xFFFF
	}; /* bitfield */
} MMVA_PDPTE_LARGE, * PMMVA_PDPTE_LARGE; /* size: 0x0008 */

typedef struct _MMVA_PDE_LARGE
{
	struct /* bitfield */
	{
		/* 0x0000 */ unsigned __int64 Offset : 21;
		/* 0x0000 */ unsigned __int64 PDT : 9;
		/* 0x0000 */ unsigned __int64 PDPT : 9;
		/* 0x0000 */ unsigned __int64 PML4T : 9;
		/* 0x0000 */ unsigned __int64 Partition : 16; //User:0x0000 System:0xFFFF
	}; /* bitfield */
} MMVA_PDE_LARGE, * PMMVA_PDE_LARGE; /* size: 0x0008 */


//////////////////////////////////////////////////////////////////////////
//prototypes

//windows API
NTKERNELAPI
NTSTATUS
PsLookupProcessByProcessId(
	_In_ HANDLE ProcessId,
	_Outptr_ PEPROCESS* Process
);

//operate physical memory via system API
HANDLE OpenPhysicalMemory();
BOOLEAN pMapPhysicalMemoryPre(HANDLE hMemory, PDWORD64 pDwAddress, PSIZE_T pSize, PDWORD64 pDwVirtualAddress);
PVOID MapPhysicalMemory(PVOID PA, SIZE_T Size);
BOOLEAN UnmapPhysicalMemory(PVOID VA);

//get specific info from CR3 value
ULONG64 GetCR3Flag(ULONG64 CR3);
ULONG64 ClearCR3Flag(ULONG64 CR3);

//get specific info from opaque eprocess struct
ULONG64 GetCR3ByEprocess(PEPROCESS pEProc);
PEPROCESS GetEProcess(ULONG64 PID);
ULONG64 GetCR3ByPID(ULONG64 PID);

//private functions
VOID pPrintPhysicalOpStructure(PPHYSICAL_OP_CR3 pPhysicalOpCR3);
NTSTATUS pFreePhysicalOpPageTableMemory(PPHYSICAL_OP_CR3 pPhysicalOpCR3);
NTSTATUS pAllocPhysicalOpPageTableMemory(PPHYSICAL_OP_CR3 pPhysicalOpCR3);
NTSTATUS pMapSystemPML4T(ULONG64 SystemCR3, PPHYSICAL_OP_CR3 pPhysicalOpCR3);
NTSTATUS pUnmapSystemPML4T(PPHYSICAL_OP_CR3 pPhysicalOpCR3);
NTSTATUS pFillGeneratedPML4TandPDPT(PPHYSICAL_OP_CR3 pPhysicalOpCR3);

//public functions
NTSTATUS CreatePhysicalOpCR3BySystemCR3(ULONG64 SystemCR3, PPHYSICAL_OP_CR3 pPhysicalOpCR3);
NTSTATUS FreePhysicalOpCR3(PPHYSICAL_OP_CR3 pPhysicalOpCR3);
NTSTATUS ContextVirtualToPhysical(PPHYSICAL_OP_CR3 pPhysicalOpCR3);
NTSTATUS ContextPhysicalToVirtual(PPHYSICAL_OP_CR3 pPhysicalOpCR3);
