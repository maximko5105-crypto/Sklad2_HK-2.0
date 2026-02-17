#ifndef DASHBOARDPAGE_H
#define DASHBOARDPAGE_H

#include <QWidget>

class QLabel;
class QTimer;
class QFrame;

class DashboardPage : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardPage(QWidget *parent = nullptr);

private:
    void setupUI();
    void updateKPI();
    QFrame* createKpiCard(const QString &title,
                          QLabel* &valueLabel,
                          const QString &accentColor);

    QLabel *totalRequestsValue;
    QLabel *approvedValue;
    QLabel *pendingValue;
    QLabel *lowStockValue;

    QTimer *refreshTimer;
};

#endif
