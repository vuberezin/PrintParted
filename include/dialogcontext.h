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


#ifndef DIALOGCONTEXT_H
#define DIALOGCONTEXT_H

#include <QtCharts>
#include <QDialog>
#include <QTextBlock>
#include "freespace.h"
#include "freespacemodel.h"
#include "chart.h"


namespace Ui {
class DialogContext;
}

class DialogContext : public QDialog
{
    Q_OBJECT

public:
    DialogContext( QWidget *parent, DataParted *dataParted, DiskData *diskdata,
                                            DataFreespace *dataFreespace,int row = -1);
    DataFreespace  *dataFreespace;
    DataChart *dataChart;
    QChartView *chartView;
    FreespaceModel *freespaceModel;
    QTableView *freespaceView;
    QLabel *label;
    DataParted *dataParted;
    DiskData *diskdata;
    QTextBlock *textBlock;
    int row;

    ~DialogContext();

private:
    Ui::DialogContext  *ui;

};


#endif // DIALOGCONTEXT_H
