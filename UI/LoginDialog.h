#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

class QLineEdit;
class QPushButton;

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget* parent = nullptr);

    int getUserId() const;
    QString getUserRole() const;

private slots:
    void attemptLogin();

private:
    QLineEdit* m_loginEdit;
    QLineEdit* m_passwordEdit;
    QPushButton* m_loginButton;

    int m_userId;
    QString m_userRole;
};

#endif // LOGINDIALOG_H
