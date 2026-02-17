#include "AnalyticsPage.h"

#include <QStringList>
#include <QPainter>

using namespace QtCharts;

AnalyticsPage::AnalyticsPage(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);

    requestsChartView = new QChartView(this);
    stockChartView = new QChartView(this);

    mainLayout->addWidget(requestsChartView);
    mainLayout->addWidget(stockChartView);

    setupCharts();
}

void AnalyticsPage::setupCharts()
{
    QStringList categories = {"Mon", "Tue", "Wed", "Thu", "Fri"};

    // Requests Chart

    QBarSet *requestSet = new QBarSet("Requests");
    *requestSet << 5 << 8 << 3 << 6 << 10;

    QBarSeries *requestSeries = new QBarSeries();
    requestSeries->append(requestSet);

    QChart *requestChart = new QChart();
    requestChart->addSeries(requestSeries);
    requestChart->setTitle("Requests Overview");
    requestChart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *requestAxisX = new QBarCategoryAxis();
    requestAxisX->append(categories);

    QValueAxis *requestAxisY = new QValueAxis();
    requestAxisY->setRange(0, 15);

    requestChart->addAxis(requestAxisX, Qt::AlignBottom);
    requestChart->addAxis(requestAxisY, Qt::AlignLeft);

    requestSeries->attachAxis(requestAxisX);
    requestSeries->attachAxis(requestAxisY);

    requestsChartView->setChart(requestChart);
    requestsChartView->setRenderHint(QPainter::Antialiasing);


    QBarSet *stockSet = new QBarSet("Stock");
    *stockSet << 20 << 15 << 30 << 12 << 25;

    QBarSeries *stockSeries = new QBarSeries();
    stockSeries->append(stockSet);

    QChart *stockChart = new QChart();
    stockChart->addSeries(stockSeries);
    stockChart->setTitle("Stock Overview");
    stockChart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *stockAxisX = new QBarCategoryAxis();
    stockAxisX->append(categories);

    QValueAxis *stockAxisY = new QValueAxis();
    stockAxisY->setRange(0, 40);

    stockChart->addAxis(stockAxisX, Qt::AlignBottom);
    stockChart->addAxis(stockAxisY, Qt::AlignLeft);

    stockSeries->attachAxis(stockAxisX);
    stockSeries->attachAxis(stockAxisY);

    stockChartView->setChart(stockChart);
    stockChartView->setRenderHint(QPainter::Antialiasing);
}
