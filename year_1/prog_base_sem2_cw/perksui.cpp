#include "perksui.h"
#include "ui_perksui.h"

// What perks do.
#define ELDORADO_VALUE 100000
#define DIAMRUSH_VALUE 100
#define ENCHSWORD_VALUE 20000

// Perks cost.
#define DIAMRUSH_COST 50000
#define ELDORADO_COST 10
#define ENCHSWORD_COST 10000
#define WINDFURY_COST 10000
#define PASSLVL_COST 10000

PerksUI::PerksUI(Stats *stats, Enemy *enemy, HeroPowers *heropowers, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PerksUI)
{
    // Initialize Perks Dialog UI.
    ui->setupUi(this);

    // Disable 'help' button.
    Qt::WindowFlags flags = this->windowFlags();
    flags &= ~Qt::WindowContextHelpButtonHint;
    this->setWindowFlags(flags);
    // Disable resizing window.
    this->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    // Copy general data from other classes.
    this->enemy = enemy;
    this->stats = stats;
    this->heropowers = heropowers;

    setWindowIcon(QIcon(":/design/design/windowicon.png"));

    this->timerUpdate = new QTimer(this);

}

PerksUI::~PerksUI()
{
    delete this->ui;
}

void PerksUI::on_perksPassLvl_btn_clicked()
{
    int perkActualCost = PASSLVL_COST - this->stats->PerksCostDecreaser*PASSLVL_COST;
    // check if player has enough diamonds
    if (this->stats->CurrentDiamonds >= perkActualCost )
    {
        this->enemy->goToNextDragon(this->stats);
        this->stats->CurrentDiamonds -= perkActualCost ;
    }
}

void PerksUI::on_perksDmndRush_btn_clicked()
{
    int perkActualCost = DIAMRUSH_COST - this->stats->PerksCostDecreaser*DIAMRUSH_COST;
    if (this->stats->CurrentGold >= perkActualCost)
    {
        this->stats->CurrentDiamonds += DIAMRUSH_VALUE;
        this->stats->TotalDiamondsCollected += DIAMRUSH_VALUE;
        this->stats->CurrentGold -= perkActualCost;
    }
}

void PerksUI::on_perksEnchantedSwrd_btn_clicked()
{
    int perkActualCost = ENCHSWORD_COST - this->stats->PerksCostDecreaser*ENCHSWORD_COST;
    bool isKilled = false;
    if (this->stats->CurrentDiamonds >= perkActualCost) {
        isKilled = this->enemy->doDamage(ENCHSWORD_VALUE);
        this->stats->CurrentDiamonds -= perkActualCost;
    }
    if (isKilled)
    {
        this->enemy->goToNextDragon(this->stats);
    }
}

void PerksUI::on_perksEldoradoBtn_clicked()
{
    int perkActualCost = ELDORADO_COST - this->stats->PerksCostDecreaser*ELDORADO_COST;
    if (this->stats->CurrentDiamonds >= perkActualCost)
    {
        this->stats->CurrentGold += ELDORADO_VALUE;
        this->stats->TotalGoldCollected += ELDORADO_VALUE;
        this->stats->CurrentDiamonds -= perkActualCost;
    }
}

void PerksUI::on_perksWindfury_btn_clicked()
{
    int perkActualCost = WINDFURY_COST - this->stats->PerksCostDecreaser*WINDFURY_COST;
    if (this->stats->CurrentDiamonds >= perkActualCost) {
        this->heropowers->refreshCD();
        this->stats->CurrentDiamonds -= perkActualCost;
    }
}
