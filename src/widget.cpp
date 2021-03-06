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
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
                        
    diskTableModel = new DiskTableModel;
    diskTableView = new QTableView;
    diskTableView->setModel(diskTableModel);
    diskTableView->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color: #F0E68C }");
    diskTableView->setStyleSheet("QTableView:item:selected {background-color: #F0E68C  ; color: #000000}\n"
                                 "QTableView:item:selected:focus {background-color: #F0E68C;}");
    diskTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    diskTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    diskTableView->setContextMenuPolicy(Qt::CustomContextMenu);
                                          
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
    dataChart = new DataChart(tableView, dataParted, diskData, dataFreespace, 0);
    chartView = new QChartView();
    QSize size = this->size();
    chartView->resize(size.width()/1.1, size.height()/1.1);
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
    connect(diskTableView, SIGNAL(customContextMenuRequested(QPoint)), this,
                                                SLOT(slotContextMenuRequested(QPoint))); 
    selectionModel = diskTableView->selectionModel();
    connect(selectionModel, &QItemSelectionModel::selectionChanged, this, &Widget::slotUpdate);

}

void Widget::slotUpdate(const QItemSelection &selected, const QItemSelection &deselected)
{

    QModelIndex index;
    QString data;
    QModelIndexList items = selected.indexes();
    QVariant variant;
    int row =  items.at(0).row();
    clickedAction(row);
     
        foreach (index, items) {
            if(index.column() == 0){
            variant = index.data();
            }
        }
        for( int i = 0; i < tableModel->rowCount(); ++i ) {
            bool match = false;
            for( int x = 0; x < tableModel->columnCount(); ++x ) {
                        
                if(variant.toString() == (tableModel->data(tableModel->index(i,x)).toString())){
                    match = true;
                    break;
        }
        }
            tableView->setRowHidden(i, !match);
        }
}


void Widget::clickedAction(int index)
{
    dataChart = new DataChart(tableView, dataParted, diskData, dataFreespace, index);
    chartView->chart()->removeAllSeries();
    dataChart->series->setPieSize(0.6);
    chartView->chart()->addSeries(dataChart->series);
    string device = diskData->vecSave.at(index).at(0);
    chartView->chart()->setTitle(QString("Disk: %1").arg(QString::fromStdString(device)));
    QItemSelectionModel::SelectionFlags flags = QItemSelectionModel::ClearAndSelect |
            QItemSelectionModel::Rows;
    QModelIndex indx = diskTableView->model()->index(index, 0);
    diskTableView->selectionModel()->select(indx, flags);
    /*chartView->resize(1278, 280);*/

}

QList<QString>* Widget::addComboItem(DiskData *diskData, QList<QString>* values)
{
    int size = diskData->vecSave.size();
    for(int i = 0; i < size; i++){

        values->append(QString::fromStdString(diskData->vecSave.at(i).at(0)));
    }
    return values;
}

void Widget::slotContextMenuRequested(QPoint pos)
{
    QMenu * menu = new QMenu(this);
    QAction * showFreespace = new QAction(tr("disk freespace"), this);
    QAction * showDevice = new QAction(tr("disk description"), this);
    connect(showFreespace, SIGNAL(triggered()), this, SLOT(slotShowFreespace()));
    connect(showDevice, SIGNAL(triggered()), this, SLOT(slotShowDiskInfo()));
    menu->addAction(showDevice);
    menu->addAction(showFreespace);
    menu->popup(diskTableView->viewport()->mapToGlobal(pos));
}

void Widget::slotShowFreespace()
{
    dialogContext = new DialogContext(this, tableView, dataParted, diskData, dataFreespace,
                                      diskTableView->selectionModel()->currentIndex().row());
    QSize size = this->size();
    dialogContext->resize(size.width()/1.1, size.height()/1.1);
    dialogContext->setWindowTitle("Disk Freespace");
    dialogContext->show();

}

void Widget::slotShowDiskInfo()
{
    dialog = new Dialog(this, tableView, dataParted, diskData, dataFreespace,
                        diskTableView->selectionModel()->currentIndex().row());
    QSize size = this->size();
    dialog->resize(size.width()/1.1, size.height()/1.1);
    dialog->setWindowTitle("Disk Description");
    dialog->show();
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

void Widget::keyPressEvent(QKeyEvent *event)
{
    auto ind = diskTableView->selectionModel()->currentIndex();          
    if(ind.row() == -1){
        return;
    }

    switch (event->key())
    {
    case Qt::Key_Return:
        dialogContext = new DialogContext(this, tableView, dataParted, diskData, dataFreespace,
                                          diskTableView->selectionModel()->currentIndex().row());
        QSize size = this->size();
        dialogContext->resize(size.width()/1.1, size.height()/1.1);
        dialogContext->setWindowTitle("Disk Freespace");
        dialogContext->show();
        break;                            
    }
}


void Widget::createSplash(QString str)
{
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(str));
    splash->show();
    Qt::Alignment bottonleft = Qt::AlignLeft | Qt::AlignBottom;

    QString message =
       QObject::tr(" PrintParted is a program for viewing the disk partition table without disk operations. Disk\n"
                   " partitions and freespace are shown in a pie chart using the Qt-5.15 framework. Also, disk\n"
                   " partitions and freespace are displayed in the context menu in table with description disks\n"
                   " Freespace means space outside of already generated partitions and can be used to expand\n"
                   " existing partition or create new one.")
                   +  QObject::tr(" It can be used under the GPLv2\n")
                   +  QObject::tr(" For more information contact: berezin-v.u@yandex.ru\n");

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
    delete dataChart;
}

