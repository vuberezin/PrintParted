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


#include "disktablemodel.h"
#include "disk.h"
#include <QApplication>

DiskTableModel::DiskTableModel(QObject *parent) :
                QAbstractTableModel(parent)
{
    diskData = new DiskData();
    dTime = new QDateTime();
    mList.insert(mList.end(),diskData->vecSave->begin(), diskData->vecSave->end() );
    dList.append(dTime->currentDateTime().toString());
    listSize = mList.size();
    col = 9;
}


int DiskTableModel::rowCount(const QModelIndex &p) const
{
    Q_UNUSED(p);
    return listSize;
}

int DiskTableModel::columnCount(const QModelIndex &p) const
{
    Q_UNUSED(p);
    return col;
}

QVariant DiskTableModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid()) {
        return QVariant();
    }

    if(index.row() < 0){
        return QVariant();
    }

    if (role == Qt::DisplayRole){

    while(index.row()){

       return (QString::fromStdString(mList[index.row()]->at(index.column())));

    }
       return (QString::fromStdString(mList[index.row()]->at(index.column())));

    }

return QVariant();
}


QVariant DiskTableModel::headerData(int part, Qt::Orientation orient, int role) const
{

    if (role != Qt::DisplayRole)
        return QVariant();

    if (orient == Qt::Horizontal) {

        switch (part) {

        case 0:
            return tr("Disk");

        case 1:
            return tr("Model");

        case 2:
           return tr("Type");

        case 3:
           return tr("Size");

        case 4:
            return tr("Logical sector size");

        case 5:
           return tr("Physical sector size");

        case 6:
           return tr("End sector");

        case 7:
            return tr("Partition table");

        case 8:
           return tr("Flags");

        default:
            return QVariant();
    }
 }

    return QVariant();
}
