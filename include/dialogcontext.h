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
