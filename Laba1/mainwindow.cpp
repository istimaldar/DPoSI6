#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <math.h>

double timePlot();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    ui->label_2->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    ui->label_3->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    ui->label_4->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    ui->label_5->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    ui->lineEdit->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Fixed);
    ui->lineEdit_2->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Fixed);
    ui->comboBox->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Fixed);
    ui->comboBox_2->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Fixed);
    ui->pushButton->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Fixed);
    for(int i=1; i<7; i++)
    {
        ui->comboBox->addItem(QString::number(pow(2, i)));
    }
    ui->comboBox_2->addItem("ДПФ");
    ui->comboBox_2->addItem("БПФ с прореживанием по времени");
    ui->comboBox_2->addItem("БПФ с прореживанием по частоте");
    connect(ui->createPlotsEvent,SIGNAL(triggered(bool)),this,SLOT(createPlots()));
}

void MainWindow::createPlots()
{
    // generate some data:
    QVector<double> x(NUMBER_OF_POINTS), y(NUMBER_OF_POINTS); // initialize with entries 0..100
    for (int i=0; i<NUMBER_OF_POINTS; i++)
    {
      x[i] = (16. * i / NUMBER_OF_POINTS); // x goes from -1 to 1
      qDebug() << x[i];
      double a = ui->lineEdit->text().toDouble();
      double b = ui->lineEdit_2->text().toDouble();
      y[i] = cos(a * x[i]) + sin(b * x[i]); // let's plot a quadratic function
    }
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("t");
    ui->customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(0, 16);
    ui->customPlot->yAxis->setRange(-2, 2);
    ui->customPlot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}
