#ifndef ANALYTICSPAGE_H
#define ANALYTICSPAGE_H

#include <QWidget>
#include <QVBoxLayout>

#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

class AnalyticsPage : public QWidget
{
    Q_OBJECT

public:
    explicit AnalyticsPage(QWidget *parent = nullptr);

private:
    void setupCharts();   // ← ВАЖНО: было забыто

    QVBoxLayout *mainLayout;

    QChartView *requestsChartView;
    QChartView *stockChartView;
};

#endif // ANALYTICSPAGE_H
