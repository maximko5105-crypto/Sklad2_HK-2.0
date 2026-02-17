#include "OrdersPage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>

#include "../../services/OrderService.h"
#include "../../services/StockService.h"
#include "../../services/Logger.h"
#include "../../core/Session.h"

OrdersPage::OrdersPage(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    loadOrders();
}

void OrdersPage::setupUI()
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40,40,40,40);
    mainLayout->setSpacing(20);

    stack = new QStackedWidget;
    mainLayout->addWidget(stack);

    // ================= LIST =================
    listPage = new QWidget;
    auto *listLayout = new QVBoxLayout(listPage);

    QLabel *title = new QLabel("Заказы на склад");
    title->setStyleSheet("font-size:26px; font-weight:600;");
    listLayout->addWidget(title);

    auto *topBar = new QHBoxLayout;

    searchEdit = new QLineEdit;
    searchEdit->setPlaceholderText("Поиск заказа...");

    createButton = new QPushButton("Заказать на склад");
    deliverButton = new QPushButton("Доставлено");
    cancelButton = new QPushButton("Отменить");

    if (Session::instance().getRole() != "admin")
    {
        deliverButton->setDisabled(true);
        cancelButton->setDisabled(true);
    }

    topBar->addWidget(searchEdit);
    topBar->addStretch();
    topBar->addWidget(createButton);
    topBar->addWidget(deliverButton);
    topBar->addWidget(cancelButton);

    listLayout->addLayout(topBar);

    table = new QTableWidget;
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels(
        {"ID", "Товар", "Количество", "Статус"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    listLayout->addWidget(table);
    stack->addWidget(listPage);

    // ================= FORM =================
    formPage = new QWidget;
    auto *formLayout = new QVBoxLayout(formPage);

    QLabel *formTitle = new QLabel("Новый заказ");
    formTitle->setStyleSheet("font-size:22px; font-weight:600;");

    productEdit = new QLineEdit;
    productEdit->setPlaceholderText("Название товара");

    quantityEdit = new QLineEdit;
    quantityEdit->setPlaceholderText("Количество");

    saveButton = new QPushButton("Создать заказ");
    backButton = new QPushButton("Назад");

    formLayout->addWidget(formTitle);
    formLayout->addWidget(productEdit);
    formLayout->addWidget(quantityEdit);
    formLayout->addWidget(saveButton);
    formLayout->addWidget(backButton);
    formLayout->addStretch();

    stack->addWidget(formPage);

    // ================= CONNECTIONS =================

    connect(createButton, &QPushButton::clicked, [this]() {
        stack->setCurrentWidget(formPage);
    });

    connect(backButton, &QPushButton::clicked, [this]() {
        stack->setCurrentWidget(listPage);
    });

    connect(saveButton, &QPushButton::clicked, [this]() {

        QString product = productEdit->text();
        int qty = quantityEdit->text().toInt();

        if (product.isEmpty() || qty <= 0)
            return;

        OrderService service;
        service.createOrder(product, qty);

        LogService::log("Создан заказ");

        productEdit->clear();
        quantityEdit->clear();

        stack->setCurrentWidget(listPage);
        loadOrders();
    });

    connect(searchEdit, &QLineEdit::textChanged, [this]() {

        QString search = searchEdit->text().toLower();

        for (int i = 0; i < table->rowCount(); ++i)
        {
            QString product =
                table->item(i,1)->text().toLower();

            table->setRowHidden(i,
                !product.contains(search));
        }
    });

    connect(deliverButton, &QPushButton::clicked, [this]() {

        if (table->currentRow() < 0) return;

        int id = table->item(table->currentRow(),0)->text().toInt();
        QString product = table->item(table->currentRow(),1)->text();
        int qty = table->item(table->currentRow(),2)->text().toInt();

        OrderService service;
        service.updateStatus(id, "Delivered");

        // Добавляем товар на склад
        StockService stock;
        stock.addOrCreateProduct(product, qty);

        LogService::log("Заказ доставлен");

        loadOrders();
    });

    connect(cancelButton, &QPushButton::clicked, [this]() {

        if (table->currentRow() < 0) return;

        int id = table->item(table->currentRow(),0)->text().toInt();

        OrderService service;
        service.updateStatus(id, "Cancelled");

        LogService::log("Заказ отменен");

        loadOrders();
    });
}

void OrdersPage::loadOrders()
{
    OrderService service;
    auto orders = service.getAllOrders();

    table->setRowCount(orders.size());

    for (int i = 0; i < orders.size(); ++i)
    {
        table->setItem(i,0,
            new QTableWidgetItem(QString::number(orders[i].id)));

        table->setItem(i,1,
            new QTableWidgetItem(orders[i].product));

        table->setItem(i,2,
            new QTableWidgetItem(QString::number(orders[i].quantity)));

        createStatusBadge(i, orders[i].status);
    }
}

void OrdersPage::createStatusBadge(int row, const QString &status)
{
    QTableWidgetItem *item = new QTableWidgetItem(status);
    item->setTextAlignment(Qt::AlignCenter);

    if (status == "Ordered")
    {
        item->setBackground(QColor("#3b82f6"));
        item->setForeground(Qt::white);
    }
    else if (status == "Delivered")
    {
        item->setBackground(QColor("#22c55e"));
        item->setForeground(Qt::white);
    }
    else if (status == "Cancelled")
    {
        item->setBackground(QColor("#ef4444"));
        item->setForeground(Qt::white);
    }

    table->setItem(row,3,item);
}
