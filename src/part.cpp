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


#include "include/part.h"



DataParted::DataParted()
{
    PedDevice *dev = NULL;
    PedDisk *disk = NULL;
    const PedDiskType* type;
    PedPartition *part = NULL;
    vecSave = partInfo(dev, disk, part);

}


int DataParted::countPart(PedDevice *dev, PedDisk *disk, PedPartition *part, string path)
{

    int count = 0;
    /*ped_device_probe_all();*/
    dev = ped_device_get(path.c_str());
    if (!ped_device_open (dev)){

        perror ("Error open device");
        return 0;
    }

    disk = ped_disk_new(dev);
    if(disk != NULL){

    for (part = ped_disk_next_partition (disk, NULL); part;
           part = ped_disk_next_partition (disk, part)) {

    if ((!ped_partition_is_active(part)) ||
            part->type & PED_PARTITION_METADATA){
        continue;

    } else {
        ++count;
    }
    }
    return count;
    }
}


int DataParted::countExtPart(PedDevice *dev, PedDisk *disk, PedPartition *part, string path)
{
    int count = 0;
    /*ped_device_probe_all();*/
    dev = ped_device_get(path.c_str());
    if (!ped_device_open (dev)){

      perror ("Error open device");
      return 0;
    }

    disk = ped_disk_new(dev);
    if(disk != NULL){

    for (part = ped_disk_next_partition (disk, NULL); part;
         part = ped_disk_next_partition (disk, part)) {

    if (part->type == PED_PARTITION_EXTENDED){
    if (part->num >= 0){
      ++count;
    }
    }
    }
    } else {

        return 0;
    }

    return count;
}


string DataParted::partFlags (PedPartition const *part)
{
    PedPartitionFlag flag;
    bool step = true;
    const char *flag1 = "";
    const char *flag2 = "";

    for (flag = ped_partition_flag_next(PedPartitionFlag(0)); flag;
                    flag = ped_partition_flag_next (flag)) {

    if (ped_partition_get_flag (part, flag)) {

    if (step){

        flag1 = (ped_partition_flag_get_name (flag));
        step = false;

    } else {
        flag2 = (ped_partition_flag_get_name (flag));

    }
    }
    }
    string s1(flag1);
    string s2(flag2);
    string s3 = s1 + "  " + s2;
    return s3;
}


vector<vector<string>> DataParted::partInfo(PedDevice *dev, PedDisk *disk, PedPartition *part)
{

    vector<vector<string>> listVect; // = new vector<vector<string>*>();
    ped_device_probe_all();

    while ((dev = ped_device_get_next(dev))){

    disk = ped_disk_new(dev);
    if(disk != NULL){

    for (part = ped_disk_next_partition (disk, NULL); part;
                  part = ped_disk_next_partition (disk, part)) {

        vector<string> vecList; // = new vector<string>();
        vecList.push_back(dev->path);

    if (part->type == PED_PARTITION_METADATA || !ped_partition_is_active(part))
                      continue;

    if (part->num >= 0){

        string part_num;
        part_num = toString(part->num);
        vecList.push_back(part_num);
    }

    if ( part->type == PED_PARTITION_NORMAL){

        vecList.push_back("primary");

    } else if(part->type == PED_PARTITION_EXTENDED ){

        vecList.push_back("extended");

    } else if(part->type == PED_PARTITION_LOGICAL ){

        vecList.push_back("logical");

    } else if(part->type == PED_PARTITION_FREESPACE ){

        vecList.push_back("freespace");

    } else if(part->type == PED_PARTITION_METADATA ){

        vecList.push_back("metadata");

    } else if(part->type == PED_PARTITION_PROTECTED ){

        vecList.push_back("protected");
    }


    char *start = ped_unit_format (dev, part->geom.start);
    vecList.push_back(start);
    free (start);
    char *end = ped_unit_format_byte (dev, (part->geom.end + 1) *
                                      (dev)->sector_size - 1);
    vecList.push_back(end);
    free (end);

    if (ped_unit_get_default() != PED_UNIT_CHS) {

        char *size = ped_unit_format (dev, part->geom.length);
        vecList.push_back(size);
        free (size);
    }

    string geom_start;
    geom_start = toString(part->geom.start);
    vecList.push_back(geom_start);

    string geom_end;
    geom_end = toString(part->geom.end);
    vecList.push_back(geom_end);

    string geom_length;
    geom_length = toString(part->geom.length);
    vecList.push_back(geom_length);

    if (!(part->type & PED_PARTITION_FREESPACE)) {

    if (part->fs_type){

        vecList.push_back(part->fs_type->name);

    } else {

        vecList.push_back(" - ");
    }

    check_feature = ped_disk_type_check_feature (disk->type,
                                         PED_DISK_TYPE_PARTITION_NAME);
    if (check_feature){

        vecList.push_back(ped_partition_get_name (part));

    } else {

        vecList.push_back(" - ");
    }

    const char *flags = (partFlags(part)).c_str();

    if(flags[0] != ' '){

        vecList.push_back(flags);

    } else {

        vecList.push_back(" - ");

    }

    /*printf ("geom_length %ll:", part->geom.length);*/

    } else {

        printf ("Has freespace: %s\n", dev->path);
    }

    listVect.push_back(vecList);

    }

    } else { printf ("No partitions: %s\n", dev->path);

    }
    }

    return listVect;
}


string DataParted::toString(long long x)
{
    string str;
    stringstream stream;
    stream << x;
    str = stream.str();
    return str;
}

DataParted::~DataParted()
{

}
