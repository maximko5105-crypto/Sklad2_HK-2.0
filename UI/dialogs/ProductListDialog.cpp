#include "ProductListDialog.h"
#include "../../services/ProductService.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>

ProductListDialog::ProductListDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Список товаров");
    resize(800, 500);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *topLayout = new QHBoxLayout();

    m_searchEdit = new QLineEdit(this);
    m_searchEdit->setPlaceholderText("Поиск по названию...");
    topLayout->addWidget(m_searchEdit);

    m_categoryBox = new QComboBox(this);
    m_categoryBox->addItem("Все категории");
    topLayout->addWidget(m_categoryBox);

    mainLayout->addLayout(topLayout);

    m_table = new QTableWidget(this);
    m_table->setColumnCount(4);
    m_table->setHorizontalHeaderLabels({
        "Название",
        "Штрихкод",
        "Категория",
        "Количество"
    });

    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainLayout->addWidget(m_table);

    connect(m_searchEdit, &QLineEdit::textChanged,
            this, &ProductListDialog::searchProducts);

    connect(m_categoryBox, &QComboBox::currentTextChanged,
            this, &ProductListDialog::filterByCategory);

    loadProducts();
}

void ProductListDialog::loadProducts()
{
    m_products = ProductService::getAllProducts();

    m_categoryBox->clear();
    m_categoryBox->addItem("Все категории");

    QSet<QString> categories;

    for (const Product &p : m_products)
        categories.insert(p.category);

    for (const QString &cat : categories)
        m_categoryBox->addItem(cat);

    updateTable(m_products);
}

void ProductListDialog::updateTable(const QList<Product> &list)
{
    m_table->setRowCount(0);

    int row = 0;
    for (const Product &p : list)
    {
        m_table->insertRow(row);

        m_table->setItem(row, 0, new QTableWidgetItem(p.name));
        m_table->setItem(row, 1, new QTableWidgetItem(p.barcode));
        m_table->setItem(row, 2, new QTableWidgetItem(p.category));
        m_table->setItem(row, 3, new QTableWidgetItem(QString::number(p.quantity)));

        row++;
    }
}

void ProductListDialog::searchProducts()
{
    QString text = m_searchEdit->text();
    QList<Product> list = ProductService::searchProducts(text);
    updateTable(list);
}

void ProductListDialog::filterByCategory()
{
    QString selected = m_categoryBox->currentText();

    if (selected == "Все категории")
    {
        updateTable(m_products);
        return;
    }

    QList<Product> filtered;

    for (const Product &p : m_products)
    {
        if (p.category == selected)
            filtered.append(p);
    }

    updateTable(filtered);
}
