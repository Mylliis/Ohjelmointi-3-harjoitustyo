#include "player.hh"
#include <algorithm>
#include <vector>
#include <iostream>
#include <QDebug>
#include <map>

namespace Student{

Player::Player(const std::string& name,
                       const std::vector<std::shared_ptr<Course::GameObject> > objects):
    Course::PlayerBase(name,
                       objects)
{
    total_properties = {{"House", 0},
                        {"Dock", 0},
                        {"Mine", 0}};

    has_upgraded_hq = false;

    player_resources_ = StudentResourcemaps::PLAYER_STARTING_RESOURCES;

    //Dev purposes only
    //player_resources_ = StudentResourcemaps::GOD_RESOURCES;

    claimed_tiles = 0;

}

Course::ResourceMap Player::getResources()
{
    return player_resources_;
}

void Player::upgraded_hq(){

    has_upgraded_hq = true;
}

void Player::add_to_claimed_tiles()
{
    claimed_tiles += 1;
}

int Player::get_claimed_tiles_amt()
{
    return claimed_tiles;
}

std::map<std::string, int> Player::get_total_properties(){

    return total_properties;
}

void Player::add_to_total_properties(std::string type){

    int &total = total_properties.at(type);
    total += 1;

}

void Player::modify_resource(Course::BasicResource resource, int amount)
{
    for(std::pair<Course::BasicResource,int> pair : player_resources_){
        if (resource==pair.first){
            player_resources_[resource]+=amount;
        }
    }
}

void Player::modify_resources(Course::ResourceMap resources)
{
    for(std::pair<Course::BasicResource,int> pair_to_add:resources){
        for(std::pair<Course::BasicResource,int> pair_in:player_resources_){
            if(pair_in.first==pair_to_add.first){
                player_resources_[pair_to_add.first]+=pair_to_add.second;
            }
        }
    }
}

std::vector<std::shared_ptr<Course::WorkerBase> > Player::getWorkers()
{
    return workers_;
}


void Player::add_worker_miner(std::shared_ptr<Course::WorkerBase> worker_to_add)
{
    workers_.push_back(worker_to_add);
}

std::string Player::get_color(){

    return player_color;
}

void Player::set_color(std::string color)
{
    player_color = color;

}

}





