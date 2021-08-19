/*
 * PrintParted is a program for viewing table of disk partitions
 * Copyright (C) 2021  Vadim Berezin
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef DISK_H
#define DISK_H

#include <parted/parted.h>
#include <parted/device.h>
#include <parted/disk.h>
#include <parted/filesys.h>
#include <parted/unit.h>
#include <parted/debug.h>
#include <parted/exception.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <QString>
#include <QVariant>
#include <QList>
#include <map>
#include <QDebug>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class DiskData
{
public:
    DiskData();
    vector<string> vecDisk;
    vector<vector<string>> vecSave;
    map<int, string> *diskType;
    vector<string>* vecTypes(int index);
    string diskFlags (PedDisk const *disk);
    void diskGeometry (const PedDevice *dev);
    vector<string> diskInfo (const PedDevice *dev, const PedDisk *diskp);
    string toString(long long x);

    ~DiskData();

};


#endif // DISK_H
