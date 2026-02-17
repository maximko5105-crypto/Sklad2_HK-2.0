#ifndef CONTAINERDIALOG_H
#define CONTAINERDIALOG_H

#include <QDialog>

class QComboBox;
class QSpinBox;

class ContainerDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ContainerDialog(QWidget *parent = nullptr);

private:
    QComboBox *containerBox;
    QComboBox *productBox;
    QSpinBox *qtySpin;

    void loadData();
};

#endif
