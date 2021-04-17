/*
    This file is part of driver-loader
    Copyright (C) 2017 @maldevel

    driver-loader - Load a Windows Kernel Driver.
    https://github.com/maldevel/driver-loader

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    For more see the file 'LICENSE' for copying permission.
*/

#include "dlcommon.h"
#include <QDebug>

static HANDLE processHeap;

//retrieve a handle to the default heap of this process
void Common::init(void) {
    processHeap = GetProcessHeap();
}

//HeapAlloc wrapper
//allocate a block of memory from a heap
void *Common::hAlloc(SIZE_T size) {
    if (processHeap == NULL || size <= 0) return NULL;

    return HeapAlloc(processHeap, HEAP_ZERO_MEMORY, size);
}

//HeapReAlloc wrapper
void *Common::hReAlloc(void *mem, SIZE_T size) {
    if (processHeap == NULL || mem == NULL || size <= 0) return NULL;

    return HeapReAlloc(processHeap, HEAP_ZERO_MEMORY, mem, size);
}

//free a memory block allocated from a heap by the HeapAlloc
void Common::hFree(void *mem) {
    if (processHeap == NULL || mem == NULL) return;

    HeapFree(processHeap, 0, mem);
    mem = NULL;
}

void Common::ConsoleLog(QString log) {
    if (log == NULL) return;

    if (DEBUG) {
        qDebug() << log;
    }
}
