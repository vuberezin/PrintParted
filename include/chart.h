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

#ifndef CHART_H
#define CHART_H

#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCore/QDebug>
#include <QChartView>
#include <QMessageBox>
#include <QDialog>
#include <cmath>
#include <iomanip>
#include <numeric>
#include "part.h"
#include "disk.h"
#include "freespace.h"
#include <string>
#include <iostream>
#include <QTableView>

#define PedSector long long
QT_CHARTS_USE_NAMESPACE
using namespace std;

class DataChart : public QObject
{
public:
    DataChart(QTableView *tableView, DataParted *dataParted, DiskData *diskData, DataFreespace *dataFreespace, int index);
    QPieSeries *series;
    QPieSlice *slice;
    QChartView *chartView;
    DataParted *dataParted;
    DataFreespace *dataFreespace;
    DiskData *diskData;
    QTableView *tableViewSave;
    QColor color;
    vector<vector<string>> *vecChart;
    void chartData(DataParted *dataPared, DiskData *diskData, DataFreespace *dataFreespace, int index);
    int countArray(int *array, int count);
    string toString(float x);
    string intToString(int  x);
    void messageBox(QString str);
    void delay();

    ~DataChart();
    
public slots:
    void selected(QPieSlice *slice);
    void deselected(QPieSlice *slice);
    
private:
    inline static bool first = true;

};

#endif // CHART_H
