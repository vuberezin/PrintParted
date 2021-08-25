#include"dialogcontext.h"



DialogContext::DialogContext(QWidget *parent, DataParted *dataParted, DiskData *diskdata,
                                            DataFreespace *dataFreespace,int row ) :
    QDialog(parent)
   // ui(new Ui::DialogContext)
{

    QGridLayout *layout = new QGridLayout;
    dataChart = new DataChart( dataParted, diskdata, dataFreespace, row);
    chartView = new QChartView();
    label = new QLabel;
    label->setWordWrap(true);
    string device = diskdata->vecSave.at(row).at(0);
    int lenght = dataFreespace->vecSave.size();

    for(int i = 0; i != lenght; i++){

    if(dataFreespace->vecSave.at(i).at(0) == device){

    label->setText("  Disk:   " + QString::fromStdString(dataFreespace->vecSave.at(i).at(0)) +
                    "\n" + "  Type:   " + QString::fromStdString(dataFreespace->vecSave.at(i).at(2)) +
                    "\n" + "  Start:   " + QString::fromStdString(dataFreespace->vecSave.at(i).at(3)) +
                    "\n" + "  End:   " + QString::fromStdString(dataFreespace->vecSave.at(i).at(4)) +
                    "\n" + "  Size:   " + QString::fromStdString(dataFreespace->vecSave.at(i).at(5)) +
                    "\n" + "  Start sector:   " + QString::fromStdString(dataFreespace->vecSave.at(i).at(6)) +
                    "\n" + "  End sector:   " + QString::fromStdString(dataFreespace->vecSave.at(i).at(7)) +
                    "\n" + "  Size in sectors:   " + QString::fromStdString(dataFreespace->vecSave.at(i).at(8)));
    freespaceModel = new FreespaceModel(dataFreespace, this);
    freespaceView = new QTableView;
    freespaceView->setModel(freespaceModel);
    freespaceView->horizontalHeader()->setStyleSheet("QHeaderView::section {background-color: #F0E68C }");
    freespaceView->setStyleSheet("QTableView:item:selected {background-color: #F0E68C  ; color: #000000}\n"
                                 "QTableView:item:selected:focus {background-color: #F0E68C;}");
    freespaceView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->chart()->setTitle("Disk: " + QString::fromStdString(device));
    chartView->chart()->addSeries(dataChart->series);
    chartView->chart()->legend()->setAlignment(Qt::AlignBottom);
    chartView->chart()->setTheme(QChart::ChartThemeQt);
    chartView->chart()->legend()->setFont(QFont("Arial", 10));
    layout->addWidget(chartView, 0, 0, 1, 1);
    layout->addWidget(freespaceView, 1, 0, 2, 1);
    setLayout(layout);
    } else {
        label->setText("There is no free space on the disk: " +
                       QString::fromStdString(device));
    }
    }

}

DialogContext::~DialogContext()
{
    //delete ui;
}
