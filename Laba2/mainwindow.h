#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setupInterface();
    friend QVector<double> buildPlot(QVector<double> & data);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
public slots:
    void createPlots();
};

#endif // MAINWINDOW_H
