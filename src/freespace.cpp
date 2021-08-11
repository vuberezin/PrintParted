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


#include "include/freespace.h"


DataFreespace::DataFreespace()
{
    PedDevice *dev = NULL;
    PedDisk *disk = NULL;
    const PedDiskType* type;
    PedPartition *part = NULL;
    vecSave = new vector<vector<string>*>();
    vecSave = partFreespace(dev, disk, part);

}


vector<vector<string>*>* DataFreespace::partFreespace(PedDevice *dev, PedDisk *disk, PedPartition *part){

    listVect = new vector<vector<string>*>();
    ped_device_probe_all();

    while ((dev = ped_device_get_next(dev))){

    disk = ped_disk_new(dev);
    if(disk != NULL){

    for (part = ped_disk_next_partition (disk, NULL); part;
              part = ped_disk_next_partition (disk, part)) {

    if(part->type == PED_PARTITION_FREESPACE){
        vecList = new vector<string>();
        vecList->push_back(dev->path);

        vecList->push_back(" - ");
        vecList->push_back("freespace");

        char *freespace_start = ped_unit_format (dev, part->geom.start);
        vecList->push_back(freespace_start);
        free (freespace_start);

        char *freespace_end = ped_unit_format_byte (dev, (part->geom.end + 1) *
                                          (dev)->sector_size - 1);
        vecList->push_back(freespace_end);
        free (freespace_end);

        char *freespace_size = ped_unit_format (dev, part->geom.length);
        vecList->push_back(freespace_size);
        free (freespace_size);

        string free_geom_start;
        free_geom_start = toString(part->geom.start);
        vecList->push_back(free_geom_start);

        string free_geom_end;
        free_geom_end = toString(part->geom.end);
        vecList->push_back(free_geom_end);

        string geom_length;
        geom_length = toString(part->geom.length);
        vecList->push_back(geom_length);
        listVect->push_back(vecList);
        }
    }
    }
    }
    return listVect;
}



string DataFreespace::toString(long long x)
{
    string str;
    stringstream stream;
    stream << x;
    str = stream.str();
    return str;
}
