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

#ifndef FREESPACE_H
#define FREESPACE_H

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
#include <QPair>
#include <QVector>
#include <QDebug>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>


using std::vector, std::string, std::stringstream, std::cout;

class DataFreespace
{
public:
    DataFreespace();
    vector<string> *vecData;
    vector<vector<string>> vecSave;
    vector<string> *vecList;
    vector<vector<string>*> *listVect;
    bool check_feature;
    string partFlags (PedPartition const *part);
    vector<vector<string>> partFreespace (PedDevice *dev, PedDisk *disk, PedPartition *part);
    int countPart(PedDevice *dev, PedDisk *disk, PedPartition *part, string path);
    int countExtPart(PedDevice *dev, PedDisk *disk, PedPartition *part, string path);
    string toString(long long x);

    ~DataFreespace();

};


#endif // FREESPACE_H
