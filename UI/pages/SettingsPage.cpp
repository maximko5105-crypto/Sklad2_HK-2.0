#include "SettingsPage.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QFrame>
#include <QGraphicsDropShadowEffect>
#include <QSettings>
#include <QApplication>

#include "../core/Session.h"

SettingsPage::SettingsPage(QWidget *parent)
    : QWidget(parent)
{
    setupUI();

    QSettings settings("sklad2_HK", "app");
    QString savedTheme = settings.value("theme", "Light").toString();
    themeBox->setCurrentText(savedTheme);
    applyTheme(savedTheme);
}

void SettingsPage::setupUI()
{
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(40,40,40,40);
    mainLayout->setSpacing(30);

    QLabel *title = new QLabel("Настройки");
    title->setStyleSheet("font-size:26px; font-weight:600;");
    mainLayout->addWidget(title);

    // ===== User Card =====
    QFrame *userCard = new QFrame;
    userCard->setStyleSheet(
        "QFrame {"
        "background:white;"
        "border-radius:16px;"
        "}"
    );

    auto *shadow = new QGraphicsDropShadowEffect;
    shadow->setBlurRadius(25);
    shadow->setOffset(0,8);
    shadow->setColor(QColor(0,0,0,40));
    userCard->setGraphicsEffect(shadow);

    auto *cardLayout = new QVBoxLayout(userCard);
    cardLayout->setContentsMargins(20,20,20,20);

    userLabel = new QLabel("Пользователь: " +
        Session::instance().getUsername());

    roleLabel = new QLabel("Роль: " +
        Session::instance().getRole());

    userLabel->setStyleSheet("font-size:16px;");
    roleLabel->setStyleSheet("font-size:16px; color:#64748b;");

    cardLayout->addWidget(userLabel);
    cardLayout->addWidget(roleLabel);

    mainLayout->addWidget(userCard);

    // ===== Theme =====
    QLabel *themeLabel = new QLabel("Тема оформления:");
    themeLabel->setStyleSheet("font-size:16px;");

    themeBox = new QComboBox;
    themeBox->addItems({"Light", "Dark"});

    mainLayout->addWidget(themeLabel);
    mainLayout->addWidget(themeBox);

    logoutButton = new QPushButton("Выйти из аккаунта");
    logoutButton->setStyleSheet(
        "QPushButton {"
        "background:#ef4444;"
        "color:white;"
        "padding:10px;"
        "border-radius:8px;"
        "}"
        "QPushButton:hover {"
        "background:#dc2626;"
        "}"
    );

    mainLayout->addWidget(logoutButton);
    mainLayout->addStretch();

    // Connections
    connect(themeBox, &QComboBox::currentTextChanged,
            this, &SettingsPage::applyTheme);

    connect(logoutButton, &QPushButton::clicked,
            this, &SettingsPage::logoutRequested);
}

void SettingsPage::applyTheme(const QString &theme)
{
    QSettings settings("sklad2_HK", "app");
    settings.setValue("theme", theme);

    if (theme == "Dark")
    {
        qApp->setStyleSheet(
            "QWidget {"
            "background:#0f172a;"
            "color:white;"
            "}"
            "QFrame {"
            "background:#1e293b;"
            "}"
            "QLineEdit, QComboBox {"
            "background:#334155;"
            "border:1px solid #475569;"
            "padding:6px;"
            "border-radius:6px;"
            "color:white;"
            "}"
            "QPushButton {"
            "background:#2563eb;"
            "color:white;"
            "padding:8px;"
            "border-radius:6px;"
            "}"
            "QPushButton:hover {"
            "background:#1d4ed8;"
            "}"
        );
    }
    else
    {
        qApp->setStyleSheet(
            "QWidget {"
            "background:#f8fafc;"
            "color:#0f172a;"
            "}"
            "QFrame {"
            "background:white;"
            "}"
            "QLineEdit, QComboBox {"
            "background:white;"
            "border:1px solid #cbd5e1;"
            "padding:6px;"
            "border-radius:6px;"
            "}"
            "QPushButton {"
            "background:#2563eb;"
            "color:white;"
            "padding:8px;"
            "border-radius:6px;"
            "}"
            "QPushButton:hover {"
            "background:#1d4ed8;"
            "}"
        );
    }
}
