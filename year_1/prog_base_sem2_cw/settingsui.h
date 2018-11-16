#pragma once

#include <QDialog>
#include <QTimer>

#include "stats.h"
#include "gameinfo.h"

namespace Ui {
class SettingsUI;
}

class SettingsUI : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsUI(GameInfo *gameInfo, Stats *stats, QWidget *parent = 0);
    ~SettingsUI();

private slots:
    void updateUI();
    // "Save" button behavior.
    void on_save_btn_clicked();
    // "Share" buttons behavior.
    void on_vkshare_btn_clicked();
    void on_fbshare_btn_clicked();
    void on_twishare_btn_clicked();

private:
    Ui::SettingsUI *ui;
    QTimer *updateUITimer;
    Stats *stats;
    GameInfo *gameInfo;
    QString humanizeNumber(long long num);
};
