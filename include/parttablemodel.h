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

#ifndef PARTTABLEMODEL_H
#define PARTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QDebug>
#include <QLabel>
#include <QString>
#include <QVariant>
#include <QList>
#include <QPair>
#include "part.h"
#include <QDateTime>
#include <iostream>
#include <QSortFilterProxyModel>


class TableModel : public QAbstractTableModel
{
Q_OBJECT

public:
    TableModel(DataParted *dataParted, QObject *parent);
    DataParted *dataParted;
    QDateTime *dTime;
    QPair<QString, QString> message;
    vector<vector<string>*> dataVec;
    QList<QString> dataList;
    int listSize;
    int col;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int part, Qt::Orientation orient, int role) const;
    QPair<QString,QString> addData(int i);


};


#endif // PARTTABLEMODEL_H
