#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <math.h>
#include <QDebug>
#include <algorithm>
#include "convolution.h"
#include "correlation.h"
#include <QStringList>
#include "discretefouriertransform.h"
#include "fftwdif.h"

void drawPlot(QCustomPlot* plot, QVector<double> x, QVector<double> y, QString horizontalLabel = "x", QString verticalLabel = "y");
void drawPlot(QCustomPlot* plot, QVector<double> x, QVector<std::complex<double>> y, QString horizontalLabel = "x", QString verticalLabel = "y");
double function(double (*func)(double), double a, double x);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupInterface();
    setWindowTitle("Кореляция и свёртка");
    connect(ui->createPlotsEvent,SIGNAL(triggered(bool)),this,SLOT(createPlots()));
}

void MainWindow::setupInterface()
{
    ui->label->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    ui->label_2->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    ui->label_3->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    ui->label_4->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    ui->label_5->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    ui->lineEdit->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Fixed);
    ui->lineEdit_2->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Fixed);
    ui->comboBox->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Fixed);
    ui->comboBox_2->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Fixed);
    ui->comboBox_3->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Fixed);
    ui->comboBox_4->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Fixed);
    ui->pushButton->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Fixed);   
    ui->tableWidget->setRowCount(9);
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "КорДПФсл" << "КорДПФум" << "КорДПФст" << "СвДПФсл" << "СвДПФум" << "СвДПФст" << "КорБПФсл" << "КорБПФум" << "КорБПФст" << "СвБПФсл" << "СвБПФум" << "СвБПФст");
    ui->tableWidget->setVerticalHeaderLabels(QStringList() << "2" << "4" << "8" << "16" << "32" << "64" << "128" << "256" << "512");
    for(int i=1; i<10; i++)
    {
        ui->comboBox->addItem(QString::number(pow(2, i)));
    }
    ui->comboBox_3->addItem("sin");
    ui->comboBox_4->addItem("sin");
    ui->comboBox_3->addItem("cos");
    ui->comboBox_4->addItem("cos");
    ui->comboBox_2->addItem("Кореляция");
    ui->comboBox_2->addItem("Свёртка");
    ui->comboBox_2->addItem("Кореляция через БПФ");
    ui->comboBox_2->addItem("Свёртка через БПФ");
}

void MainWindow::createPlots()
{
    int numberOfPoints = ui->comboBox->currentText().toInt();
    QVector<double> t0(numberOfPoints), u0(numberOfPoints), u1(numberOfPoints); // initialize with entries 0..100
    double a = ui->lineEdit->text().toDouble();
    double b = ui->lineEdit_2->text().toDouble();
    for (int i=0; i<numberOfPoints; i++)
    {
      t0[i] = (8. * i / numberOfPoints); // x goes from -1 to 1
      double (*op)(double);
      if (ui->comboBox_3->currentIndex()==0)
      {
          op = &sin;
      }
      else
      {
          op = &cos;
      }
      u0[i] = function(op, a, t0[i]);
      if (ui->comboBox_4->currentIndex()==0)
      {
          op = &sin;
      }
      else
      {
          op = &cos;
      }
      u1[i] = function(op, b, t0[i]);
    }
    drawPlot(ui->customPlot, t0, u0, "t", "u");
    drawPlot(ui->customPlot_2, t0, u1, "t", "u");
    OperationWithTwoOperands *operation;
    Transform *transform;
    if (ui->comboBox_2->currentIndex() % 2) {
        operation = new Correlation();
    }
    else
    {
        operation = new Convolution();
    }
    if (ui->comboBox_2->currentIndex() / 2) {
        transform = new FFTWDIF();
    }
    else
    {
        transform = new DiscreteFourierTransform();
    }
    QVector<std::complex<double>> *data = operation->execute(u0, u1, (*transform));
    drawPlot(ui->customPlot_3, t0, *data, "u", "phi");
    ui->tableWidget->setItem(log2(transform->getLastSize()) - 1, ui->comboBox_2->currentIndex() * 3,
                             new QTableWidgetItem(QString::number(transform->getAddOperations())));
    ui->tableWidget->setItem(log2(transform->getLastSize()) - 1, ui->comboBox_2->currentIndex() * 3 + 1,
                             new QTableWidgetItem(QString::number(transform->getMulOperations())));
    ui->tableWidget->setItem(log2(transform->getLastSize()) - 1, ui->comboBox_2->currentIndex() * 3 + 2,
                             new QTableWidgetItem(QString::number(transform->getPowOperations())));
}

void drawPlot(QCustomPlot* plot, QVector<double> x, QVector<double> y, QString horizontalLabel, QString verticalLabel)
{
    plot->addGraph();
    plot->graph(0)->setData(x, y);
    // give the axes some labels:
    plot->xAxis->setLabel(horizontalLabel);
    plot->yAxis->setLabel(verticalLabel);
    // set axes ranges, so we see all data:
    plot->xAxis->setRange(*std::min_element(x.constBegin(), x.constEnd()), *std::max_element(x.constBegin(), x.constEnd()));
    plot->yAxis->setRange(*std::min_element(y.constBegin(), y.constEnd()), *std::max_element(y.constBegin(), y.constEnd()));
    plot->replot();
}

void drawPlot(QCustomPlot* plot, QVector<double> x, QVector<std::complex<double>> y, QString horizontalLabel, QString verticalLabel)
{
    QVector<double> *u;
    u = new QVector<double>(y.size());
    for (int i = 0;i<y.size();i++)
    {
        (*u)[i] = y[i].real();
    }
    drawPlot(plot, x, *u, horizontalLabel, verticalLabel);
    delete u;
}

double function(double (*func)(double), double a, double x)
{
    return (*func)(a*x);
}

MainWindow::~MainWindow()
{
    delete ui;
}
