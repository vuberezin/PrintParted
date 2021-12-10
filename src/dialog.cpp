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


#include "include/dialog.h"


Dialog::Dialog(QWidget *parent, QTableView * tableView, DataParted *dataParted, DiskData *diskdata, DataFreespace *dataFreespace, int index) :
    QDialog(parent)
{
    //ui->setupUi(this);
    string device = diskdata->vecSave.at(index).at(0);    
    QGridLayout *layout = new QGridLayout;
    dataChart = new DataChart( tableView, dataParted, diskdata, dataFreespace, index);
    chartView = new QChartView();
    diskTableModel = new DiskTableModel;
    diskTableView = new QTableView;
    diskTableView->setModel(diskTableModel);
    updateDialog(QString::fromStdString(device));
    diskTableView->setContextMenuPolicy(Qt::CustomContextMenu);

    diskTableView->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color: #F0E68C }");
    diskTableView->setStyleSheet("QTableView:item:selected {background-color: #F0E68C  ; color: #000000}\n"
                                 "QTableView:item:selected:focus {background-color: #F0E68C;}");
    diskTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    diskTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    label = new QLabel;
    label->setStyleSheet("font-size: 13px; color: #2F4F4F;  border-style: solid;\
                                                            border-width: 1px;\
                                                            border-color: #F0E68C;");    
    label->setWordWrap(true);
    label->setText("  Disk: " + QString::fromStdString(diskdata->vecSave.at(index).at(0)) +
                    "\n" + "  Model: " + QString::fromStdString(diskdata->vecSave.at(index).at(1)) +
                    "\n" + "  Type: " + QString::fromStdString(diskdata->vecSave.at(index).at(2)) +
                    "\n" + "  Size: " + QString::fromStdString(diskdata->vecSave.at(index).at(3)) +
                    "\n" + "  Logical sector size: " + QString::fromStdString(diskdata->vecSave.at(index).at(4)) + "B" +
                    "\n" + "  Physical sector size: " + QString::fromStdString(diskdata->vecSave.at(index).at(5)) + "B" +
                    "\n" + "  Size in sectors: " + QString::fromStdString(diskdata->vecSave.at(index).at(6))  +
                    "\n" + "  Partition Table: " + QString::fromStdString(diskdata->vecSave.at(index).at(7)) +
                    "\n" + "  Disk Flags: " + QString::fromStdString(diskdata->vecSave.at(index).at(8)));
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->setTitle("Disk: " + QString::fromStdString(device));
    chartView->chart()->addSeries(dataChart->series);
    chartView->chart()->legend()->setAlignment(Qt::AlignBottom);
    chartView->chart()->setTheme(QChart::ChartThemeQt);
    chartView->chart()->legend()->setFont(QFont("Arial", 10));
    layout->addWidget(chartView, 0, 0, 1, 1);
    layout->addWidget(diskTableView, 1, 0, 2, 1);
    setLayout(layout);

};

void Dialog::updateDialog(const QString &data)
{

        for( int i = 0; i < diskTableModel->rowCount(); ++i )
        {

            bool match = false;
            for( int x = 0; x < diskTableModel->columnCount(); ++x )
            {
                if(data == (diskTableModel->data(diskTableModel->index(i,x)).toString())){
                    match = true;
                    break;
        }
        }
            diskTableView->setRowHidden(i, !match);

        }
}

Dialog::~Dialog()
{
    delete dataChart;
}
