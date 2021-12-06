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


#include "include/chart.h"



DataChart::DataChart( DataParted *dataParted, DiskData *diskData, DataFreespace *dataFreespace, int index)
{
    //: QWidget(parent)
    chartData(dataParted, diskData, dataFreespace, index);

}

void DataChart::chartData(DataParted *dataParted, DiskData *diskData, DataFreespace *dataFreespace,int index)
{

    PedDevice *dev = NULL;
    PedDisk *disk = NULL;
    const PedDiskType* type;
    PedPartition *part = NULL;

    series = new QPieSeries();
    series->setHoleSize(0.35);
    vector<vector<string>> vecChart;
    vecChart = dataParted->vecSave;

    int size = diskData->vecSave.size();
    static int *arr1 = new int[size];

    if(first){

    for(int i = 0; i < size; i++){

        arr1[i] = dataParted->countPart(dev,disk,part, diskData->vecSave.at(i).at(0));

    }
    first = false;
    }


    string device = diskData->vecSave.at(index).at(0);
    int lenght = dataFreespace->vecSave.size();
    for(int i = 0; i != lenght; i++){

        if(dataFreespace->vecSave.at(i).at(0) == device){

            PedSector diskSectors = atoi(diskData->vecSave.at(index).at(6).c_str());
            PedSector sizeDisk = diskSectors*512;
            PedSector sizePart = atoi(dataFreespace->vecSave.at(i).at(8).c_str())*512;
            float percentPart = ((float)sizePart/(float)sizeDisk)*100;

         if(percentPart > 0){

            string percentPartition = toString(percentPart);
            string str = "Freespace " + percentPartition + "%";
            slice = series->append(str.c_str(), percentPart);
            slice->setExploded();
            //slice->setLabelVisible();
            }
        }
    }
    PedSector sizePart;
    PedSector diskSectors = atoi(diskData->vecSave.at(index).at(6).c_str());
    PedSector sizeDisk = diskSectors*512;
    int i = countArray(arr1, index);
    int x = countArray(arr1, index + 1);

    for(; i != x; i++){

    if(vecChart.at(i).at(2) == "extended" ){

        i++;
        if(vecChart.at(i).at(2) != "logical" ){
            QMessageBox msgBox;
            msgBox.setText("You need to create a logical partition inside\n"
                           "the extended partition");
            msgBox.setStyleSheet("QLabel {min-width: 300px;}");
            msgBox.exec();
            return;
        }
        
        PedSector partSectors = atoi(vecChart.at(i).at(8).c_str() );
        sizePart = partSectors*512;

    } else {

        PedSector partSectors = atoi(vecChart.at(i).at(8).c_str() );
        sizePart = partSectors*512;

    }

    float percentPart = ((float)sizePart/(float)sizeDisk)*100;
    string percentPartition = toString(percentPart);

    if(vecChart.at(i).at(2) == "extended"){

        i++;
        string str = "Part" + vecChart.at(i).at(1) + " " + percentPartition + "%";
        slice = series->append(str.c_str(), percentPart);
        slice->setExploded();
        //slice->setLabelVisible();

    } else if(percentPart > 0){

        string str = "Part" + vecChart.at(i).at(1) + " " + percentPartition + "%";
        slice = series->append(str.c_str(), percentPart);
        slice->setExploded();
        //slice->setLabelVisible();
    }
    }

}

string DataChart::toString(float x)
{
    string str;
    stringstream stream;
    stream << fixed << setprecision(2) << x;
    str = stream.str();
    return str;
}


int DataChart::countArray(int arr[], int count)
{
    int init = 0;
    return accumulate(arr, arr + count, init);
}

DataChart::~DataChart()
{

}
