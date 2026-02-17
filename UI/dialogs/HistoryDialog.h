#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H

#include <QDialog>

class QTableView;
class QLineEdit;

class HistoryDialog : public QDialog
{
    Q_OBJECT
public:
    explicit HistoryDialog(QWidget *parent = nullptr);

private:
    QTableView *table;
    QLineEdit  *filterEdit;

    void loadHistory(const QString& filter="");
};

#endif
