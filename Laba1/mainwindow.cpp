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

void drawPlot(QCustomPlot* plot, QVector<double> x, QVector<double> y, QString horizontalLabel = "x", QString verticalLabel = "y");
void drawPlot(QCustomPlot* plot, QVector<double> x, QVector<std::complex<double>> y, QString horizontalLabel = "x", QString verticalLabel = "y", bool amplitude=true, bool real=false);

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
    ui->comboBox_2->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Fixed);
    ui->pushButton->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Fixed);
    ui->tableWidget->setRowCount(9);
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "ДПФсл" << "ДПФум" << "ДПФст" << "БПФПВсл" << "БПФПВум" << "БПФПВст" << "БПФПЧсл" << "БПФПЧум" << "БПФПЧст");
    ui->tableWidget->setVerticalHeaderLabels(QStringList() << "2" << "4" << "8" << "16" << "32" << "64" << "128" << "256" << "512");
    for(int i=1; i<10; i++)
    {
        ui->comboBox->addItem(QString::number(pow(2, i)));
    }
    ui->comboBox_2->addItem("ДПФ");
    ui->comboBox_2->addItem("БПФ с прореживанием по времени");
    ui->comboBox_2->addItem("БПФ с прореживанием по частоте");
}

void MainWindow::createPlots()
{
    int numberOfPoints = ui->comboBox->currentText().toInt();
    QVector<double> t0(numberOfPoints), u0(numberOfPoints); // initialize with entries 0..100
    for (int i=0; i<numberOfPoints; i++)
    {
      t0[i] = (8. * i / numberOfPoints); // x goes from -1 to 1
      double a = ui->lineEdit->text().toDouble();
      double b = ui->lineEdit_2->text().toDouble();
      u0[i] = cos(a * t0[i]) + sin(b * t0[i]); // let's plot a quadratic function
    }
    drawPlot(ui->customPlot, t0, u0, "t", "u");
    Transform *transform;
    switch (ui->comboBox_2->currentIndex()) {
    case 0:
        transform = new DiscreteFourierTransform();
        break;
    case 1:
        transform = new FFTWDIT();
        break;
    case 2:
        transform = new FFTWDIF();
    }
    QVector<std::complex<double>> *data = transform->directTransform(u0);
    drawPlot(ui->customPlot_2, t0, *data, "f", "u", true);
    drawPlot(ui->customPlot_3, t0, *data, "f", "phi", false);
    ui->customPlot_2->graph(0)->setLineStyle(QCPGraph::lsImpulse);
    ui->customPlot_3->graph(0)->setLineStyle(QCPGraph::lsImpulse);
    QVector<std::complex<double>> *original = transform->inverseTransform(*data);
    drawPlot(ui->customPlot_4, t0, *original, "t", "u", false, true);
    delete data;
    delete original;
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
