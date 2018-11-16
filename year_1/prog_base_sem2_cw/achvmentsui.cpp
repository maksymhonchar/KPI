#include "achvmentsui.h"
#include "ui_achvmentsui.h"

AchvmentsUI::AchvmentsUI(Achvments *achvments, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AchvmentsUI)
{
    // Initialize Achvments Dialog UI.
    ui->setupUi(this);

    // Disable 'help' button.
    Qt::WindowFlags flags = this->windowFlags();
    flags &= ~Qt::WindowContextHelpButtonHint;
    this->setWindowFlags(flags);
    // Disable resizing window.
    this->setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    this->achvments = achvments;

    // Each 100ms check if some achievement was reached.
    this->updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateUI()));
    this->updateTimer->start(100);

    setWindowIcon(QIcon(":/design/design/windowicon.png"));
}

AchvmentsUI::~AchvmentsUI()
{
    delete this->updateTimer;
    delete this->ui;
}

void AchvmentsUI::updateUI()
{
    if(this->achvments->EarnNGold)
        ui->ach1_status_1->setStyleSheet("background-image: url(:/design/achievementDone_label.png)");
    if(this->achvments->EarnNDiamonds)
        ui->ach2_status_2->setStyleSheet("background-image: url(:/design/achievementDone_label.png)");
    if(this->achvments->KillNMonsters)
        ui->ach3_status_3->setStyleSheet("background-image: url(:/design/achievementDone_label.png)");
    if(this->achvments->ReachNStage)
        ui->ach4_status_4->setStyleSheet("background-image: url(:/design/achievementDone_label.png)");
    if(this->achvments->OwnNArtifacts)
        ui->ach5_status_5->setStyleSheet("background-image: url(:/design/achievementDone_label.png)");
    if(this->achvments->HireNSoldiers)
        ui->ach6_status_6->setStyleSheet("background-image: url(:/design/achievementDone_label.png)");
    if(this->achvments->TapNTimes)
        ui->ach7_status_7->setStyleSheet("background-image: url(:/design/achievementDone_label.png)");
    if(this->achvments->HeropowNTimes)
        ui->ach8_status_8->setStyleSheet("background-image: url(:/design/achievementDone_label.png)");
    if(this->achvments->DoNCritical)
        ui->ach9_status_9->setStyleSheet("background-image: url(:/design/achievementDone_label.png)");
}

