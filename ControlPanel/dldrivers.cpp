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

#include "dldrivers.h"
#include "dlcommon.h"
#include <Windows.h>
#include <Shlwapi.h>

static BOOL _fileExists(const char *filename) {
    if (filename == NULL)return FALSE;

    return PathFileExistsA(filename);
}

QString Drivers::GetFileVersion(QString fName) {
    if (fName == NULL || !_fileExists(fName.toStdString().c_str())) return "";

    DWORD handle;
    DWORD size = 0;
    void *buffer = 0;
    VS_FIXEDFILEINFO *lpBuffer = 0;
    unsigned int len = 0;
    QString fVersion = 0;

    if ((size = GetFileVersionInfoSizeA(fName.toStdString().c_str(), &handle)) == FALSE) {
        return "";
    }

    if ((buffer = Common::hAlloc(size)) == NULL) {
        return "";
    }

    if (GetFileVersionInfoA(fName.toStdString().c_str(), handle, size, buffer) == FALSE) {
        Common::hFree(buffer);
        return "";
    }

    if (VerQueryValue(buffer, QString("\\").toStdWString().c_str(), (void **)&lpBuffer, &len) == FALSE) {
        Common::hFree(buffer);
        return "";
    }

    fVersion = QString("%1.%2.%3.%4")
               .arg(HIWORD(lpBuffer->dwFileVersionMS))
               .arg(LOWORD(lpBuffer->dwFileVersionMS))
               .arg(HIWORD(lpBuffer->dwFileVersionLS))
               .arg(LOWORD(lpBuffer->dwFileVersionLS));

    Common::hFree(buffer);

    return fVersion;
}

unsigned long Drivers::GetDriverFileSize(QString fName) {
    if (fName == NULL || !_fileExists(fName.toStdString().c_str())) return 0;

    HANDLE hFile;
    unsigned long size = 0;
    unsigned long sizeHigh = 0;

    if ((hFile = CreateFileA(fName.toStdString().c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0)) == INVALID_HANDLE_VALUE) {
        return 0;
    }

    if ((size = GetFileSize(hFile,  NULL)) == INVALID_FILE_SIZE) {
        if (GetLastError() == NO_ERROR) {
            if ((size = GetFileSize(hFile,  &sizeHigh)) != INVALID_FILE_SIZE) {
                CloseHandle(hFile);
                return sizeHigh;
            }
        }

        CloseHandle(hFile);
        return 0;
    }

    CloseHandle(hFile);

    return size;
}

QString Drivers::GetFileLastWriteTime(QString fName) {
    if (fName == NULL || !_fileExists(fName.toStdString().c_str())) return 0;

    HANDLE hFile;
    FILETIME ftCreate, ftAccess, ftWrite;
    SYSTEMTIME stUTC, stLocal;
    QString day = "";
    QString month = "";

    if ((hFile = CreateFileA(fName.toStdString().c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0)) == INVALID_HANDLE_VALUE) {
        return "";
    }

    if (GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite) == 0) {
        CloseHandle(hFile);
        return "";
    }

    if (FileTimeToSystemTime(&ftWrite, &stUTC) == 0) {
        CloseHandle(hFile);
        return "";
    }

    if (SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal) == 0) {
        CloseHandle(hFile);
        return "";
    }

    switch (stLocal.wDayOfWeek) {
        case 0:
            day = "Sunday";
            break;
        case 1:
            day = "Monday";
            break;
        case 2:
            day = "Tuesday";
            break;
        case 3:
            day = "Wednesday";
            break;
        case 4:
            day = "Thursday";
            break;
        case 5:
            day = "Friday";
            break;
        case 6:
            day = "Saturday";
            break;
    };

    switch (stLocal.wMonth) {
        case 1:
            month = "January";
            break;
        case 2:
            month = "February";
            break;
        case 3:
            month = "March";
            break;
        case 4:
            month = "April";
            break;
        case 5:
            month = "May";
            break;
        case 6:
            month = "June";
            break;
        case 7:
            month = "July";
            break;
        case 8:
            month = "August";
            break;
        case 9:
            month = "September";
            break;
        case 10:
            month = "October";
            break;
        case 11:
            month = "November";
            break;
        case 12:
            month = "December";
            break;
    };

    CloseHandle(hFile);

    return QString("%1, %2 %3, %4 %5:%6:%7")
           .arg(day)
           .arg(month)
           .arg(stLocal.wDay)
           .arg(stLocal.wYear)
           .arg(stLocal.wHour)
           .arg(stLocal.wMinute)
           .arg(stLocal.wSecond);
}
