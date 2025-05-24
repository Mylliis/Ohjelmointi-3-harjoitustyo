#include "gameeventhandler.hh"

#include "popup_dialog.hh"
#include "house.h"
#include <QMessageBox>
#include <iostream>
#include <algorithm>
#include "student_resourcemaps.h"
#include "dock.h"
#include "mine.h"
#include "miner.h"
#include "player.hh"


namespace Student{
GameEventHandler::GameEventHandler()
{

}

GameEventHandler::~GameEventHandler()
{

}

bool GameEventHandler::modifyResources(std::shared_ptr<Course::PlayerBase> player,
                                       Course::ResourceMap resources)
{
    std::shared_ptr<Player> d = std::dynamic_pointer_cast<Player>(player);
    if(d){
        d->modify_resources(resources);
        return true;
    }else{
        return false;
    }


}

bool GameEventHandler::modifyResource(std::shared_ptr<Course::PlayerBase> player,
                                      Course::BasicResource resource, int amount)
{
    std::shared_ptr<Player> d =std::dynamic_pointer_cast<Player>(player);
    if(d){
        d->modify_resource(resource,amount);
        return true;
    }else{
        return false;
    }

}

std::shared_ptr<Course::PlayerBase> GameEventHandler::get_current_player(){

    return turn_.first;

}



void GameEventHandler::start_working(std::shared_ptr<Course::WorkerBase> worker_going_work,
                                     std::shared_ptr<Course::TileBase> tile)
{
    std::shared_ptr<WorkerBase_S> worker_s = std::dynamic_pointer_cast<WorkerBase_S>(worker_going_work);
    if(worker_s){

     worker_s->update_status("unavailable",tile);

    }


}

void GameEventHandler::update_rounds_on_work()
{
    std::shared_ptr<Player> current_player = std::dynamic_pointer_cast<Player>(turn_.first);
    std::vector<std::shared_ptr<Course::WorkerBase>> workers = current_player->getWorkers();

    // Let's check the status of all the players workers
    for(auto workertype : workers){
        std::shared_ptr<Student::WorkerBase_S> worker =
                std::dynamic_pointer_cast<Student::WorkerBase_S>(workertype);

        // If a worker is unavailable, update the work progress
        if(worker->get_status() == "unavailable"){
            worker->update_rounds_unavailability();

            // If worker is done in the activity, it's time to call them home
            if(worker->return_remaining_unavailability_rounds() == 0){

                std::shared_ptr<Course::TileBase> tile = worker->get_tile_where_worker_is_at();

                // Set worker status back to available
                worker->update_status("available", nullptr);
                tile->removeWorker(worker);
                int workers_count = tile->getWorkerCount();
                std::cout << workers_count << std::endl;

                // Gather the resources from wherever the worker was

                if(tile->getType() == "berrybush"){

                    current_player->modify_resources(Student::StudentResourcemaps::BERRYBUSHBP);
                    scene_->drawItem(tile, workers_count);
                }
                else{
                    std::vector<std::shared_ptr<Course::BuildingBase>> building = tile->getBuildings();
                    std::string building_type = building.at(0)->getType();
                    if(building_type == "Dock"){
                        current_player->modify_resources(Student::StudentResourcemaps::DOCK_PRODUCTION);
                    }
                    else if(building_type == "mine"){
                        current_player->modify_resources(Student::StudentResourcemaps::MINE_PRODUCTION);
                    }

                    scene_->drawItem(tile->getBuildings().at(0), workers_count);
                }

        }
    }

}
}

void GameEventHandler::add_worker(std::shared_ptr<Course::WorkerBase> worker_to_add,
                                  std::shared_ptr<Course::PlayerBase> player,
                                  std::shared_ptr<Course::TileBase> tile)
{   std::vector<worker_and_locale> vector;
    worker_and_locale struccct ={worker_to_add , tile, 0};
    vector.push_back(struccct);
    if(workers_.find(player)==workers_.end()){
    workers_.insert({player,vector});
    
    }else{
    workers_[player].push_back({worker_to_add,tile,0});
    }std::shared_ptr<Player> s_player = std::dynamic_pointer_cast<Player>(player);
    if(s_player){
        s_player->add_worker_miner(worker_to_add);
    }
}

void GameEventHandler::giveScene(GameScene *scene)
{
    scene_ = scene;

}




void GameEventHandler::turn(std::shared_ptr<Course::PlayerBase> player, int round)

{
        turn_.first =player;
        turn_.second = round;
}


void GameEventHandler::send_worker_to_activity(std::shared_ptr<Course::TileBase> tile,
                                               std::string worker_type ){

    std::shared_ptr<Player> current_player = std::dynamic_pointer_cast<Player>(turn_.first);
    std::vector<std::shared_ptr<Course::WorkerBase>> all_workers = current_player->getWorkers();

    // Let's find the specific type of worker who's also available
    for(auto worker : all_workers){
        std::cout << worker->getType() << std::endl;

        std::shared_ptr<Student::WorkerBase_S> worker_2 =
                std::dynamic_pointer_cast<Student::WorkerBase_S>(worker);

        // Found an available worker
        if((worker_2->get_status() == "available") && (worker_2->getType() == worker_type)){

               // Send worker to the activity

               tile->addWorker(worker_2);
               start_working(worker_2, tile);
               worker_2->set_unavailable_rounds(2);
               scene_->updateStats();

               return;
        }

    }



}

void GameEventHandler::buy_and_manage_properties(std::shared_ptr<Course::TileBase> tile,
                                                 std::string building_type)
{

    std::shared_ptr<Course::PlayerBase> tile_owner = tile->getOwner();
    std::shared_ptr<tilebase_s> current_tile = std::dynamic_pointer_cast<Student::tilebase_s>(tile);
    std::shared_ptr<Player> current_player = std::dynamic_pointer_cast<Player>(turn_.first);

    std::map< std::string, std::vector<std::string> > terrain_type_buildings = {{"House", {"Grassland", "Forest"}},
                                                                                {"Dock", {"watertile"}},
                                                                                {"Mine", {"stone"}}};

    // The player has conquered the tile (or it's unconquered)
    if((tile_owner == nullptr) || (tile_owner == current_player)){

        // Check if it's possible to build the wanted house type on this terrain
        if (tile->getBuildingCount() == 0){
            std::vector<std::string> types = terrain_type_buildings.at(building_type);
            if(std::find(types.begin(), types.end(), current_tile->getType()) != types.end()) {

                if(building_type == "Mine"){

                    current_player->modify_resources(StudentResourcemaps::MINE_BUILD_COST);

                    std::shared_ptr<mine> new_mine = std::make_shared<mine>(current_tile->get_geh(),
                                                                            current_tile->get_objm(),
                                                                            current_player);

                    current_tile->addBuilding(new_mine);
                    new_mine->setCoordinate(current_tile->getCoordinate());
                    scene_->drawItem(new_mine, 0);
                }
                else if(building_type == "House"){

                    current_player->modify_resources(StudentResourcemaps::HOUSE_BUILD_COST);

                    // Building on forest grants extra resources
                    if(current_tile->getType() == "Forest"){
                        current_player->modify_resource(Course::BasicResource::WOOD, 100);
                        current_player->modify_resource(Course::BasicResource::FOOD, -50);

                    }

                    std::shared_ptr<house> new_house = std::make_shared<house>(current_tile->get_geh(),
                                                                               current_tile->get_objm(),
                                                                               current_player);
                    current_tile->addBuilding(new_house);

                    new_house->setCoordinate(current_tile->getCoordinate());
                    scene_->drawItem(new_house, 0);


                }
                else if(building_type == "Dock"){

                    current_player->modify_resources(StudentResourcemaps::DOCK_BUILD_COST);

                    std::shared_ptr<dock> new_dock = std::make_shared<dock>(current_tile->get_geh(),
                                                                            current_tile->get_objm(),
                                                                            current_player);
                    current_tile->addBuilding(new_dock);
                    new_dock->setCoordinate(current_tile->getCoordinate());
                    scene_->drawItem(new_dock, 0);
                }


                // Claim the tile and add a property on it
                current_tile->setOwner(current_player);
                current_player->add_to_claimed_tiles();
                current_player->add_to_total_properties(building_type);

            }
            else {

                // Display an error message
                QMessageBox msgBox;
                msgBox.setStyleSheet("background-color: #5D1B0E; color: #e5bd1b;");
                msgBox.setText("Unavailable terrain type for chosen action!!");
                msgBox.exec();
                }

        }
        else {
            // Display an error message
            QMessageBox msgBox;
            msgBox.setStyleSheet("background-color: #5D1B0E; color: #e5bd1b;");
            msgBox.setText("This tile already has property on it!");
            msgBox.exec();
        }
    }

    else
    {
        // Display an error message
            QMessageBox msgBox;
            msgBox.setStyleSheet("background-color: #5D1B0E; color: #e5bd1b;");
            msgBox.setText("This tile is already occupied by someone else.");
            msgBox.exec();
        }


}

void GameEventHandler::buy_worker(int type,std::shared_ptr<Course::iGameEventHandler> geh,
                                  std::shared_ptr<Course::iObjectManager> mngr,
                                  std::shared_ptr<Course::TileBase> tile)
{
    std::shared_ptr<Student::Player> player_stud =
        std::dynamic_pointer_cast<Student::Player>(turn_.first);

    if(player_stud){

        if(type == 1){

            player_stud->modify_resources(Student::StudentResourcemaps::WORKER_RECRUITMENT_COST);
            std::shared_ptr<worker> worker_to_add = std::make_shared<worker>(geh,mngr,turn_.first);
            add_worker(worker_to_add,player_stud,tile);
        }
        else if(type == 2){
            player_stud->modify_resources(Student::StudentResourcemaps::MINER_RECRUITMENT_COST);
            std::shared_ptr<miner> worker_to_add = std::make_shared<miner>(geh,mngr,turn_.first);
            add_worker(worker_to_add,player_stud,tile);
        }

  }

}

}
