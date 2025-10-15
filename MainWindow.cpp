#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QTimer>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupTheme();
    setupCharts();

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateSystemStats);
    timer->start(1000); 
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupTheme()
{
  
    qApp->setStyleSheet(R"(
        QMainWindow { background-color: #121212; }
        QProgressBar { border: 1px solid #333; border-radius: 5px; text-align: center; color: white; }
        QProgressBar::chunk { background-color: #00BCD4; }
        QTabWidget::pane { border: 0; }
        QTabBar::tab { background: #1E1E1E; color: white; padding: 5px; }
        QTabBar::tab:selected { background: #333333; }
    )");
}

void MainWindow::setupCharts()
{

    cpuSeries = new QLineSeries();
    QChart* cpuChart = new QChart();
    cpuChart->addSeries(cpuSeries);
    cpuChart->legend()->hide();
    cpuChart->setTitle("CPU Usage %");
    QValueAxis* cpuX = new QValueAxis();
    cpuX->setRange(0, 30); cpuX->setLabelFormat("%d"); cpuChart->addAxis(cpuX, Qt::AlignBottom); cpuSeries->attachAxis(cpuX);
    QValueAxis* cpuY = new QValueAxis();
    cpuY->setRange(0, 100); cpuChart->addAxis(cpuY, Qt::AlignLeft); cpuSeries->attachAxis(cpuY);
    ui->cpuChartView->setChart(cpuChart);

    ramSeries = new QLineSeries();
    QChart* ramChart = new QChart();
    ramChart->addSeries(ramSeries);
    ramChart->legend()->hide();
    ramChart->setTitle("RAM Usage %");
    QValueAxis* ramX = new QValueAxis();
    ramX->setRange(0, 30); ramX->setLabelFormat("%d"); ramChart->addAxis(ramX, Qt::AlignBottom); ramSeries->attachAxis(ramX);
    QValueAxis* ramY = new QValueAxis();
    ramY->setRange(0, 100); ramChart->addAxis(ramY, Qt::AlignLeft); ramSeries->attachAxis(ramY);
    ui->ramChartView->setChart(ramChart);

    networkSeries = new QLineSeries();
    QChart* netChart = new QChart();
    netChart->addSeries(networkSeries);
    netChart->legend()->hide();
    netChart->setTitle("Network (KB/s)");
    QValueAxis* netX = new QValueAxis(); netX->setRange(0, 30); netX->setLabelFormat("%d"); netChart->addAxis(netX, Qt::AlignBottom); networkSeries->attachAxis(netX);
    QValueAxis* netY = new QValueAxis(); netY->setRange(0, 1000); netChart->addAxis(netY, Qt::AlignLeft); networkSeries->attachAxis(netY);
    ui->networkChartView->setChart(netChart);

    diskSeries = new QPieSeries();
    QChart* diskChart = new QChart();
    diskChart->addSeries(diskSeries);
    diskChart->setTitle("Disk Usage");
    ui->diskChartView->setChart(diskChart);
}

void MainWindow::updateSystemStats()
{
    int cpuLoad = cpuMonitor.getCpuUsage();
    int ramLoad = ramMonitor.getUsagePercent();

    ui->cpuProgressBar->setValue(cpuLoad);
    ui->ramProgressBar->setValue(ramLoad);

    cpuSeries->append(timeCounter, cpuLoad);
    ramSeries->append(timeCounter, ramLoad);

    if (cpuSeries->count() > 30) cpuSeries->remove(0);
    if (ramSeries->count() > 30) ramSeries->remove(0);


    int netSpeed = networkMonitor.getSpeedKbPerSec();
    networkSeries->append(timeCounter, netSpeed);
    if (networkSeries->count() > 30) networkSeries->remove(0);


    diskSeries->clear();
    auto disks = diskMonitor.getDiskInfo(); 
    for (auto& [name, percent] : disks) {
        QPieSlice* slice = diskSeries->append(name, percent);
        slice->setLabel(QString("%1: %2%").arg(name).arg(percent));
    }

    timeCounter++;
}
