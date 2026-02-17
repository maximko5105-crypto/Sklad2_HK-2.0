#include "RequestsPage.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QStackedWidget>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QMessageBox>

#include "../../services/RequestService.h"
#include "../../services/Logger.h"
#include "../../core/Session.h"

RequestsPage::RequestsPage(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    loadRequests();
}

void RequestsPage::setupUI()
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40,40,40,40);
    mainLayout->setSpacing(20);

    stack = new QStackedWidget;
    mainLayout->addWidget(stack);

    // ================= LIST PAGE =================
    listPage = new QWidget;
    auto *listLayout = new QVBoxLayout(listPage);
    listLayout->setSpacing(15);

    QLabel *title = new QLabel("Заявки");
    title->setStyleSheet("font-size:26px; font-weight:600;");
    listLayout->addWidget(title);

    auto *topBar = new QHBoxLayout;

    searchEdit = new QLineEdit;
    searchEdit->setPlaceholderText("Поиск заявки...");

    statusFilter = new QComboBox;
    statusFilter->addItems({"Все", "Pending", "Approved", "Rejected"});

    createButton = new QPushButton("Создать заявку");
    approveButton = new QPushButton("Одобрить");
    rejectButton = new QPushButton("Отклонить");

    if (Session::instance().getRole() != "admin")
    {
        approveButton->setDisabled(true);
        rejectButton->setDisabled(true);
    }

    topBar->addWidget(searchEdit);
    topBar->addWidget(statusFilter);
    topBar->addStretch();
    topBar->addWidget(createButton);
    topBar->addWidget(approveButton);
    topBar->addWidget(rejectButton);

    listLayout->addLayout(topBar);

    table = new QTableWidget;
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels(
        {"ID", "Название", "Количество", "Статус"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    listLayout->addWidget(table);
    stack->addWidget(listPage);

    // ================= FORM PAGE =================
    formPage = new QWidget;
    auto *formLayout = new QVBoxLayout(formPage);

    QLabel *formTitle = new QLabel("Создание заявки");
    formTitle->setStyleSheet("font-size:22px; font-weight:600;");

    titleEdit = new QLineEdit;
    titleEdit->setPlaceholderText("Название товара");

    quantityEdit = new QLineEdit;
    quantityEdit->setPlaceholderText("Количество");

    saveButton = new QPushButton("Сохранить");
    cancelButton = new QPushButton("Отмена");

    formLayout->addWidget(formTitle);
    formLayout->addWidget(titleEdit);
    formLayout->addWidget(quantityEdit);
    formLayout->addWidget(saveButton);
    formLayout->addWidget(cancelButton);
    formLayout->addStretch();

    stack->addWidget(formPage);

    // ================= CONNECTIONS =================

    connect(createButton, &QPushButton::clicked, [this]() {
        stack->setCurrentWidget(formPage);
    });

    connect(cancelButton, &QPushButton::clicked, [this]() {
        stack->setCurrentWidget(listPage);
    });

    connect(saveButton, &QPushButton::clicked, [this]() {

        QString title = titleEdit->text();
        int qty = quantityEdit->text().toInt();

        if (title.isEmpty() || qty <= 0)
            return;

        RequestService service;
        service.createRequest(title, qty);

        LogService::log("Создана заявка");

        titleEdit->clear();
        quantityEdit->clear();

        stack->setCurrentWidget(listPage);
        loadRequests();
    });

    connect(searchEdit, &QLineEdit::textChanged,
            this, &RequestsPage::applyFilters);

    connect(statusFilter, &QComboBox::currentTextChanged,
            this, &RequestsPage::applyFilters);

    connect(approveButton, &QPushButton::clicked, [this]() {

        if (table->currentRow() < 0) return;

        int id = table->item(table->currentRow(),0)->text().toInt();

        RequestService service;
        service.updateStatus(id, "Approved");

        LogService::log("Одобрена заявка");

        loadRequests();
    });

    connect(rejectButton, &QPushButton::clicked, [this]() {

        if (table->currentRow() < 0) return;

        int id = table->item(table->currentRow(),0)->text().toInt();

        RequestService service;
        service.updateStatus(id, "Rejected");

        LogService::log("Отклонена заявка");

        loadRequests();
    });
}

void RequestsPage::loadRequests()
{
    RequestService service;
    auto requests = service.getAllRequests();

    table->setRowCount(requests.size());

    for (int i = 0; i < requests.size(); ++i)
    {
        table->setItem(i,0,
            new QTableWidgetItem(QString::number(requests[i].id)));

        table->setItem(i,1,
            new QTableWidgetItem(requests[i].title));

        table->setItem(i,2,
            new QTableWidgetItem(QString::number(requests[i].quantity)));

        createStatusBadge(i, requests[i].status);
    }

    applyFilters();
}

void RequestsPage::createStatusBadge(int row, const QString &status)
{
    QTableWidgetItem *item = new QTableWidgetItem(status);
    item->setTextAlignment(Qt::AlignCenter);

    if (status == "Pending")
    {
        item->setBackground(QColor("#f59e0b"));
        item->setForeground(Qt::white);
    }
    else if (status == "Approved")
    {
        item->setBackground(QColor("#22c55e"));
        item->setForeground(Qt::white);
    }
    else if (status == "Rejected")
    {
        item->setBackground(QColor("#ef4444"));
        item->setForeground(Qt::white);
    }

    table->setItem(row,3,item);
}

void RequestsPage::applyFilters()
{
    QString search = searchEdit->text().toLower();
    QString status = statusFilter->currentText();

    for (int i = 0; i < table->rowCount(); ++i)
    {
        QString title = table->item(i,1)->text().toLower();
        QString rowStatus = table->item(i,3)->text();

        bool matchSearch = title.contains(search);
        bool matchStatus = (status == "Все" || status == rowStatus);

        table->setRowHidden(i, !(matchSearch && matchStatus));
    }
}
