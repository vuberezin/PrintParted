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


#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableView>
#include <QListView>
#include <QLabel>
#include <QLineEdit>
#include <QTextBrowser>
#include <QDateEdit>
#include <QString>
#include <QStringListModel>
#include <QComboBox>
#include <QMessageBox>
#include <QHeaderView>
#include <QFormLayout>
#include <QItemSelectionModel>
#include <QProgressBar>
#include <iostream>
#include <unistd.h>
#include "parttablemodel.h"
#include "comboboxmodel.h"
#include "disk.h"
#include "chart.h"
#include "disktablemodel.h"
#include "dialog.h"
#include "freespace.h"
#include "freespacemodel.h"
#include "dialogcontext.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class TableModel;
class Widget : public QWidget
{
Q_OBJECT

public:
    Widget(QWidget *parent = 0);

    QTableView *tableView;
    QTableView *diskTableView;
    TableModel *tableModel;
    QTableView *freespaceView;
    QLabel *diskLabel;
    QStringListModel *model;
    QComboBox *comboBox;
    QList<QString> *values;
    ComboBoxModel *combomodel;
    DiskData *diskData;
    DiskTableModel *diskTableModel;
    DataChart *dataChart;
    DataParted *dataParted;
    DataFreespace *dataFreespace;
    FreespaceModel * freespaceModel;
    QChartView *chartView;
    QItemSelectionModel *selectionModel;
    Dialog *dialog;
    QDialog* dialogWidget;
    DialogContext *dialogContext;
    QGridLayout *layout;
    int vecSize(vector<vector<string>> vec);
    QList<QString>* addComboItem(DiskData *diskData, QList<QString> *values);
    void keyPressEvent(QKeyEvent *event)override;
    void createSplash(QString str);

    ~Widget();

private:
     Ui::Widget *ui;
     
public slots:
    void clickedAction( int i);
    void slotShowFreespace();
    void slotShowDiskInfo();
    void slotContextMenuRequested(QPoint pos);
    void slotUpdate(const QItemSelection &selected, const QItemSelection &deselected);

};



#endif // WIDGET_H
