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


#include "include/freespacemodel.h"
#include <QApplication>


FreespaceModel::FreespaceModel(DataFreespace *dataFreespace, QObject *parent) :
            QAbstractTableModel(parent)
{
    dataVec.insert(dataVec.end(),dataFreespace->vecSave->begin(), dataFreespace->vecSave->end() );
    listSize = dataVec.size();
    col = 9;

}

int FreespaceModel::rowCount(const QModelIndex &p) const
{
    Q_UNUSED(p);
    return listSize;
}


int FreespaceModel::columnCount(const QModelIndex &p) const
{
    Q_UNUSED(p);
    return col;
}

QVariant FreespaceModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid()) {

        return QVariant();
    }

    if(index.row() < 0) {

        return QVariant();
}

/*
if( role == Qt::BackgroundColorRole ){

    return QVariant(QColor(Qt::lightGray));
}*/

if (role == Qt::DisplayRole) {

    while(index.row()){

        return (QString::fromStdString(dataVec[index.row()]->at(index.column())));

}
    return (QString::fromStdString(dataVec[index.row()]->at(index.column())));

}

    return QVariant();
}


QVariant FreespaceModel::headerData(int part, Qt::Orientation orient, int role) const
{
    if (role != Qt::DisplayRole)
    return QVariant();

    if (orient == Qt::Horizontal) {

        switch (part){

        case 0:
            return tr("Disk");

        case 1:
            return tr("Part number");

        case 2:
           return tr("Part type");

        case 3:
            return tr("Start");

        case 4:
           return tr("End");

        case 5:
            return tr("Size");

        case 6:
           return tr("Start sector");

        case 7:
           return tr("End sector");

        case 8:
            return tr("Size in sectors");

    default:
        return QVariant();
    }
    }
    return QVariant();
}


QPair<QString,QString> FreespaceModel::addData(int i)
{

    return qMakePair(QString::fromStdString(dataVec.at(i)->at(0)),
                            QString::fromStdString(dataVec.at(i)->at(4)));
}
