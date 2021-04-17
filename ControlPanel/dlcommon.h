#pragma once

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

#include "dlconfig.h"

#include <Windows.h>
#include <QString>

//#define TRUE 1
//#define FALSE 0

namespace Common {
    //initialize common lib stuff
    void init(void);

    //Allocates a block of memory from a heap.
    void *hAlloc(SIZE_T size);

    //Reallocates a block of memory from a heap.
    void *hReAlloc(void *mem, SIZE_T size);

    //free a memory block allocated from a heap by the hAlloc
    void hFree(void *mem);

    //console.log
    void ConsoleLog(QString log);
}
