#include <QDesktopWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QLabel>
#include <QtXml>
#include <QXmlStreamWriter>
#include <QDebug>
#include <QDir>
#include <QCursor>

#include "battlefieldui.h"
#include "ui_battlefieldui.h"

#define XML_FILE_PATH "settings.xml"

BattleFieldUI::BattleFieldUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BattleFieldUI)
{
    // Initialize class objects.
    this->achievements = new Achvments();
    this->army = new Army();
    this->stats = new Stats();
    this->heropowers = new HeroPowers();
    this->enemy = new Enemy(this->stats->CurrentLevel);
    this->gameInfo = new GameInfo("___ErrorName___");
    this->perksUi = new PerksUI(this->stats, this->enemy, this->heropowers, this);
    this->achvmentsUi = new AchvmentsUI(this->achievements, this);
    this->settingsUi = new SettingsUI(this->gameInfo, this->stats, this);
    this->rankingsUi = new RankingsUI(this->gameInfo, this->stats, this);

    // Upload info from .xml file.
    // Load the file.
    QDomDocument document;
    QFile file(XML_FILE_PATH);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Failed open file stream.";
        qDebug() << file.error();
        return;
    }
    else
    {
        if (!document.setContent(&file))
        {
            qDebug() << "Failed to load document.";
            return;
        }
        file.close();
    }
    // Get the root element.
    this->root = document.firstChildElement();
    // Fill all classes fields.
    this->loadSettingsFromXML();
    file.close();
    // Check if it was the first launch.
    if (this->gameInfo->firstLaunch == 0) {
        this->gameInfo->firstLaunch = 1;
        // TODO: go to "New Player UI" window.
    }

    // Main UI things.
    // Initialize UI objects.
    ui->setupUi(this);
    // Set exit prompt.
    this->setAttribute(Qt::WA_QuitOnClose);
    // Disable resizing a BattleField window.
    this->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    // Disable 'maximize' and 'hide' button in a BattleField window.
    setWindowFlags(Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
    // Move BattleField window to the center of screen.
    this->move((QApplication::desktop()->width() - this->size().width()) / 2,
               (QApplication::desktop()->height() - this->size().height()) / 2 - 50);

    // Update everything on the main window.
    emit this->uiUpdate();
    // Update window icon
    setWindowIcon(QIcon(":/design/design/windowicon.png"));

    // Set cursors
    QCursor cursorTarget = QCursor(QPixmap(":/cursors/design/cursors/cursorTarget.png"));
    this->ui->monster_btn->setCursor(cursorTarget);
    QCursor standartCursor = QCursor(QPixmap(":/cursors/design/cursors/cursorArrovRed.png"));
    this->setCursor(standartCursor);

    // "Battle field" tab.
    // Set monster button and first tab as default.
    ui->monster_btn->setDefault(true);
    ui->tabWidget->setCurrentIndex(0);
    // Initialize and start timer for army attack.
    this->armyAttackTimer = new QTimer(this);
    connect(armyAttackTimer, SIGNAL(timeout()), this, SLOT(armyAttack()));
    this->armyAttackTimer->start(1000);
    // Initialize and start timer for UI elements update.
    this->statsUIUpdateTimer = new QTimer(this);
    connect(statsUIUpdateTimer, SIGNAL(timeout()), this, SLOT(uiUpdate()));
    this->statsUIUpdateTimer->start(100);

    // "Hire army" tab.
    // Get text in labels and buttons from .csv file.
    for (int i = 0; i < SOLDIERS_AMOUNT; i++)
    {
        // Buttons.
        QString curBtnName = QString("soldier_btn_%1").arg(i + 1);
        QPushButton *curButton = this->ui->tabWidget->findChild<QPushButton *>(curBtnName);
        connect(curButton, SIGNAL(released()), this, SLOT(buySoldier()));
        curButton->setText("");
    }
    // Update DPS and Price labels.
    this->updateHireArmyUI();
}

void BattleFieldUI::armyAttack()
{
    // Do a damage.
    bool isKilled = this->enemy->doDamage(this->army->getArmyDamage());
    // Check if monster was killed.
    if(isKilled)
    {
        this->enemy->goToNextDragon(this->stats);
    }
}

void BattleFieldUI::on_monster_btn_clicked()
{
    // Do a damage. Possible, that it will be a critical damage.
    bool isKilled = this->enemy->doTapDamage(this->stats);
    // Check if monster was killed.
    if (isKilled)
    {
        this->enemy->goToNextDragon(this->stats);
    }
}

void BattleFieldUI::uiUpdate()
{
    // Update info in labels, according to general stats.
    this->ui->monsterHP_lbl->setText(QString("Monster HP: %1/%2")
                                     .arg(this->humanizeNumber(this->enemy->CurrentHP))
                                     .arg(this->humanizeNumber(this->enemy->TotalHP)));
    this->ui->armyDmg_lbl->setText(QString("Army damage: %1").arg(this->humanizeNumber(this->stats->CurrentArmyDamage)));
    this->ui->criticalChance_lbl->setText(QString("Critical chance: %1%").arg(this->stats->CurrentCriticalChance * 100));
    this->ui->dmndState_lbl->setText(QString("Diamonds: %1").arg(this->humanizeNumber(this->stats->CurrentDiamonds)));
    this->ui->goldState_lbl->setText(QString("Gold: %1").arg(this->humanizeNumber(this->stats->CurrentGold)));
    this->ui->tapDmg_lbl->setText(QString("Tap damage: %1").arg(this->humanizeNumber(this->stats->CurrentTapDamage)));
    this->ui->currentLevel_lbl->setText(QString("Level: %1").arg(this->stats->CurrentLevel));

    // Update Achievements class fields - check if achievements were unlocked.
    this->achievements->checkAchievements(this->stats);
    // Update total time played in GlobalState class.
    this->stats->TotalPlayTime = this->stats->TotalPlayTime.addMSecs(100);
    this->stats->checkDayPassed();

    // Update DPS and Price labels in HireArmy tab.
    this->updateHireArmyUI();

    // Update Artifacts levels.
    this->ui->goldArtLvl_lbl->setText(QString::number(this->stats->GoldMultiplier * 100) + QString("%"));
    this->ui->dmndsArtLvl_lbl->setText(QString::number(this->stats->DiamondsMultiplier * 100) + QString("%"));
    this->ui->critArtLvl_lbl->setText(QString::number(this->stats->CriticalHitMultiplier * 100) + QString("%"));
    this->ui->hpdecrArtLvl_lbl->setText(QString::number(this->stats->MonsterHPDecreaser * 100) + QString("%"));
    this->ui->perksArtLvl_lbl->setText(QString::number(this->stats->PerksCostDecreaser * 100) + QString("%"));
}

void BattleFieldUI::updateHireArmyUI()
{
    for (int i = 0; i < SOLDIERS_AMOUNT; i++)
    {
        // DPS labels.
        QString curDpsLblName = QString("soldier_dmg_lbl_%1").arg(i + 1);
        QLabel *curDpsLabel = this->ui->tabWidget->findChild<QLabel *>(curDpsLblName);
        long long curDPSToLbl = this->army->army[i].DPS * this->army->soldiersAmount[i];
        curDpsLabel->setText(this->humanizeNumber(curDPSToLbl) + QString(" DPS"));
        // Price labels.
        QString curPriceLblName = QString("soldier_price_lbl_%1").arg(i + 1);
        QLabel *curPriceLabel = this->ui->tabWidget->findChild<QLabel *>(curPriceLblName);
        long long curPrice = this->army->army[i].Price;
        curPriceLabel->setText(this->humanizeNumber(curPrice) + QString(" Gold"));
    }
}

QString BattleFieldUI::humanizeNumber(long long num)
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

void BattleFieldUI::buySoldier()
{
    // Get index of soldier, that player wants to buy.
    QPushButton *senderObj = (QPushButton *)QObject::sender();
    QString senderName = senderObj->objectName();
    QByteArray senderNameInBytes = senderName.toLatin1();
    char *senderNameInCharPtr = senderNameInBytes.data();
    int index = 0;
    sscanf(senderNameInCharPtr, "soldier_btn_%i", &index);
    index--;
    // Check if player has enough gold to hire specific soldier.
    if (this->stats->CurrentGold >= this->army->army[index].Price)
    {
        // Manipulation with soldiers amount.
        this->army->soldiersAmount[index]++;
        this->stats->ArmyAmount++;
        this->stats->CurrentArmyDamage += this->army->army[index].DPS;
        // Payment for the hire.
        this->stats->CurrentGold -= this->army->army[index].Price;
        // Increase army hiring price.
        this->army->army[index].Price *= 1.15;
    }
}

void BattleFieldUI::closeEvent(QCloseEvent *e)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Quit program?", tr("Save progress and exit battle field?\n"),
                                                               QMessageBox::Cancel | QMessageBox::Yes, QMessageBox::Yes);
    if(resBtn != QMessageBox::Yes)
    {
        e->ignore();
    }
    else
    {
        this->writeSettingsToXML();
        e->accept();
    }
}

void BattleFieldUI::on_settings_btn_clicked()
{
    // Open a window, if it is not opened yet.
    if (!this->settingsUi->isVisible())
    {
        this->settingsUi->show();
    }
    // If window is already open - change focus.
    this->settingsUi->activateWindow();
}

void BattleFieldUI::on_perks_btn_clicked()
{
    // Open a window, if it is not opened yet.
    if (!this->perksUi->isVisible())
    {
        this->perksUi->show();
    }
    // If window is already open - change focus.
    this->perksUi->activateWindow();
}

void BattleFieldUI::on_achvments_btn_clicked()
{
    // Open a window, if it is not opened yet.
    if (!this->achvmentsUi->isVisible())
    {
        this->achvmentsUi->show();
    }
    // If window is already open - change focus.
    this->achvmentsUi->activateWindow();
}

void BattleFieldUI::on_ranking_btn_clicked()
{
    // Open a window, if it is not opened yet.
    if (!this->rankingsUi->isVisible())
    {
        this->rankingsUi->show();
    }
    // If window is already open - change focus.
    this->rankingsUi->activateWindow();
}

void BattleFieldUI::on_tapDmg_btn_clicked()
{
    if(this->stats->CurrentGold >= TAPDMG_UPGRADE_COST) {
        this->stats->CurrentTapDamage += TAPDMG_UPGRADE_VALUE;
        this->stats->CurrentGold -= TAPDMG_UPGRADE_COST;
    }
}

void BattleFieldUI::on_anduinMagic_btn_clicked()
{
    // Use ability, if cooldown equals to true.
    if(this->heropowers->anduinCD) {
        this->stats->CurrentTapDamage *= ANDUIN_UPGRADE_VALUE;
        this->heropowers->anduinCD = false;
        this->heropowers->anduinTimer->start(ANDUIN_DURATION_MS);
        connect(heropowers->anduinTimer, SIGNAL(timeout()), this, SLOT(returnPrevSettings_anduin()));
    }
    // Check if ability was bought.
    if(this->stats->CurrentGold >= ANDUIN_UPGRADE_COST && !heropowers->anduinBought) {
        this->heropowers->anduinCD = true;
        this->heropowers->anduinBought = true;
        this->stats->HeropowersUnlocked++;
        this->stats->CurrentGold -= ANDUIN_UPGRADE_COST;
    }
}
void BattleFieldUI::returnPrevSettings_anduin()
{
    this->heropowers->anduinTimer->stop();
    disconnect(heropowers->anduinTimer, SIGNAL(timeout()), this, SLOT(returnPrevSettings_anduin()));
    this->stats->CurrentTapDamage /= ANDUIN_UPGRADE_VALUE;
    this->heropowers->anduinCD = true;
}

void BattleFieldUI::on_sylvanasCritical_btn_clicked()
{
    if(this->heropowers->sylvanasCD) {
        this->stats->CurrentCriticalChance += SYLVANAS_UPGRADE_VALUE;
        this->heropowers->sylvanasCD = false;
        this->heropowers->sylvanasTimer->start(SYLVANA_DURATION_MS);
        connect(heropowers->sylvanasTimer, SIGNAL(timeout()), this, SLOT(returnPrevSettings_sylvana()));
    }
    if(this->stats->CurrentGold >= SYLVANAS_UPGRADE_COST && !heropowers->sylvanasBought) {
        this->heropowers->sylvanasCD = true;
        this->heropowers->sylvanasBought = true;
        this->stats->HeropowersUnlocked++;
        this->stats->CurrentGold -= SYLVANAS_UPGRADE_COST;
    }
}
void BattleFieldUI::returnPrevSettings_sylvana()
{
    this->heropowers->sylvanasTimer->stop();
    disconnect(heropowers->sylvanasTimer, SIGNAL(timeout()), this, SLOT(returnPrevSettings_sylvana()));
    this->stats->CurrentCriticalChance -= SYLVANAS_UPGRADE_VALUE;
    this->heropowers->sylvanasCD = true;
}

void BattleFieldUI::on_guldanRampage_btn_clicked()
{
    if(this->heropowers->guldanCD) {
        this->stats->CurrentArmyDamage += GULDAN_UPGRADE_VALUE;
        this->heropowers->guldanCD = false;
        this->heropowers->guldanTimer->start(GULDAN_DURATION_MS);
        connect(heropowers->guldanTimer, SIGNAL(timeout()), this, SLOT(returnPrevSettings_guldan()));
    }
    if(this->stats->CurrentGold >= GULDAN_UPGRADE_COST && !heropowers->guldanBought) {
        this->heropowers->guldanCD = true;
        this->heropowers->guldanBought = true;
        this->stats->HeropowersUnlocked++;
        this->stats->CurrentGold -= GULDAN_UPGRADE_COST;
    }
}
void BattleFieldUI::returnPrevSettings_guldan()
{
    this->heropowers->guldanTimer->stop();
    disconnect(heropowers->guldanTimer, SIGNAL(timeout()), this, SLOT(returnPrevSettings_guldan()));
    this->stats->CurrentArmyDamage -= GULDAN_UPGRADE_VALUE;
    this->heropowers->guldanCD = true;
}

void BattleFieldUI::on_artasUnity_btn_clicked()
{
    if(this->heropowers->artasCD) {
        this->stats->CurrentTapDamage += ARTAS_UPGRADE_VALUE;
        this->heropowers->artasCD = false;
        this->heropowers->artasTimer->start(ARTAS_DURATION_MS);
        connect(heropowers->artasTimer, SIGNAL(timeout()), this, SLOT(returnPrevSettings_artas()));
    }

    if(this->stats->CurrentGold >= ARTAS_UPGRADE_COST && !heropowers->artasBought) {
        this->heropowers->artasCD = true;
        this->heropowers->artasBought = true;
        this->stats->HeropowersUnlocked++;
        this->stats->CurrentGold -= ARTAS_UPGRADE_COST;
    }
}
void BattleFieldUI::returnPrevSettings_artas()
{
    this->heropowers->artasTimer->stop();
    disconnect(heropowers->artasTimer, SIGNAL(timeout()), this, SLOT(returnPrevSettings_artas()));
    this->stats->CurrentTapDamage -= ARTAS_UPGRADE_VALUE;
    this->heropowers->artasCD = true;
}

void BattleFieldUI::on_goldArt_btn_clicked()
{
    if (this->stats->CurrentDiamonds >= MULTIPLIER_COST)
    {
        if (this->stats->GoldMultiplier >= 0.8) {
            this->stats->GoldMultiplier = 0.9;
            this->ui->goldArt_btn->setEnabled(false);
            return;
        }
        // Pay for buying artifact.
        this->stats->CurrentDiamonds -= MULTIPLIER_COST;
        // Get artifact effect.
        this->stats->GoldMultiplier += 0.1;
        //
        this->stats->ArtifactsUnlocked++;
    }
}

void BattleFieldUI::on_dmndsArt_btn_clicked()
{
    if (this->stats->CurrentDiamonds >= MULTIPLIER_COST)
    {
        if (this->stats->DiamondsMultiplier >= 0.8) {
            this->stats->DiamondsMultiplier = 0.9;
            this->ui->dmndsArt_btn->setEnabled(false);
            return;
        }
        // Pay for buying artifact.
        this->stats->CurrentDiamonds -= MULTIPLIER_COST;
        // Get artifact effect.
        this->stats->DiamondsMultiplier += 0.1;
        //
        this->stats->ArtifactsUnlocked++;
    }
}

void BattleFieldUI::on_critArt_btn_clicked()
{
    if (this->stats->CurrentDiamonds >= MULTIPLIER_COST)
    {
        if (this->stats->CriticalHitMultiplier >= 0.5) {
            this->stats->CriticalHitMultiplier = 0.6;
            this->ui->critArt_btn->setEnabled(false);
            return;
        }
        // Pay for buying artifact.
        this->stats->CurrentDiamonds -= MULTIPLIER_COST;
        // Get artifact effect.
        this->stats->CriticalHitMultiplier += 0.1;
        //
        this->stats->ArtifactsUnlocked++;
    }
}

void BattleFieldUI::on_hpdecrArt_btn_clicked()
{
    if (this->stats->CurrentDiamonds >= MULTIPLIER_COST)
    {
        if (this->stats->MonsterHPDecreaser >= 0.8) {
            this->stats->MonsterHPDecreaser = 0.9;
            this->ui->hpdecrArt_btn->setEnabled(false);
            return;
        }
        // Pay for buying artifact.
        this->stats->CurrentDiamonds -= MULTIPLIER_COST;
        // Get artifact effect.
        this->stats->MonsterHPDecreaser += 0.1;
        //
        this->stats->ArtifactsUnlocked++;
    }
}

void BattleFieldUI::on_perksArt_btn_clicked()
{
    if (this->stats->CurrentDiamonds >= MULTIPLIER_COST)
    {
        if (this->stats->PerksCostDecreaser >= 0.8) {
            this->stats->PerksCostDecreaser = 0.9;
            this->ui->perksArt_btn->setEnabled(false);
            return;
        }
        // Pay for buying artifact.
        this->stats->CurrentDiamonds -= MULTIPLIER_COST;
        // Get artifact effect.
        this->stats->PerksCostDecreaser += 0.1;
        //
        this->stats->ArtifactsUnlocked++;
    }
}

QString BattleFieldUI::listElements(QString tagName1, QString tagName2)
{
    QDomNodeList items = this->root.elementsByTagName(tagName1);
    QDomNodeList items2 = items.at(0).childNodes();
    for (int i = 0; i < items2.count(); i++)
    {
        QDomNode curNode = items2.at(i).toElement();
        if (!QString::compare(curNode.nodeName(), tagName2))
        {
            QDomElement curElem = curNode.toElement();
            return (curElem.text());
        }
    }
    qDebug() << "ACHTUNG! ERROR in listElements (error with parsing xml file)";
    return (QString("notFound"));
}

void BattleFieldUI::loadSettingsFromXML()
{
    // GameInfo settings class.
    gameInfo->firstLaunch = listElements("gameinfo", "firstLaunch").toInt();
    gameInfo->playerName = listElements("gameinfo", "username");
    gameInfo->positionInRank = listElements("gameinfo", "rank").toInt();
    // Achievements settings class.
    achievements->EarnNGold = listElements("achievements", "earnNGold").toInt();
    achievements->EarnNDiamonds = listElements("achievements", "earnNDiamonds").toInt();
    achievements->KillNMonsters = listElements("achievements", "killNMonsters").toInt();
    achievements->ReachNStage = listElements("achievements", "reachNStage").toInt();
    achievements->OwnNArtifacts = listElements("achievements", "ownNArtifacts").toInt();
    achievements->HireNSoldiers = listElements("achievements", "hireNSoldiers").toInt();
    achievements->TapNTimes = listElements("achievements", "tapNTimes").toInt();
    achievements->HeropowNTimes = listElements("achievements", "heropowNTimes").toInt();
    achievements->DoNCritical = listElements("achievements", "doNCritical").toInt();
    // Army class.
    for (int i = 1; i < 11; i++)
    {
        QString query = QString("type%1").arg(i);
        army->soldiersAmount[i - 1] = listElements("army", query).toInt();
    }
    // Stats class.
    stats->CurrentLevel = listElements("stats", "currentLevel").toInt();
    stats->CurrentGold = listElements("stats", "currentGold").toInt();
    stats->CurrentDiamonds = listElements("stats", "currentDiamonds").toInt();
    stats->CurrentTapDamage = listElements("stats", "currentTapDamage").toInt();
    stats->CurrentArmyDamage = listElements("stats", "currentArmyDamage").toInt();
    stats->CurrentCriticalChance = listElements("stats", "currentCriticalChance").toDouble();
    stats->ArmyAmount = listElements("stats", "armyAmount").toInt();
    stats->ArtifactsUnlocked = listElements("stats", "artifactsUnlocked").toInt();
    stats->HeropowersUnlocked = listElements("stats", "heropowersUnlocked").toInt();
    stats->AwardsCollected = listElements("stats", "awardsCollected").toInt();
    stats->TotalGoldCollected = listElements("stats", "totalGoldCollected").toInt();
    stats->TotalDiamondsCollected = listElements("stats", "totalDiamondsCollected").toInt();
    stats->TotalTapsMade = listElements("stats", "totalTapsMade").toInt();
    stats->TotalCriticalTapsMade = listElements("stats", "totalCriticalTapsMade").toInt();
    stats->TotalMonsterKills = listElements("stats", "totalMonsterKills").toInt();
    int h = listElements("stats", "totalPlayTimeH").toInt();
    int m = listElements("stats", "totalPlayTimeM").toInt();
    int s = listElements("stats", "totalPlayTimeS").toInt();
    stats->TotalPlayTime.setHMS(h, m, s);
    stats->TotalDaysPlayed = listElements("stats", "totalDaysPlayed").toDouble();
    stats->GoldMultiplier = listElements("stats", "goldMultiplier").toDouble();
    stats->CriticalHitMultiplier = listElements("stats", "criticalHitMultiplier").toDouble();
    stats->DiamondsMultiplier = listElements("stats", "diamondsMultiplier").toDouble();
    stats->MonsterHPDecreaser = listElements("stats", "monsterHPDecreaser").toDouble();
    stats->PerksCostDecreaser = listElements("stats", "perksCostDecreaser").toDouble();
    // Heropowers class.
    heropowers->anduinBought = listElements("heropowers", "anduinBought").toInt();
    heropowers->sylvanasBought = listElements("heropowers", "sylvanasBought").toInt();
    heropowers->guldanBought = listElements("heropowers", "guldanBought").toInt();
    heropowers->artasBought = listElements("heropowers", "artasBought").toInt();
    // Enemy class.
    enemy->CurrentHP = listElements("enemy", "currentHP").toInt();
    enemy->GoldDropped = listElements("enemy", "goldDropped").toInt();
    enemy->DiamondsDropped = listElements("enemy", "diamondsDropped").toInt();
    enemy->TotalHP = listElements("enemy", "totalHP").toInt();
}

void BattleFieldUI::writeSettingsToXML()
{
    QFile file(XML_FILE_PATH);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Failed open file stream";
        qDebug() << file.error();
        return;
    }
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    // Start writing to .xml file.
    xmlWriter.writeStartElement("settings");
    // Gameinfo section.
    xmlWriter.writeStartElement("gameinfo");
    xmlWriter.writeTextElement("firstLaunch", QString::number(gameInfo->firstLaunch));
    xmlWriter.writeTextElement("username", gameInfo->playerName);
    xmlWriter.writeTextElement("rank", QString::number(gameInfo->positionInRank));
    xmlWriter.writeEndElement();
    // Achievements section.
    xmlWriter.writeStartElement("achievements");
    xmlWriter.writeTextElement("earnNGold", QString::number(achievements->EarnNGold));
    xmlWriter.writeTextElement("earnNDiamonds", QString::number(achievements->EarnNDiamonds));
    xmlWriter.writeTextElement("killNMonsters", QString::number(achievements->KillNMonsters));
    xmlWriter.writeTextElement("reachNStage", QString::number(achievements->ReachNStage));
    xmlWriter.writeTextElement("ownNArtifacts", QString::number(achievements->OwnNArtifacts));
    xmlWriter.writeTextElement("hireNSoldiers", QString::number(achievements->HireNSoldiers));
    xmlWriter.writeTextElement("tapNTimes", QString::number(achievements->TapNTimes));
    xmlWriter.writeTextElement("heropowNTimes", QString::number(achievements->HeropowNTimes));
    xmlWriter.writeTextElement("doNCritical", QString::number(achievements->DoNCritical));
    xmlWriter.writeEndElement();
    // Army section.
    xmlWriter.writeStartElement("army");
    for (int i = 1; i < 11; i++)
    {
        QString query = QString("type%1").arg(i);
        xmlWriter.writeTextElement(query, QString::number(army->soldiersAmount[i - 1]));
    }
    xmlWriter.writeEndElement();
    // Stats section.
    xmlWriter.writeStartElement("stats");
    xmlWriter.writeTextElement("currentLevel", QString::number(stats->CurrentLevel));
    xmlWriter.writeTextElement("currentGold", QString::number(stats->CurrentGold));
    xmlWriter.writeTextElement("currentDiamonds", QString::number(stats->CurrentDiamonds));
    xmlWriter.writeTextElement("currentTapDamage", QString::number(stats->CurrentTapDamage));
    xmlWriter.writeTextElement("currentArmyDamage", QString::number(stats->CurrentArmyDamage));
    xmlWriter.writeTextElement("currentCriticalChance", QString::number(stats->CurrentCriticalChance));
    xmlWriter.writeTextElement("armyAmount", QString::number(stats->ArmyAmount));
    xmlWriter.writeTextElement("artifactsUnlocked", QString::number(stats->ArtifactsUnlocked));
    xmlWriter.writeTextElement("heropowersUnlocked", QString::number(stats->HeropowersUnlocked));
    xmlWriter.writeTextElement("awardsCollected", QString::number(stats->AwardsCollected));
    xmlWriter.writeTextElement("totalGoldCollected", QString::number(stats->TotalGoldCollected));
    xmlWriter.writeTextElement("totalDiamondsCollected", QString::number(stats->TotalDiamondsCollected));
    xmlWriter.writeTextElement("totalTapsMade", QString::number(stats->TotalTapsMade));
    xmlWriter.writeTextElement("totalCriticalTapsMade", QString::number(stats->TotalCriticalTapsMade));
    xmlWriter.writeTextElement("totalMonsterKills", QString::number(stats->TotalMonsterKills));
    xmlWriter.writeTextElement("totalPlayTimeH", QString::number(stats->TotalPlayTime.hour()));
    xmlWriter.writeTextElement("totalPlayTimeM", QString::number(stats->TotalPlayTime.minute()));
    xmlWriter.writeTextElement("totalPlayTimeS", QString::number(stats->TotalPlayTime.second()));
    xmlWriter.writeTextElement("totalDaysPlayed", QString::number(stats->TotalDaysPlayed));
    xmlWriter.writeTextElement("goldMultiplier", QString::number(stats->GoldMultiplier));
    xmlWriter.writeTextElement("criticalHitMultiplier", QString::number(stats->CriticalHitMultiplier));
    xmlWriter.writeTextElement("diamondsMultiplier", QString::number(stats->DiamondsMultiplier));
    xmlWriter.writeTextElement("monsterHPDecreaser", QString::number(stats->MonsterHPDecreaser));
    xmlWriter.writeTextElement("perksCostDecreaser", QString::number(stats->PerksCostDecreaser));
    xmlWriter.writeEndElement();
    // Heropowers section.
    xmlWriter.writeStartElement("heropowers");
    xmlWriter.writeTextElement("anduinBought", QString::number(heropowers->anduinBought));
    xmlWriter.writeTextElement("sylvanasBought", QString::number(heropowers->sylvanasBought));
    xmlWriter.writeTextElement("guldanBought", QString::number(heropowers->guldanBought));
    xmlWriter.writeTextElement("artasBought", QString::number(heropowers->artasBought));
    xmlWriter.writeEndElement();
    // Enemy section.
    xmlWriter.writeStartElement("enemy");
    xmlWriter.writeTextElement("currentHP", QString::number(enemy->CurrentHP));
    xmlWriter.writeTextElement("goldDropped", QString::number(enemy->GoldDropped));
    xmlWriter.writeTextElement("diamondsDropped", QString::number(enemy->DiamondsDropped));
    xmlWriter.writeTextElement("totalHP", QString::number(enemy->TotalHP));
    xmlWriter.writeEndElement();
    // End of the .xml file.
    xmlWriter.writeEndElement();
    file.close();
}
