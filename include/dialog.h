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

#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>
#include <QtCharts>
#include <QDialog>
#include <QTextBlock>
#include "chart.h"
#include "part.h"
#include "disk.h"
#include "disktablemodel.h"


class Dialog : public QDialog
{

  public:
    Dialog(QWidget *parent, QTableView * tableView, DataParted *dataParted, DiskData *diskdata, DataFreespace *dataFreespace,int index);
    DataChart *dataChart;
    QChartView *chartView;
    QLabel *label;
    DataParted *dataParted;
    DiskData *diskdata;
    DiskTableModel *diskTableModel;
    QTableView *diskTableView;
    QTextBlock *textBlock;
    int index;
    
    ~Dialog();
    
public slots:
    void updateDialog(const QString &data);

};

#endif // DIALOG_H
