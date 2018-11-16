#include "controlpanel.h"
#include "ui_controlpanel.h"

#include <QSerialPort>
#include <QMediaPlayer>
#include <QDebug>

ControlPanel::ControlPanel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ControlPanel)
{
    ui->setupUi(this);

    // Settings for main window.
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    // Settings for COM port.
    serial.setPortName(this->COM);
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    // Multimedia
    player = new QMediaPlayer(this);
}

ControlPanel::~ControlPanel()
{
    delete ui;
    serial.close();
}

void ControlPanel::on_systemOnButton_clicked()
{
    serial.open(QIODevice::ReadWrite);
    ui->statusLabel->setText(QString("Port opened to %1.").arg(this->COM));
}

void ControlPanel::on_switchL1_clicked()
{
    serial.write("1*");
    ui->statusLabel->setText("Lamp 1 is turned on.");
}

void ControlPanel::on_switchL2_clicked()
{
    serial.write("2*");
    ui->statusLabel->setText("Lamp 2 is turned on.");
}

void ControlPanel::on_switchL3_clicked()
{
    serial.write("3*");
    ui->statusLabel->setText("Lamp 3 is turned on.");
}

void ControlPanel::on_switchL4_clicked()
{
    serial.write("4*");
    ui->statusLabel->setText("Lamp 4 is turned on.");
}

void ControlPanel::on_switchL5_clicked()
{
    serial.write("5*");
    ui->statusLabel->setText("Lamp 5 is turned on.");
}

void ControlPanel::on_switchL6_clicked()
{
    serial.write("6*");
    ui->statusLabel->setText("Lamp 6 is turned on.");
}

void ControlPanel::on_switchL7_clicked()
{
    serial.write("7*");
    ui->statusLabel->setText("Lamp 7 is turned on.");
}

void ControlPanel::on_switchL8_clicked()
{
    serial.write("8*");
    ui->statusLabel->setText("Lamp 8 is turned on.");
}

void ControlPanel::on_changeClrL1_clicked()
{
    serial.write("q*");
    ui->statusLabel->setText("Lamp 1 changed his color.");
}

void ControlPanel::on_changeClrL2_clicked()
{
    serial.write("w*");
    ui->statusLabel->setText("Lamp 2 changed his color.");
}

void ControlPanel::on_changeClrL3_clicked()
{
    serial.write("e*");
    ui->statusLabel->setText("Lamp 3 changed his color.");
}

void ControlPanel::on_changeClrL4_clicked()
{
    serial.write("r*");
    ui->statusLabel->setText("Lamp 4 changed his color.");
}

void ControlPanel::on_changeClrL5_clicked()
{
    serial.write("t*");
    ui->statusLabel->setText("Lamp 5 changed his color.");
}

void ControlPanel::on_changeClrL6_clicked()
{
    serial.write("y*");
    ui->statusLabel->setText("Lamp 6 changed his color.");
}

void ControlPanel::on_changeClrL7_clicked()
{
    serial.write("u*");
    ui->statusLabel->setText("Lamp 7 changed his color.");
}

void ControlPanel::on_changeClrL8_clicked()
{
    serial.write("i*");
    ui->statusLabel->setText("Lamp 8 changed his color.");
}

void ControlPanel::on_changeBrght_Plus_clicked()
{
    serial.write("+*");
    ui->statusLabel->setText("Brightness for all lamps increased.");
}

void ControlPanel::on_changeBrght_Minus_clicked()
{
    serial.write("-*");
    ui->statusLabel->setText("Brightness for all lamps decreased.");
}


void ControlPanel::on_colorsAllButton_clicked()
{
    serial.write("a*");
    ui->statusLabel->setText("All colors changed.");
}

void ControlPanel::on_switchAllButton_clicked()
{
    serial.write("s*");
    ui->statusLabel->setText("All lamps are switched.");
}

void ControlPanel::on_pingPongButton_clicked()
{
    serial.write("zz*");
    ui->statusLabel->setText("Ping pong animation!");
}

void ControlPanel::on_newYearButton_clicked()
{
    serial.write("zx*");
    ui->statusLabel->setText("New year animation!");
}


void ControlPanel::on_chaserButton_clicked()
{
    serial.write("zc*");
    ui->statusLabel->setText("Chaser animation!");
}

void ControlPanel::on_sorcererButton_clicked()
{
    QString temp = "Song was turned on.\n";
    // Load the file
    player->setMedia(QUrl::fromLocalFile("C:/Users/maxgo/Desktop/sorcerer.mp3"));
    player->play();
    ui->statusLabel->setText(player->errorString());

    temp.append("X-Ray Dog - Sorcerer (remix) animation!");
    serial.write("zv*");
    ui->statusLabel->setText(temp);
}
