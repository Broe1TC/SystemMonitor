#pragma once

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QPieSeries>
#include "CpuMonitor.h"
#include "RamMonitor.h"
#include "DiskMonitor.h"
#include "NetworkMonitor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void updateSystemStats();

private:
    Ui::MainWindow* ui;

    CpuMonitor cpuMonitor;
    RamMonitor ramMonitor;
    DiskMonitor diskMonitor;
    NetworkMonitor networkMonitor;

    QLineSeries* cpuSeries;
    QLineSeries* ramSeries;
    QLineSeries* networkSeries;
    QPieSeries* diskSeries;

    int timeCounter = 0;

    void setupCharts();
    void setupTheme();
};
