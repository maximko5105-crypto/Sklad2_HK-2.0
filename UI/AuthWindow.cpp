#include "AuthWindow.h"
#include "../services/AuthService.h"

#include <QTabWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

AuthWindow::AuthWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Авторизация");
    resize(400, 300);
    setupUI();
}

void AuthWindow::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    tabWidget = new QTabWidget(this);

    // ===== ВКЛАДКА ВХОД =====
    QWidget* loginTab = new QWidget();
    QVBoxLayout* loginLayout = new QVBoxLayout(loginTab);

    loginEdit = new QLineEdit();
    loginEdit->setPlaceholderText("Логин");

    passwordEdit = new QLineEdit();
    passwordEdit->setPlaceholderText("Пароль");
    passwordEdit->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("Войти");

    loginLayout->addWidget(loginEdit);
    loginLayout->addWidget(passwordEdit);
    loginLayout->addWidget(loginButton);

    tabWidget->addTab(loginTab, "Вход");

    // ===== ВКЛАДКА РЕГИСТРАЦИЯ =====
    QWidget* regTab = new QWidget();
    QVBoxLayout* regLayout = new QVBoxLayout(regTab);

    regLoginEdit = new QLineEdit();
    regLoginEdit->setPlaceholderText("Логин");

    regPasswordEdit = new QLineEdit();
    regPasswordEdit->setPlaceholderText("Пароль");
    regPasswordEdit->setEchoMode(QLineEdit::Password);

    registerButton = new QPushButton("Зарегистрироваться");

    regLayout->addWidget(regLoginEdit);
    regLayout->addWidget(regPasswordEdit);
    regLayout->addWidget(registerButton);

    tabWidget->addTab(regTab, "Регистрация");

    mainLayout->addWidget(tabWidget);

    connect(loginButton, &QPushButton::clicked,
            this, &AuthWindow::handleLogin);

    connect(registerButton, &QPushButton::clicked,
            this, &AuthWindow::handleRegister);
}

void AuthWindow::handleLogin()
{
    QString login = loginEdit->text();
    QString password = passwordEdit->text();

    AuthService auth;

    int userId;
    QString role;

    if (auth.login(login, password, userId, role))
    {
        emit loginSuccessful(userId, role);
    }
    else
    {
        QMessageBox::warning(this, "Ошибка",
                             "Неверный логин или пароль");
    }
}

void AuthWindow::handleRegister()
{
    QString login = regLoginEdit->text();
    QString password = regPasswordEdit->text();

    if (login.isEmpty() || password.isEmpty())
    {
        QMessageBox::warning(this, "Ошибка",
                             "Заполните все поля");
        return;
    }

    AuthService auth;

    if (auth.registerUser(login, password, "user"))
    {
        QMessageBox::information(this,
                                 "Успех",
                                 "Регистрация прошла успешно!");

        // После регистрации сразу логиним
        int userId;
        QString role;

        if (auth.login(login, password, userId, role))
        {
            emit loginSuccessful(userId, role);
        }
    }
    else
    {
        QMessageBox::warning(this,
                             "Ошибка",
                             "Пользователь уже существует");
    }
}
