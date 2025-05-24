#include "starting_screen.hh"
#include "ui_starting_screen.h"
#include <QMessageBox>

#include <QString>
#include <QTimer>
#include <QPixmap>
#include <iostream>

Starting_screen::Starting_screen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Starting_screen)
{
    ui->setupUi(this);
    this->setWindowTitle("Pirkanmaa Conquest - 2019");
    QPixmap pict(":/files/castle.png");
    QPixmap gametitlepicture(":/files/gametitle.png");
    QPixmap player1titlepicture(":/files/player_1_title.png");
    QPixmap player2titlepicture(":/files/player_2_title.png");

    ui->error_label->setVisible(false);

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    ui->logolbl->setPixmap(pict);
    ui->game_title_label->setPixmap(gametitlepicture);
    ui->player_1_title->setPixmap(player1titlepicture);
    ui->player_2_title->setPixmap(player2titlepicture);

    ui->error_label->setStyleSheet("color: #dbcc8f");



}


Starting_screen::~Starting_screen()
{
    delete ui;
}

void Starting_screen::on_pushButton_clicked()
{
    QString player_1_name = ui->lineEdit->text();
    QString player_2_name = ui->lineEdit_2->text();

    if (player_1_name.trimmed().isEmpty()){
        player_1_name = "Player 1";
    }
    if (player_2_name.trimmed().isEmpty()){
        player_2_name = "Player 2";
    }

    if (player_1_name.size() > 10 || player_2_name.size() > 10){
            ui->error_label->setVisible(true);
            QTimer::singleShot(7000, ui->error_label, &QLabel::hide);
    }
    else{
        emit this->sendValue(player_1_name, player_2_name);
        Starting_screen::close();
    }


}

void Starting_screen::on_help_btn_clicked()
{
    QMessageBox msgBox;
    msgBox.setStyleSheet("background-color: #550000; color: #e5bd1b;");
    msgBox.setWindowTitle("Help");
    msgBox.setText("Game rules can be found from an attached README - file!");
    msgBox.exec();

}

