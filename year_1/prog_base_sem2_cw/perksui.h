#pragma once

#include <QDialog>
#include <QTimer>

#include "stats.h"
#include "enemy.h"
#include "heropowers.h"

namespace Ui {
class PerksUI;
}

class PerksUI : public QDialog
{
    Q_OBJECT

public:
    explicit PerksUI(Stats *stats, Enemy *enemy, HeroPowers *heropowers, QWidget *parent = 0);
    ~PerksUI();

private:
    // UI object.
    Ui::PerksUI *ui;

    Stats *stats;
    Enemy *enemy;
    HeroPowers *heropowers;

    QTimer *timerUpdate;

private slots:
    // Buttons behavior handlers.
    void on_perksPassLvl_btn_clicked();
    void on_perksDmndRush_btn_clicked();
    void on_perksEnchantedSwrd_btn_clicked();
    void on_perksEldoradoBtn_clicked();
    void on_perksWindfury_btn_clicked();
};
