#include "add_building_dialog.hh"
#include "ui_add_building_dialog.h"
#include "core/resourcemaps.h"
#include "core/basicresources.h"
#include <QDebug>
#include "student_resourcemaps.h"
#include <iostream>
#include <QTimer>

add_building_dialog::add_building_dialog(Course::ResourceMap resources, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_building_dialog),
    player_resources(resources)
{
    ui->setupUi(this);
    this->setWindowTitle("Add new properties");

    //Error label
    ui->label_5->setVisible(false);
    ui->label_5->setText("Insufficient funds!");

}

add_building_dialog::~add_building_dialog()
{
    delete ui;
}

bool add_building_dialog::check_if_player_has_funds(Course::ResourceMap resources){

    // Compare the player resources to the resources needed for the property
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

void add_building_dialog::on_pushButton_clicked()
{
    //Check if player has all the resources for a house
    if(check_if_player_has_funds(Student::StudentResourcemaps::HOUSE_BUILD_COST)){

        emit this->sendValue_2("House");
        this->done(0);
    }
    else{

        // Display error for a brief time
        ui->label_5->setVisible(true);
        QTimer::singleShot(2000, ui->label_5, &QLabel::hide);
    }

}

void add_building_dialog::on_pushButton_2_clicked()
{
    //Check if player has all the resources for a mine
    if(check_if_player_has_funds(Student::StudentResourcemaps::MINE_BUILD_COST)){

        emit this->sendValue_2("Mine");
        this->done(1);
    }
    else{

        // Display error for a brief time
        ui->label_5->setVisible(true);
        QTimer::singleShot(2000, ui->label_5, &QLabel::hide);
    }
}

void add_building_dialog::on_pushButton_3_clicked()
{
    //Check if player has all the resources for a dock
    if(check_if_player_has_funds(Student::StudentResourcemaps::DOCK_BUILD_COST)){

        emit this->sendValue_2("Dock");
        this->done(2);
    }
    else{

        // Display error for a brief time
        ui->label_5->setVisible(true);
        QTimer::singleShot(2000, ui->label_5, &QLabel::hide);
    }
}
