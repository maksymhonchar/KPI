#include <QLabel>
#include <QDebug>

#include "rankingsui.h"
#include "ui_rankingsui.h"

RankingsUI::RankingsUI(GameInfo *gameInfo, Stats *stats, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RankingsUI)
{
    ui->setupUi(this);

    // Disable 'help' button.
    Qt::WindowFlags flags = this->windowFlags();
    flags &= ~Qt::WindowContextHelpButtonHint;
    this->setWindowFlags(flags);

    this->stats = stats;
    this->gameInfo = gameInfo;

    this->uiUpdateTimer = new QTimer(this);
    connect(uiUpdateTimer, SIGNAL(timeout()), this, SLOT(uiUpdate()));
    this->uiUpdateTimer->start(100);

    setWindowIcon(QIcon(":/design/design/windowicon.png"));
}

RankingsUI::~RankingsUI()
{
    delete this->uiUpdateTimer;
    delete this->ui;
}

void RankingsUI::uiUpdate()
{
    // Fill set of players.
    Player *playerSet[10];
    QString playerNamesSet[10] = {"Lesha", "Ivan", "Tosha", "Vasya", "Petya", "Andrey", "Misha", "Igor", "Sasha", this->gameInfo->playerName};
    int playerLevelSet[10] = {20,50,100,200,250,500,750,1000,1250,this->stats->CurrentLevel};
    int playerTapDmgSet[10] = {40,60,100,250,500,1000,1500,2500,5000,(int)this->stats->CurrentTapDamage};
    QTime *playerTimePlayedSet[10];
    for (int i = 0; i < 9; i++) {
        playerTimePlayedSet[i] = new QTime(i+2,i+20, rand()%20);
    }
    playerTimePlayedSet[9] = new QTime(stats->TotalPlayTime.hour(),
                                       stats->TotalPlayTime.minute(),
                                       stats->TotalPlayTime.second());
    for (int i = 0; i < 10; i++) {
        playerSet[i] = new Player(playerNamesSet[i],
                                  playerLevelSet[i],
                                  playerTapDmgSet[i],
                                  playerTimePlayedSet[i]
                                  );
    }
    // Sort set of players by level.
    this->BubbleSort(playerSet, 10);
    // Fill sorted info to labels.
    for (int i = 0; i < 10; i++)
    {
        QString idLblCurName = QString("id_lbl_%1").arg(i + 1);
        fillTextInLabelByItsName(idLblCurName, QString("Rank %1").arg(i + 1));
        QString nameLblCurName = QString("name_lbl_%1").arg(i + 1);
        fillTextInLabelByItsName(nameLblCurName, playerSet[i]->name);
        QString levelLblCurName = QString("level_lbl_%1").arg(i + 1);
        fillTextInLabelByItsName(levelLblCurName, QString::number(playerSet[i]->level));
        QString tapdmgLblCurName = QString("tapdmg_lbl_%1").arg(i + 1);
        fillTextInLabelByItsName(tapdmgLblCurName, QString::number(playerSet[i]->tapDmg));
        QString timePlLblCurName = QString("timePlayed_lbl_%1").arg(i + 1);
        fillTextInLabelByItsName(timePlLblCurName, playerSet[i]->timePlayed->toString("hh-mm")); //timePlayed_lbl_6
    }
}

void RankingsUI::BubbleSort(Player **playerSet, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (playerSet[j]->level < playerSet[j+1]->level)
            {
                // swap [j] and [j+1] players.
                Player *swap = playerSet[j];
                playerSet[j] = playerSet[j+1];
                playerSet[j + 1] = swap;
            }
        }
    }
}

void RankingsUI::fillTextInLabelByItsName(QString lblName, QString text)
{
    QLabel *labelObj = this->findChild<QLabel *>(lblName);
    labelObj->setText(text);
}
