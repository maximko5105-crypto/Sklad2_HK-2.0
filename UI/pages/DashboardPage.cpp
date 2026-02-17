#include "DashboardPage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QTimer>

#include "services/RequestService.h"
#include "../../services/StockService.h"

DashboardPage::DashboardPage(QWidget *parent)
    : QWidget(parent)
{
    setupUI();

    refreshTimer = new QTimer(this);
    connect(refreshTimer, &QTimer::timeout,
            this, &DashboardPage::updateKPI);
    refreshTimer->start(5000);

    updateKPI();
}

void DashboardPage::setupUI()
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40, 40, 40, 40);
    mainLayout->setSpacing(30);

    // ===== Заголовок =====
    QLabel *title = new QLabel("Dashboard");
    title->setStyleSheet(
        "font-size:28px;"
        "font-weight:600;"
    );

    mainLayout->addWidget(title);

    // ===== KPI Layout =====
    auto *kpiLayout = new QHBoxLayout;
    kpiLayout->setSpacing(25);

    QFrame *card1 = createKpiCard("Всего заявок",
                                  totalRequestsValue,
                                  "#3b82f6");

    QFrame *card2 = createKpiCard("Одобрено",
                                  approvedValue,
                                  "#22c55e");

    QFrame *card3 = createKpiCard("В ожидании",
                                  pendingValue,
                                  "#f59e0b");

    QFrame *card4 = createKpiCard("Низкий остаток",
                                  lowStockValue,
                                  "#ef4444");

    kpiLayout->addWidget(card1);
    kpiLayout->addWidget(card2);
    kpiLayout->addWidget(card3);
    kpiLayout->addWidget(card4);

    mainLayout->addLayout(kpiLayout);
    mainLayout->addStretch();
}

QFrame* DashboardPage::createKpiCard(const QString &title,
                                     QLabel* &valueLabel,
                                     const QString &accentColor)
{
    QFrame *card = new QFrame;
    card->setMinimumHeight(140);
    card->setStyleSheet(
        "QFrame {"
        "background: qlineargradient("
        "x1:0 y1:0 x2:1 y2:1,"
        "stop:0 #ffffff,"
        "stop:1 #f1f5f9);"
        "border-radius:16px;"
        "}"
    );

    auto *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(25);
    shadow->setOffset(0, 8);
    shadow->setColor(QColor(0,0,0,40));
    card->setGraphicsEffect(shadow);

    auto *layout = new QVBoxLayout(card);
    layout->setContentsMargins(20, 20, 20, 20);

    QLabel *titleLabel = new QLabel(title);
    titleLabel->setStyleSheet(
        "font-size:14px;"
        "color:#64748b;"
    );

    valueLabel = new QLabel("0");
    valueLabel->setStyleSheet(
        "font-size:32px;"
        "font-weight:700;"
        "color:" + accentColor + ";"
    );

    layout->addWidget(titleLabel);
    layout->addWidget(valueLabel);
    layout->addStretch();

    return card;
}

void DashboardPage::updateKPI()
{
    RequestService requestService;
    StockService stockService;

    auto requests = requestService.getAllRequests();
    auto products = stockService.getAllProducts();

    int total = requests.size();
    int approved = 0;
    int pending = 0;
    int lowStock = 0;

    for (const auto &r : requests)
    {
        if (r.status == "Approved")
            approved++;
        if (r.status == "Pending")
            pending++;
    }

    for (const auto &p : products)
    {
        if (p.quantity < 5)
            lowStock++;
    }

    totalRequestsValue->setText(QString::number(total));
    approvedValue->setText(QString::number(approved));
    pendingValue->setText(QString::number(pending));
    lowStockValue->setText(QString::number(lowStock));
}
