#include "MainWindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QFont>

#include "pages/DashboardPage.h"
#include "pages/RequestsPage.h"
#include "pages/OrdersPage.h"
#include "pages/WarehousePage.h"
#include "pages/AnalyticsPage.h"
#include "pages/ReportsPage.h"
#include "pages/SettingsPage.h"

#include "../core/Session.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("sklad2_HK");
    resize(1400, 850);

    setupUI();
    setupSidebar();
    setupPages();
    updateAccessByRole();
    applyDarkTheme();
}

void MainWindow::setupUI()
{
    centralWidgetContainer = new QWidget;
    setCentralWidget(centralWidgetContainer);

    auto *mainLayout = new QHBoxLayout(centralWidgetContainer);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    sidebar = new QListWidget;
    sidebar->setFixedWidth(240);

    stack = new QStackedWidget;

    mainLayout->addWidget(sidebar);
    mainLayout->addWidget(stack);
}

void MainWindow::setupSidebar()
{
    sidebar->addItem("📊 Dashboard");
    sidebar->addItem("📄 Заявки");
    sidebar->addItem("📦 Заказы");
    sidebar->addItem("🏬 Склад");
    sidebar->addItem("📈 Аналитика");
    sidebar->addItem("🧾 Отчёты");
    sidebar->addItem("⚙ Настройки");

    connect(sidebar, &QListWidget::currentRowChanged,
            stack, &QStackedWidget::setCurrentIndex);

    sidebar->setCurrentRow(0);
}

void MainWindow::setupPages()
{
    dashboardPage = new DashboardPage;
    requestsPage = new RequestsPage;
    ordersPage = new OrdersPage;
    warehousePage = new WarehousePage;
    analyticsPage = new AnalyticsPage;
    reportsPage = new ReportsPage;
    settingsPage = new SettingsPage;

    stack->addWidget(dashboardPage);
    stack->addWidget(requestsPage);
    stack->addWidget(ordersPage);
    stack->addWidget(warehousePage);
    stack->addWidget(analyticsPage);
    stack->addWidget(reportsPage);
    stack->addWidget(settingsPage);
}

void MainWindow::updateAccessByRole()
{
    QString role = Session::instance().getRole();

    if (role == "user")
    {
        sidebar->item(2)->setHidden(true); // Заказы
        sidebar->item(4)->setHidden(true); // Аналитика
        sidebar->item(5)->setHidden(true); // Отчёты
    }
}

void MainWindow::applyDarkTheme()
{
    isDarkTheme = true;

    qApp->setStyleSheet(R"(
        QMainWindow { background-color: #0F172A; }

        QListWidget {
            background-color: #111827;
            border: none;
            color: #E2E8F0;
            font-size: 15px;
        }

        QListWidget::item {
            padding: 14px;
        }

        QListWidget::item:selected {
            background-color: #0EA5E9;
            color: white;
            border-radius: 8px;
        }
    )");
}

void MainWindow::applyLightTheme()
{
    isDarkTheme = false;

    qApp->setStyleSheet(R"(
        QMainWindow { background-color: #F1F5F9; }

        QListWidget {
            background-color: white;
            border: none;
            color: #0F172A;
            font-size: 15px;
        }

        QListWidget::item {
            padding: 14px;
        }

        QListWidget::item:selected {
            background-color: #38BDF8;
            color: white;
            border-radius: 8px;
        }
    )");
}
