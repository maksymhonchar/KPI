#pragma once

#include <QDialog>
#include <QTimer>

#include "achvments.h"

namespace Ui {
class AchvmentsUI;
}

class AchvmentsUI : public QDialog
{
    Q_OBJECT

public:
    explicit AchvmentsUI(Achvments *achvments, QWidget *parent = 0);
    ~AchvmentsUI();

private:
    Ui::AchvmentsUI *ui;
    Achvments *achvments;
    QTimer *updateTimer;

private slots:
    void updateUI();
};
