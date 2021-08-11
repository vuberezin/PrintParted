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


#include "dialog.h"


Dialog::Dialog(QWidget *parent, DataParted *dataParted, DiskData *diskdata, DataFreespace *dataFreespace, int index) :
    QDialog(parent)
{
    //ui->setupUi(this);
    QGridLayout *layout = new QGridLayout;
    dataChart = new DataChart( dataParted, diskdata, dataFreespace, index);
    chartView = new QChartView();
    label = new QLabel;
    label->setWordWrap(true);
    label->setText("Disk: " + QString::fromStdString(diskdata->vecSave->at(index)->at(0)) +
                    "\n" + "Model: " + QString::fromStdString(diskdata->vecSave->at(index)->at(1)) +
                    "\n" + "Type: " + QString::fromStdString(diskdata->vecSave->at(index)->at(2)) +
                    "\n" + "Size: " + QString::fromStdString(diskdata->vecSave->at(index)->at(3)) +
                    "\n" + "Logical sector size: " + QString::fromStdString(diskdata->vecSave->at(index)->at(4)) + "B" +
                    "\n" + "Physical sector size: " + QString::fromStdString(diskdata->vecSave->at(index)->at(5)) + "B" +
                    "\n" + "Partition Table: " + QString::fromStdString(diskdata->vecSave->at(index)->at(6)) +
                    "\n" + "Disk Flags: " + QString::fromStdString(diskdata->vecSave->at(index)->at(7)));
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->setTitle("Patitions table");
    chartView->chart()->addSeries(dataChart->series);
    chartView->chart()->legend()->setAlignment(Qt::AlignBottom);
    chartView->chart()->setTheme(QChart::ChartThemeQt);
    chartView->chart()->legend()->setFont(QFont("Arial", 10));
    layout->addWidget(chartView, 0, 0);
    layout->addWidget(label, 0, 1);
    setLayout(layout);

};
