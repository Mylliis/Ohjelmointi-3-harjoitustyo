#include "popup_dialog.hh"
#include "ui_popup_dialog.h"
#include <string>
#include <iostream>
#include <QDebug>
#include <QTimer>

#include "mapitem.hh"
#include "gamescene.hh"
#include "student_resourcemaps.h"

popup_dialog::popup_dialog(std::shared_ptr<Student::tilebase_s> tile,
                           std::shared_ptr<Student::Player> player,
                           bool is_berrybush, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::popup_dialog),
    tile(tile),
    player_(player),
    is_tile_berrybush(is_berrybush)
{

    // Interface modifications
    ui->setupUi(this);
    this->setWindowTitle("Activity");
    ui->label_2->setStyleSheet("color: #f0c61e");
    ui->reward_label->setStyleSheet("color: #f0c61e");
    ui->notice_label->setStyleSheet("color: #f0c61e");
    ui->notice_label_2->setStyleSheet("color: #f0c61e");

    // Hide the error label
    ui->label->setVisible(false);

    // Set the interface labels according to the mouse click event
    setPopupTexts();


}

popup_dialog::~popup_dialog()
{
    delete ui;
}

void popup_dialog::hideTexts(){

    ui->worker_resource_1->setVisible(false);
    ui->worker_resource_2->setVisible(false);

    ui->miner_resource_1->setVisible(false);
    ui->miner_resource_2->setVisible(false);

    ui->pushButton_1->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->pushButton_3->setVisible(false);

    ui->hq_resource_1->setVisible(false);
    ui->hq_resource_2->setVisible(false);

    ui->line->setVisible(false);
}

void popup_dialog::setPopupTexts(){

    // This is initialized only if player clicked one of these:
    // HQ, berrybush, dock, mine.

    // Player has clicked a berrybush tile
    if(tile->getType() == "berrybush"){

        QString berrybush_gain =
                QString::number(Student::StudentResourcemaps::BERRYBUSHBP.at
                                (Course::BasicResource::FOOD));

        // Set the texts
        ui->label_2->setText("Berrybush");
        ui->reward_label->setText("Gain: " + berrybush_gain + " FOOD");
        ui->send_worker_btn->setText("Send worker");
        ui->notice_label->setText("Send a worker to pick up some berries");
        ui->notice_label_2->setText("Note: Worker will be unavailable two rounds for you");

        // Tile wasn't HQ, so hide the texts
        hideTexts();


    }
    else{

        // Check what building is on the tile and set interface texts

        std::string building_type = tile->getBuildings().at(0)->getType();

        if(building_type == "HeadQuarters")
        {

            QString worker_gold_cost = QString::number(-(Student::StudentResourcemaps::WORKER_RECRUITMENT_COST.at
                                                         (Course::BasicResource::MONEY)));
            QString worker_food_cost = QString::number(-(Student::StudentResourcemaps::WORKER_RECRUITMENT_COST.at
                                                         (Course::BasicResource::FOOD)));

            QString miner_gold_cost = QString::number(-(Student::StudentResourcemaps::MINER_RECRUITMENT_COST.at
                                                        (Course::BasicResource::MONEY)));
            QString miner_food_cost = QString::number(-(Student::StudentResourcemaps::MINER_RECRUITMENT_COST.at
                                                        (Course::BasicResource::FOOD)));

            QString hq_ore_cost = QString::number(-(Student::StudentResourcemaps::HQ_UPGRADE.at
                                                    (Course::BasicResource::ORE)));
            QString hq_gold_cost = QString::number(-(Student::StudentResourcemaps::HQ_UPGRADE.at
                                                     (Course::BasicResource::MONEY)));

            QString title = QString::fromStdString(building_type);

            ui->label_2->setText(title);
            ui->reward_label->setVisible(false);
            ui->send_worker_btn->setVisible(false);
            ui->notice_label->setVisible(false);
            ui->notice_label_2->setVisible(false);


            ui->worker_resource_1->setText(worker_gold_cost + " GOLD, ");
            ui->worker_resource_2->setText(worker_food_cost + " FOOD");
            ui->miner_resource_1->setText(miner_gold_cost + " GOLD, ");
            ui->miner_resource_2->setText(miner_food_cost + " FOOD");

            ui->hq_resource_1->setText(hq_gold_cost + " GOLD, ");
            ui->hq_resource_2->setText(hq_ore_cost + " ORE");


        }
        else if(building_type == "mine"){

            QString mine_gain_gold = QString::number(Student::StudentResourcemaps::MINE_PRODUCTION.at
                                                     (Course::BasicResource::MONEY));
            QString mine_gain_ore = QString::number(Student::StudentResourcemaps::MINE_PRODUCTION.at
                                                    (Course::BasicResource::ORE));
            QString mine_gain_stone = QString::number(Student::StudentResourcemaps::MINE_PRODUCTION.at
                                                      (Course::BasicResource::STONE));


            ui->label_2->setText("The Mine");
            ui->reward_label->setText("Gain: " + mine_gain_gold + " GOLD, " + mine_gain_ore + " ORE, " + mine_gain_stone + " STONE");
            ui->send_worker_btn->setText("Send miner");
            ui->notice_label->setText("WORKER TYPE NEEDED FOR THIS ACTIVITY: MINER");
            ui->notice_label_2->setText("Note: Miner will be unavailable two rounds for you");

            hideTexts();

        }
        else if(building_type == "Dock"){

            QString dock_gain_food = QString::number(Student::StudentResourcemaps::DOCK_PRODUCTION.at
                                                     (Course::BasicResource::FOOD));

            ui->label_2->setText("The Dock");
            ui->reward_label->setText("Gain: " + dock_gain_food + " FOOD");
            ui->send_worker_btn->setText("Send worker");
            ui->notice_label->setText("WORKER TYPE NEEDED: BASIC WORKER");
            ui->notice_label_2->setText("Note: Worker will be unavailable for one round");

            hideTexts();

        }

    }
}


bool popup_dialog::check_if_player_has_funds(Course::ResourceMap resources){

    Course::ResourceMap player_resources = player_->getResources();

    // Compare player resources to the needed resources
    for(std::pair<Course::BasicResource,int> pair_to_compare:resources){
        for(std::pair<Course::BasicResource,int> pair_in:player_resources){
            if(pair_in.first == pair_to_compare.first){
                if(pair_in.second < -(pair_to_compare.second)){
                    return false;
                }
            }
        }
    }

    return true;

}

void popup_dialog::on_pushButton_1_clicked()
{

    //Buy a basic worker

    if(check_if_player_has_funds(Student::StudentResourcemaps::WORKER_RECRUITMENT_COST)){

        std::shared_ptr<Student::GameEventHandler> handler =
                std::dynamic_pointer_cast<Student::GameEventHandler>(tile->get_geh());

        if(handler){
            handler->buy_worker(1, handler,tile->get_objm(),tile);

            emit this->player_bought();
            this->done(3);
        }

    else{

        // Not enough resources
        ui->label->setText("INSUFFICIENT RESOURCES FOR THIS ACTION!");
        ui->label->setVisible(true);
        QTimer::singleShot(2000, ui->label, &QLabel::hide);
    }

}
}

void popup_dialog::on_pushButton_2_clicked()
{

    //Buy a miner
    if(check_if_player_has_funds(Student::StudentResourcemaps::MINER_RECRUITMENT_COST)){

        std::shared_ptr<Student::GameEventHandler> handler =
                std::dynamic_pointer_cast<Student::GameEventHandler>(tile->get_geh());

        if(handler){
            handler->buy_worker(2, handler,tile->get_objm(),tile);
            emit this->player_bought();
            this->done(3);
        }

    else{

        ui->label->setText("INSUFFICIENT RESOURCES FOR THIS ACTION!");
        ui->label->setVisible(true);
        QTimer::singleShot(2000, ui->label, &QLabel::hide);

        }
    }
}

void popup_dialog::on_send_worker_btn_clicked()
{
    bool available_miner = false;
    bool available_worker = false;
    bool send_worker = false;

    std::string workertype = "";
    std::string property_type;

    std::vector<std::shared_ptr<Course::WorkerBase>> workers = player_->getWorkers();

    // Check if player has the specific workertype available for activity
    for(auto worker_type : workers){
        std::shared_ptr<Student::WorkerBase_S> worker =
                std::dynamic_pointer_cast<Student::WorkerBase_S>(worker_type);

        if(worker->getType() == "Miner"){
            if(worker->get_status() == "available"){
                available_miner = true;
            }
        }
        else if(worker->getType() == "Worker"){
            if(worker->get_status() == "available"){
                available_worker = true;
            }
        }
    }

    if(!is_tile_berrybush){
        property_type = tile->getBuildings().at(0)->getType();
    }

    // Worker can go to dock or berrybush activity
    if((property_type == "Dock") || (tile->getType() == "berrybush")){
        if(available_worker){
                workertype = "Worker";
                send_worker = true;
        }
    }

    // Miner can only go to the mines
    else if(property_type == "mine" ){
        if(available_miner){
                workertype = "Miner";
                send_worker = true;
            }
    }

    // Send worker if the player has one available
    if(send_worker){
        if(tile->getWorkerCount() <= 2){
            emit this->sendValue(tile, workertype);
            this->done(1);
        }
        else{

            // Display error for a brief time
            ui->label->setText("TILE CAN ONLY HOLD 3 WORKERS");
            ui->label->setVisible(true);
            QTimer::singleShot(2000, ui->label, &QLabel::hide);
        }

    }
    else{

        // Display error for a brief time
        ui->label->setVisible(true);
        QTimer::singleShot(2000, ui->label, &QLabel::hide);
    }
}


void popup_dialog::on_pushButton_3_clicked()
{

    // Upgrade the HQ (This is not a ready feature)
    if(check_if_player_has_funds(Student::StudentResourcemaps::HQ_UPGRADE)){
        player_->upgraded_hq();
        this->done(3);
    }
    else{
        ui->label->setText("INSUFFICIENT RESOURCES FOR THIS ACTION!");
        ui->label->setVisible(true);
        QTimer::singleShot(2000, ui->label, &QLabel::hide);
    }

}
