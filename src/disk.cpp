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


#include "include/disk.h"


DiskData::DiskData()
{

    PedDevice *current_dev = NULL;
    PedDisk *disk = NULL;
    PedPartition *part = NULL;
    vecDisk = new vector<string>();
    vecSave = new vector<vector<string>*>();
    diskType = new map<int, string>();
    diskType->emplace(0, "unknown");    diskType->emplace(1, "scsi");
    diskType->emplace(2, "ide");        diskType->emplace(3, "dac960");
    diskType->emplace(4, "cpqarray");   diskType->emplace(5, "file");
    diskType->emplace(6, "ataraid");    diskType->emplace(7, "i2o");
    diskType->emplace(8, "ubd");        diskType->emplace(9, "dasd");
    diskType->emplace(10, "viodasd");   diskType->emplace(11, "sx8");
    diskType->emplace(12, "dm");        diskType->emplace(13, "xvd");
    diskType->emplace(14, "sd/mmc");    diskType->emplace(15, "virtblk");
    diskType->emplace(16, "aoe");       diskType->emplace(17, "md");
    diskType->emplace(18, "loop");      diskType->emplace(19, "nvme");
    diskType->emplace(20, "ram");       diskType->emplace(21, "pmem");

    ped_device_probe_all();
    while ((current_dev = ped_device_get_next(current_dev))){
         vecDisk = diskInfo(current_dev, disk);
         vecSave->push_back(vecDisk);

      }

}

string DiskData::diskFlags (PedDisk const *disk)
{
    PedDiskFlag flag;
    bool step = true;
    const char *flag1 = "";
    const char *flag2 = "";
    string s = "";

    if (!disk)
        return s;

    for (flag = ped_disk_flag_next (flag); flag;
                 flag = ped_disk_flag_next (flag)){

    if (ped_disk_get_flag (disk, flag)){

    if (step){
        flag1 = (ped_disk_flag_get_name (flag));
        step = false;

    } else {

        flag2 = (ped_disk_flag_get_name (flag));

    }
    }
    }
    string s1(flag1);
    string s2(flag2);
    string s3 = s1 + "  " + s2;
    return s3;
}


vector<string>* DiskData::diskInfo (const PedDevice *dev, const PedDisk *disk)
{

    char* start = ped_unit_format (dev, 0);
    auto unit = ped_unit_get_default();
    char* end = ped_unit_format_byte (dev, dev->length * dev->sector_size
                     - (unit == PED_UNIT_CHS || unit == PED_UNIT_CYLINDER));

    disk = ped_disk_new((PedDevice*)dev);
    const char* pt_name;
    const char *disk_flags;
    vecTemp = new vector<string>();
    vecTemp->push_back(dev->path);
    vecTemp->push_back(dev->model);

    map<int, string>::iterator it = diskType->begin();
    for (; it != diskType->end(); it++){

    if(it->first == dev->type){

        vecTemp->push_back(it->second);
    }
    }
    vecTemp->push_back(end);

    string log_sect_size;
    log_sect_size = toString(dev->sector_size);
    vecTemp->push_back(log_sect_size);

    string phys_sector_size;
    phys_sector_size = toString(dev->phys_sector_size);
    vecTemp->push_back(phys_sector_size);

    string dev_length;
    dev_length = toString(dev->length);
    vecTemp->push_back(dev_length);

    if (disk){

        pt_name = disk->type->name;
        vecTemp->push_back(pt_name);

    } else {

        vecTemp->push_back(" - ");
    }

    if(disk && !(ped_disk_is_flag_available(disk, PED_DISK_CYLINDER_ALIGNMENT))){

        disk_flags = diskFlags(disk).c_str();
        vecTemp->push_back(disk_flags);

    } else {

        vecTemp->push_back(" - ");
    }


    free (start);
    free (end);
    return vecTemp;

}

string DiskData::toString(long long x)
{
    string str;
    stringstream stream;
    stream << x;
    str = stream.str();
    return str;
}
