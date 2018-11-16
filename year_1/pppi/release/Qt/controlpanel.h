#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QMainWindow>
#include <QSerialPort>
#include <QMediaPlayer>
#include <QDebug>

namespace Ui {
class ControlPanel;
}

class ControlPanel : public QMainWindow
{
    Q_OBJECT

public:
    explicit ControlPanel(QWidget *parent = 0);
    QSerialPort serial;
    const char *COM = "COM7";
    ~ControlPanel();

private slots:
    // Slots for buttons
    void on_systemOnButton_clicked();
    void on_switchL1_clicked();
    void on_switchL2_clicked();
    void on_switchL3_clicked();
    void on_switchL4_clicked();
    void on_switchL5_clicked();
    void on_switchL6_clicked();
    void on_switchL7_clicked();
    void on_switchL8_clicked();
    void on_changeClrL1_clicked();
    void on_changeClrL2_clicked();
    void on_changeClrL3_clicked();
    void on_changeClrL4_clicked();
    void on_changeClrL5_clicked();
    void on_changeClrL6_clicked();
    void on_changeClrL7_clicked();
    void on_changeClrL8_clicked();
    void on_changeBrght_Plus_clicked();
    void on_changeBrght_Minus_clicked();
    void on_colorsAllButton_clicked();
    void on_switchAllButton_clicked();
    void on_pingPongButton_clicked();
    void on_newYearButton_clicked();
    void on_chaserButton_clicked();
    void on_sorcererButton_clicked();

private:
    Ui::ControlPanel *ui;
    QMediaPlayer *player;
};

#endif // CONTROLPANEL_H
