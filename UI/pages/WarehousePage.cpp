#include "WarehousePage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QMessageBox>

#include "../../services/StockService.h"
#include "../../services/LogService.h"
#include "../../services/QRService.h"
#include "../../core/Session.h"

WarehousePage::WarehousePage(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    loadProducts();
}

void WarehousePage::setupUI()
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40,40,40,40);
    mainLayout->setSpacing(20);

    stack = new QStackedWidget;
    mainLayout->addWidget(stack);

    // ================= LIST =================
    listPage = new QWidget;
    auto *listLayout = new QVBoxLayout(listPage);

    QLabel *title = new QLabel("Склад");
    title->setStyleSheet("font-size:26px; font-weight:600;");
    listLayout->addWidget(title);

    auto *topBar = new QHBoxLayout;

    searchEdit = new QLineEdit;
    searchEdit->setPlaceholderText("Поиск товара...");

    addButton = new QPushButton("Добавить товар");
    increaseButton = new QPushButton("Приход");
    decreaseButton = new QPushButton("Списание");
    qrButton = new QPushButton("QR");

    if (Session::instance().getRole() != "admin")
    {
        addButton->setDisabled(true);
        increaseButton->setDisabled(true);
        decreaseButton->setDisabled(true);
    }

    topBar->addWidget(searchEdit);
    topBar->addStretch();
    topBar->addWidget(addButton);
    topBar->addWidget(increaseButton);
    topBar->addWidget(decreaseButton);
    topBar->addWidget(qrButton);

    listLayout->addLayout(topBar);

    table = new QTableWidget;
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels(
        {"ID", "Название", "Количество"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    listLayout->addWidget(table);
    stack->addWidget(listPage);

    // ================= FORM =================
    formPage = new QWidget;
    auto *formLayout = new QVBoxLayout(formPage);

    QLabel *formTitle = new QLabel("Новый товар");
    formTitle->setStyleSheet("font-size:22px; font-weight:600;");

    nameEdit = new QLineEdit;
    nameEdit->setPlaceholderText("Название товара");

    quantityEdit = new QLineEdit;
    quantityEdit->setPlaceholderText("Количество");

    saveButton = new QPushButton("Сохранить");
    backButton = new QPushButton("Назад");

    formLayout->addWidget(formTitle);
    formLayout->addWidget(nameEdit);
    formLayout->addWidget(quantityEdit);
    formLayout->addWidget(saveButton);
    formLayout->addWidget(backButton);
    formLayout->addStretch();

    stack->addWidget(formPage);

    // ================= CONNECTIONS =================

    connect(addButton, &QPushButton::clicked, [this]() {
        stack->setCurrentWidget(formPage);
    });

    connect(backButton, &QPushButton::clicked, [this]() {
        stack->setCurrentWidget(listPage);
    });

    connect(saveButton, &QPushButton::clicked, [this]() {

        QString name = nameEdit->text();
        int qty = quantityEdit->text().toInt();

        if (name.isEmpty() || qty < 0)
            return;

        StockService service;
        service.addOrCreateProduct(name, qty);

        LogService::log("Добавлен товар на склад");

        nameEdit->clear();
        quantityEdit->clear();

        stack->setCurrentWidget(listPage);
        loadProducts();
    });

    connect(searchEdit, &QLineEdit::textChanged, [this]() {

        QString search = searchEdit->text().toLower();

        for (int i = 0; i < table->rowCount(); ++i)
        {
            QString name =
                table->item(i,1)->text().toLower();

            table->setRowHidden(i,
                !name.contains(search));
        }
    });

    connect(increaseButton, &QPushButton::clicked, [this]() {

        if (table->currentRow() < 0) return;

        int id = table->item(table->currentRow(),0)->text().toInt();

        StockService service;
        service.changeQuantity(id, 1);

        LogService::log("Приход товара");

        loadProducts();
    });

    connect(decreaseButton, &QPushButton::clicked, [this]() {

        if (table->currentRow() < 0) return;

        int id = table->item(table->currentRow(),0)->text().toInt();

        StockService service;
        service.changeQuantity(id, -1);

        LogService::log("Списание товара");

        loadProducts();
    });

    connect(qrButton, &QPushButton::clicked, [this]() {

        if (table->currentRow() < 0) return;

        QString name = table->item(
            table->currentRow(),1)->text();

        QRService qr;
        qr.generate(name);
    });
}

void WarehousePage::loadProducts()
{
    StockService service;
    auto products = service.getAllProducts();

    table->setRowCount(products.size());

    for (int i = 0; i < products.size(); ++i)
    {
        table->setItem(i,0,
            new QTableWidgetItem(QString::number(products[i].id)));

        table->setItem(i,1,
            new QTableWidgetItem(products[i].name));

        QTableWidgetItem *qtyItem =
            new QTableWidgetItem(
                QString::number(products[i].quantity));

        qtyItem->setTextAlignment(Qt::AlignCenter);

        table->setItem(i,2,qtyItem);

        highlightLowStock(i, products[i].quantity);
    }
}

void WarehousePage::highlightLowStock(int row, int quantity)
{
    if (quantity < 5)
    {
        for (int col = 0; col < table->columnCount(); ++col)
        {
            table->item(row,col)
                ->setBackground(QColor("#fee2e2"));
        }
    }
}
