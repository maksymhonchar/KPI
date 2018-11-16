#pragma once

#include <QDialog>
#include <QTimer>

#include "stats.h"
#include "player.h"
#include "gameinfo.h"

namespace Ui {
class RankingsUI;
}

class RankingsUI : public QDialog
{
    Q_OBJECT

public:
    explicit RankingsUI(GameInfo *gameInfo, Stats *stats, QWidget *parent = 0);
    ~RankingsUI();

private slots:
    void uiUpdate();

private:
    Ui::RankingsUI *ui;

    QTimer *uiUpdateTimer;

    Stats *stats;
    GameInfo *gameInfo;

    void BubbleSort(Player **playerSet, int n);
    void fillTextInLabelByItsName(QString lblName, QString text);
};

