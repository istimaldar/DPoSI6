#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVector>
#include <math.h>
#include <QDebug>
#include <algorithm>
#include "discretefouriertransform.h"
#include "fftwdit.h"
#include "fftwdif.h"
#include <QStringList>
#include "filter.h"
#include <iostream>
#include "recursivefilter.h"
#include <QMessageBox>

void drawPlot(QCustomPlot* plot, QVector<double> x, QVector<double> y, QString horizontalLabel = "x", QString verticalLabel = "y");
void drawPlot(QCustomPlot* plot, QVector<double> x, QVector<std::complex<double>> y, QString horizontalLabel = "x", QString verticalLabel = "y", bool amplitude=true, bool real=false);
void drawFreqPlot(QCustomPlot* plot, QVector<std::complex<double>> y);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupInterface();
    setWindowTitle("Преобразования Фурье");
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
    ui->pushButton->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Fixed);
    ui->lineEdit_3->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    for(int i=1; i<12; i++)
    {
        ui->comboBox->addItem(QString::number(pow(2, i)));
    }
}

void MainWindow::createPlots()
{
    int numberOfPoints = ui->comboBox->currentText().toInt();
    int M = ui->lineEdit_3->text().toInt();
    if (M > numberOfPoints || M <= 0)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","M must be less or equal then number of points anf greather then 0.");
        messageBox.setFixedSize(500,200);
        return;
    }
    QVector<double> t0(numberOfPoints), u0(numberOfPoints);
    for (int i = 0; i < numberOfPoints; i++)
    {
      t0[i] = (16. * i / numberOfPoints); // x goes from -1 to 1
      double a = ui->lineEdit->text().toDouble();
      double b = ui->lineEdit_2->text().toDouble();
      u0[i] = cos(a * t0[i]) + sin(b * t0[i]);
      u0[i] += sin(80  * t0[i]);
      u0[i] += sin(0.1  * t0[i]);
      u0[i] += 0.3;
    }
    //delete temp;
    drawPlot(ui->customPlot_5, t0, u0, "t", "u");
    double fl = ui->lineEdit_4->text().toDouble();
    if (fl <= 0|| fl > 0.5)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Wrong low freq");
        messageBox.setFixedSize(500,200);
        return;
    }
    double fh = ui->lineEdit_5->text().toDouble();
    if (fh <= 0|| fh > 0.5 || fh <= fl)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Wrong high freq");
        messageBox.setFixedSize(500,200);
        return;
    }
    QVector<double> *impulseResponseHF = Filter::buildHighFrequencyIR(numberOfPoints, M, fh);
    QVector<double> *blackmanssWindowHF = Filter::blackmansWindow(*impulseResponseHF, M);
    QVector<double> *impulseResponseLF = Filter::buildLowFrequencyIR(numberOfPoints, M, fl);
    QVector<double> *blackmanssWindowLF = Filter::blackmansWindow(*impulseResponseLF, M);
    delete impulseResponseHF;
    delete impulseResponseLF;
    QVector<double> *impulseResponse = Filter::buildBandPassIR(*blackmanssWindowLF, *blackmanssWindowHF, DiscreteFourierTransform::getInstance());
    delete blackmanssWindowHF;
    delete blackmanssWindowLF;
    QVector<double> *timeData = Filter::filter(u0, 100, 0.1, DiscreteFourierTransform::getInstance(), *impulseResponse);
    QVector<std::complex<double>> *data = DiscreteFourierTransform::getInstance()->directTransform(*timeData);
    QVector<std::complex<double>> *data1 = DiscreteFourierTransform::getInstance()->directTransform(u0);
    double x = ui->lineEdit_6->text().toDouble();
    if (x >= 1)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Wrong x");
        messageBox.setFixedSize(500,200);
        return;
    }
    QVector<double> *finalData = RecursiveFilter::filter(*timeData, x);
    drawFreqPlot(ui->customPlot, *data1);
    drawFreqPlot(ui->customPlot_2, *data);
    drawPlot(ui->customPlot_3, t0, *timeData, "t", "u");
    double difference = 0;
    for (unsigned int i = 0; i < timeData->size() / 10; i++)
    {
        double real = ((*data1)[i] / (*data)[i]).real();
        double imag = ((*data1)[i] / (*data)[i]).imag();
        difference += std::sqrt(real * real + imag * imag);
    }
    difference /= timeData->size() * 10;
    std::cout << difference << std::endl;
    //drawPlot(ui->customPlot_3, t0, *timeData1, "t", "u");
    drawPlot(ui->customPlot_4, t0, *finalData, "t", "u");
    //drawPlot(ui->customPlot_4, t0, *inverse, "t", "u");
    //delete &u0;
}

void drawFreqPlot(QCustomPlot* plot, QVector<std::complex<double>> y)
{
    size_t size = y.size() / 2;
    if (y.size() % 2)
    {
        size++;
    }
    QVector<double> t(size);
    QVector<double> *amplitude = Transform::getAmplitude(y);
    QVector<double> u(size);
    for (int i = 0; i < size; i++)
    {
        t[i] = i;
        u[i] = (*amplitude)[i];
    }
    plot->addGraph();
    plot->graph(0)->setData(t, u);
    plot->xAxis->setLabel("f");
    plot->yAxis->setLabel("u");
    plot->xAxis->setRange(*std::min_element(t.constBegin(), t.constEnd()), *std::max_element(t.constBegin(), t.constEnd()));
    plot->yAxis->setRange(*std::min_element(u.constBegin(), u.constEnd()), *std::max_element(u.constBegin(), u.constEnd()));
    plot->graph(0)->setLineStyle(QCPGraph::lsImpulse);
    plot->replot();
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

void drawPlot(QCustomPlot* plot, QVector<double> x, QVector<std::complex<double>> y, QString horizontalLabel, QString verticalLabel, bool amplitude, bool real)
{
    QVector<double> *u;
    if (real)
    {
        u = new QVector<double>(y.size());
        for (int i = 0;i<y.size();i++)
        {
            (*u)[i] = y[i].real();
        }
    }
    else
    {
        if (amplitude)
        {
            u = Transform::getAmplitude(y);
        }
        else
        {
            u = Transform::getPhase(y);
        }
    }
    drawPlot(plot, x, *u, horizontalLabel, verticalLabel);
    delete u;
}

MainWindow::~MainWindow()
{
    delete ui;
}
