#include "AddProductDialog.h"
#include "../../services/ProductService.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QMessageBox>

AddProductDialog::AddProductDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Добавить товар");
    resize(300, 200);

    QVBoxLayout *layout = new QVBoxLayout(this);

    m_nameEdit = new QLineEdit(this);
    m_nameEdit->setPlaceholderText("Название товара");
    layout->addWidget(m_nameEdit);

    m_categoryEdit = new QLineEdit(this);
    m_categoryEdit->setPlaceholderText("Категория");
    layout->addWidget(m_categoryEdit);

    m_quantitySpin = new QSpinBox(this);
    m_quantitySpin->setMinimum(0);
    m_quantitySpin->setMaximum(100000);
    layout->addWidget(m_quantitySpin);

    m_addButton = new QPushButton("Добавить", this);
    layout->addWidget(m_addButton);

    connect(m_addButton, &QPushButton::clicked,
            this, &AddProductDialog::onAddClicked);
}

void AddProductDialog::onAddClicked()
{
    QString name = m_nameEdit->text().trimmed();
    QString category = m_categoryEdit->text().trimmed();
    int quantity = m_quantitySpin->value();

    if (name.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка",
                             "Введите название товара");
        return;
    }

    if (ProductService::addProduct(name, category, quantity))
    {
        QMessageBox::information(this, "Успех",
                                 "Товар успешно добавлен");
        accept();
    }
    else
    {
        QMessageBox::critical(this, "Ошибка",
                              "Не удалось добавить товар");
    }
}
