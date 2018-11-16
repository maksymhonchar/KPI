#include <QUrl>
#include <QDesktopServices>

#include "settingsui.h"
#include "ui_settingsui.h"

#include "battlefieldui.h"

SettingsUI::SettingsUI(GameInfo *gameInfo, Stats *stats, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsUI)
{
    // Initialize Settings Dialog UI.
    ui->setupUi(this);

    // Disable 'help' button.
    Qt::WindowFlags flags = this->windowFlags();
    flags &= ~Qt::WindowContextHelpButtonHint;
    this->setWindowFlags(flags);

    // Set first tab as default.
    ui->settingsTabs_tabWidget->setCurrentIndex(0);

    this->stats = stats;
    this->gameInfo = gameInfo;

    this->updateUITimer = new QTimer(this);
    connect(updateUITimer, SIGNAL(timeout()), this, SLOT(updateUI()));
    this->updateUITimer->start(100);

    setWindowIcon(QIcon(":/design/design/windowicon.png"));
}

SettingsUI::~SettingsUI()
{
    delete ui;
    delete this->updateUITimer;
}

void SettingsUI::updateUI()
{
    this->ui->val_lbl_1->setText(humanizeNumber(this->stats->CurrentLevel));
    this->ui->val_lbl_2->setText(humanizeNumber(this->stats->CurrentGold));
    this->ui->val_lbl_3->setText(humanizeNumber(this->stats->ArmyAmount));
    this->ui->val_lbl_4->setText(humanizeNumber(this->stats->ArtifactsUnlocked));
    this->ui->val_lbl_5->setText(humanizeNumber(this->stats->HeropowersUnlocked));
    this->ui->val_lbl_6->setText(humanizeNumber(this->stats->AwardsCollected));
    this->ui->val_lbl_7->setText(humanizeNumber(this->stats->CurrentTapDamage));
    this->ui->val_lbl_8->setText(humanizeNumber(this->stats->CurrentCriticalChance));
    this->ui->val_lbl_9->setText(humanizeNumber(this->stats->CurrentArmyDamage));
    this->ui->val_lbl_10->setText(humanizeNumber(this->stats->MonsterHPDecreaser));
    this->ui->val_lbl_11->setText(humanizeNumber(this->stats->CriticalHitMultiplier));
    this->ui->val_lbl_12->setText(humanizeNumber(this->stats->GoldMultiplier));
    this->ui->val_lbl_13->setText(humanizeNumber(this->stats->TotalGoldCollected));
    this->ui->val_lbl_14->setText(humanizeNumber(this->stats->TotalTapsMade));
    this->ui->val_lbl_15->setText(humanizeNumber(this->stats->TotalCriticalTapsMade));
    this->ui->val_lbl_16->setText(humanizeNumber(this->stats->TotalMonsterKills));
    this->ui->val_lbl_17->setText(QString("%1d %2").arg(this->stats->TotalDaysPlayed).arg(this->stats->TotalPlayTime.toString("hh-mm-ss")));
    this->ui->val_lbl_18->setText(QString::number(this->gameInfo->positionInRank));
}

void SettingsUI::on_save_btn_clicked()
{
    BattleFieldUI *bfObj = (BattleFieldUI *)this->parent();
    bfObj->writeSettingsToXML();
}

void SettingsUI::on_vkshare_btn_clicked()
{
    QDesktopServices::openUrl(QUrl("http://vk.com/id0", QUrl::TolerantMode));
}

void SettingsUI::on_fbshare_btn_clicked()
{
    QDesktopServices::openUrl(QUrl("http://www.facebook.com/profile.php?=743264506", QUrl::TolerantMode));
}

void SettingsUI::on_twishare_btn_clicked()
{
    QDesktopServices::openUrl(QUrl("http://twitter.com", QUrl::TolerantMode));
}

QString SettingsUI::humanizeNumber(long long num)
{
    QString toRet = "";
    if (num < 1000)
        toRet = QString::number((double)num);
    else if (num >= 1000000000)
        toRet = QString::number((double)num/1000000000) + "G";
    else if (num >= 1000000)
        toRet = QString::number((double)num/1000000) + "M";
    else if (num >= 1000)
        toRet = QString::number((double)num/1000) + "K";
    return (toRet);
}

