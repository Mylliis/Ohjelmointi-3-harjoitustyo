#ifndef MINE_H
#define MINE_H
#include "tiles/tilebase.h"
#include <buildings/buildingbase.h>
#include "student_resourcemaps.h"
#include <string>
#include "player.hh"

namespace Student {


class mine : public Course::BuildingBase
{
public:

    /**
    * @brief Default constructor of class mine
    * @param eventhandler The GameEventHandler of the game
    * @param objectmanager The ObjectManager of the game
    * @param owner The owner of the building
    * @param tilespaces The amount of tilespaces the building
    * occupies, default set to 1
    * @param buildcost The cost of building a mine,
    * default set to StudentResourcemaps::MINE_BUILD_COST
    * @param production The resource production of the building,
    * default set to StudentRecoursemaps::MINE_PRODUCTION
    */
    mine(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
         const std::shared_ptr<Course::iObjectManager>& objectmanager,
         const std::shared_ptr<Course::PlayerBase>& owner,
         const int& tilespaces = 1,
         const Course::ResourceMap& buildcost = StudentResourcemaps::MINE_BUILD_COST,
         const Course::ResourceMap& production = StudentResourcemaps::MINE_PRODUCTION);

    /**
    * @brief Default destructor of class mine
    */
    ~mine();

    /**
    * @brief Returns the type of the building
    * @return mine
    */
    virtual std::string getType() const override;

    /**
    * @brief Checks if mine can be placed on targer tile,
    * in practise checks if the tile is stone.
    * @param target The tile to check
    */
    virtual bool canBePlacedOnTile(
            const std::shared_ptr<Course::TileBase> &target) const override;


};
}
#endif // MINE_H
