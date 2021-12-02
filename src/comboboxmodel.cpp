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


#include "include/comboboxmodel.h"
#include "include/part.h"
#include <QModelIndex>
#include <QDebug>


ComboBoxModel::ComboBoxModel(QObject *parent)
                :QAbstractListModel(parent)
{
    values = new QList<QString>();

}

int ComboBoxModel::rowCount(const QModelIndex &p) const
{
  Q_UNUSED(p);  
  return values->count();
}

QVariant ComboBoxModel::data( const QModelIndex &index, int role ) const
{

    QVariant value;

    switch(role) {

    case Qt::DisplayRole:
        value = this->values->value(index.row());   
        break;

    case Qt::UserRole:
        value = this->values->value(index.row());
        break;

    default:
        break;
}
    return value;
}


void ComboBoxModel::populate(QList<QString>* newValues)
{
    int id = this->values->count();
    this->beginInsertRows(QModelIndex(), 1, id);
    this->values = newValues;
    endInsertRows();
}

ComboBoxModel::~ComboBoxModel()
{

}
