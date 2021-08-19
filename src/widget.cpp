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


#include <QtGui>
#include <QGridLayout>
#include "include/widget.h"
#include "include/freespace.h"



Widget::Widget(QWidget *parent) :
            QWidget(parent)
{

    this->setStyleSheet("background-color: #FFFFE0 ;");
    dataParted = new DataParted();
    diskData = new DiskData();
    tableModel = new TableModel(dataParted, this);
    tableView = new QTableView;
    tableView->setModel(tableModel);
    tableView->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color: #F0E68C }");
    tableView->setStyleSheet("QTableView:item:selected {background-color: #F0E68C  ; color: #000000}\n"
                             "QTableView:item:selected:focus {background-color: #F0E68C;}");
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    diskTableModel = new DiskTableModel;
    diskTableView = new QTableView;
    diskTableView->setModel(diskTableModel);
    diskTableView->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color: #F0E68C }");
    diskTableView->setStyleSheet("QTableView:item:selected {background-color: #F0E68C  ; color: #000000}\n"
                                 "QTableView:item:selected:focus {background-color: #F0E68C;}");
    diskTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    dataFreespace = new DataFreespace;
    freespaceModel = new FreespaceModel(dataFreespace, this);
    freespaceView = new QTableView;
    freespaceView->setModel(freespaceModel);
    freespaceView->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color: #F0E68C }");
    freespaceView->setStyleSheet("QTableView:item:selected {background-color: #F0E68C  ; color: #000000}\n"
                                 "QTableView:item:selected:focus {background-color: #F0E68C;}");
    freespaceView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    diskLabel = new QLabel(tr("Disk:"));
    values = new QList<QString>();
    addComboItem(diskData, values);
    combomodel = new ComboBoxModel();
    combomodel->populate(values);
    comboBox = new QComboBox;
    comboBox->setModel(combomodel);
    comboBox->setStyleSheet("background-color: #F0E68C; color: #000000; border: 1px solid darkgray;\n"
                            " selection-background-color: #FFFFE0;");
    dataChart = new DataChart( dataParted, diskData, dataFreespace, 0);
    chartView = new QChartView();
    chartView->resize(1278, 280);
    dataChart->series->setPieSize(0.6);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->setTitle("Disk Partitions");
    chartView->chart()->addSeries(dataChart->series);
    chartView->chart()->legend()->setAlignment(Qt::AlignBottom);
    chartView->chart()->setTheme(QChart::ChartThemeQt);
    chartView->setStyleSheet("border: 1px solid darkgray;");
    chartView->chart()->legend()->setFont(QFont("Arial", 10));
    chartView->chart()->legend()->setVisible(true);
    chartView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);

    layout = new QGridLayout;
    layout->setRowStretch(0,0);
    layout->addWidget(diskLabel, 0, 0);
    layout->addWidget(comboBox, 0, 1);
    layout->addWidget(chartView, 1, 0, 1, 2);
    layout->addWidget(diskTableView, 2, 0, 1, 2);
    layout->addWidget(tableView, 3, 0, 1, 2);
    /*layout->addWidget(freespaceView, 4, 0, 1, 2);*/
    setLayout(layout);
    setWindowTitle(tr("PrintParted"));
    delete dataChart;

    connect(comboBox,SIGNAL(activated(int)),this, SLOT(clickedAction(int)));

}

void Widget::clickedAction(int index)
{

    dataChart = new DataChart(dataParted, diskData, dataFreespace, index);
    chartView->chart()->removeAllSeries();
    dataChart->series->setPieSize(0.6);
    chartView->chart()->addSeries(dataChart->series);
    chartView->chart()->setTitle("Disk Partitions");
    delete dataChart;
    /*chartView->resize(1278, 280);*/

//------------------------------------------------------------------------------------------------
    /*dialog = new Dialog(this, dataParted, diskData, index);
    dialog->resize(900, 700);
    dialog->setWindowTitle("Disk Partitions");
    dialog->show();*/
}

QList<QString>* Widget::addComboItem(DiskData *diskData, QList<QString>* values)
{
    int size = diskData->vecSave.size();
    for(int i = 0; i < size; i++){

        values->append(QString::fromStdString(diskData->vecSave.at(i).at(0)));
    }
    return values;
}

int Widget::vecSize(vector<vector<string>> vec)
{
    static int count = 0;
    int size = vec.size();
    for (int i = 0; i < size; i++) {     
        for (int x = 0; x < vec[i].size(); x++){
        ++count;
    }
    }
    return count;
}

void Widget::createSplash(QString str)
{
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(str));
    splash->show();
    Qt::Alignment bottonleft = Qt::AlignLeft | Qt::AlignBottom;

    QString message =
       QObject::tr(" PrintParted is a program for viewing the disk partition table without disk operations. Disk\n"
                   " partitions and freespace are shown in a pie chart using the Qt-5.15 framework. Freespace means\n"
                   " space outside of already generated partitions and can be used to expand existing partition\n"
                   " or create new one.")
                   +  QObject::tr(" It can be used under the GPLv2\n")
                   +  QObject::tr(" Contact for more information: berezin-v.u@yandex.ru\n");

    splash->showMessage(message, bottonleft, Qt::lightGray);

}

Widget::~Widget()
{
    delete dataParted;
    delete diskData;
    delete dataFreespace;
    delete values;
    delete combomodel;
    delete comboBox;
    delete diskTableModel;
}

