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

#include <Windows.h>
#include <QString>

namespace Services {
    //initialize services lib stuff
    bool init(void);

    //un-initialize services lib stuff
    void uninit(void);

    //register a new service (install)
    unsigned long Register(QString driver, QString serviceName, QString displayName, QString startType, QString error);

    //unregister a service (uninstall)
    unsigned long Unregister(QString service);

    //start a service
    unsigned long Start(SC_HANDLE service);

    //start a service
    unsigned long Start(QString service);

    //stop a service
    unsigned long Stop(SC_HANDLE service);

    //stop a service
    unsigned long Stop(QString service);

    //open handle to service
    SC_HANDLE Open(QString service);
}

