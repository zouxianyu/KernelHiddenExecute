#pragma once

#include <ntddk.h>
#include <windef.h>

#include "DebugPrintEx.h"
#include "HiddenExecute.h"
#include "HiddenCallApiTransfer.h"

//////////////////////////////////////////////////////////////////////////
//prototypes

//NTSTATUS HiddenFunctionA(PHIDDEN_PAGE_RECORD pHiddenPageRecord);
BOOL HiddenFunction(PCHAR checkStr);
BOOL UnsafeFunction(PCHAR checkStr);