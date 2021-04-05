#pragma once

#include <ntddk.h>
#include <windef.h>

#include "DebugPrintEx.h"
#include "HiddenExecute.h"


//////////////////////////////////////////////////////////////////////////
//prototypes

NTSTATUS SimulateApi(ULONG64 param1);
NTSTATUS ApiTransfer_SimulateApi(PHIDDEN_PAGE_RECORD pHiddenPageRecord, ULONG64 param1);