#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QWidget>

class QTabWidget;
class QLineEdit;
class QPushButton;

class AuthWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AuthWindow(QWidget *parent = nullptr);

signals:
    void loginSuccessful(int userId, const QString &role);

private slots:
    void handleLogin();
    void handleRegister();

private:
    void setupUI();

    QTabWidget* tabWidget;

    // Login
    QLineEdit* loginEdit;
    QLineEdit* passwordEdit;
    QPushButton* loginButton;

    // Register
    QLineEdit* regLoginEdit;
    QLineEdit* regPasswordEdit;
    QPushButton* registerButton;
};

#endif // AUTHWINDOW_H
