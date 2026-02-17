#include "LoginDialog.h"
#include "../services/AuthService.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget* parent)
    : QDialog(parent),
      m_userId(-1)
{
    setWindowTitle("Вход в систему");
    resize(300, 150);

    QVBoxLayout* layout = new QVBoxLayout(this);

    m_loginEdit = new QLineEdit(this);
    m_loginEdit->setPlaceholderText("Логин");

    m_passwordEdit = new QLineEdit(this);
    m_passwordEdit->setPlaceholderText("Пароль");
    m_passwordEdit->setEchoMode(QLineEdit::Password);

    m_loginButton = new QPushButton("Войти", this);

    layout->addWidget(m_loginEdit);
    layout->addWidget(m_passwordEdit);
    layout->addWidget(m_loginButton);

    connect(m_loginButton, &QPushButton::clicked,
            this, &LoginDialog::attemptLogin);
}

void LoginDialog::attemptLogin()
{
    QString login = m_loginEdit->text();
    QString password = m_passwordEdit->text();

    AuthService auth;

    int userId;
    QString role;

    if (auth.login(login, password, userId, role))
    {
        m_userId = userId;
        m_userRole = role;
        accept();
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Неверный логин или пароль");
    }
}

int LoginDialog::getUserId() const
{
    return m_userId;
}

QString LoginDialog::getUserRole() const
{
    return m_userRole;
}
