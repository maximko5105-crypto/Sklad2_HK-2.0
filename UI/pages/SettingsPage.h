#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "../../core/Logger.h"

class SettingsPage : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsPage(QWidget *parent = nullptr);

private:
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QPushButton *clearLogsButton;

private slots:
    void onClearLogs();
};

#endif // SETTINGSPAGE_H
