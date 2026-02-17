#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QListWidget;
class QStackedWidget;
class QWidget;
class QPushButton;

class DashboardPage;
class RequestsPage;
class OrdersPage;
class WarehousePage;
class AnalyticsPage;
class ReportsPage;
class SettingsPage;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void setupUI();
    void setupSidebar();
    void setupPages();
    void applyLightTheme();
    void applyDarkTheme();
    void updateAccessByRole();

    QWidget *centralWidgetContainer;
    QListWidget *sidebar;
    QStackedWidget *stack;

    QPushButton *themeToggleButton;

    // Pages
    DashboardPage *dashboardPage;
    RequestsPage *requestsPage;
    OrdersPage *ordersPage;
    WarehousePage *warehousePage;
    AnalyticsPage *analyticsPage;
    ReportsPage *reportsPage;
    SettingsPage *settingsPage;

    bool isDarkTheme = true;
};

#endif
