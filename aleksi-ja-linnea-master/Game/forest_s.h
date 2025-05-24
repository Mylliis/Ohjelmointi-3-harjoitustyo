#ifndef FOREST_S_H
#define FOREST_S_H
#include "tiles/forest.h"
#include "gameeventhandler.hh"
#include "objectmanager.hh"
#include "student_resourcemaps.h"
#include "tilebase_s.h"

namespace Student {


class Forest_S : public tilebase_s
{
public:
    /**
    * @brief Default constructor of class Forest_S
    * @param location The coordinate where tile is set to be
    * @param eventhandler The GameEventHandler of the game
    * @param objectmanager The ObjectManager of the game
    * @param max_build The amount of max buildings on the tile,
    * default set to 2
    * @param max_work The amount of max workers on the tile,
    * default set to 3
    * @param production The resource production of the tile,
    * default set to COURSE::ConstResourceMaps::FOREST_BP
    */
    Forest_S(const Course::Coordinate& location,
           const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
           const std::shared_ptr<Course::iObjectManager> &objectmanager,
           const unsigned int& max_build = 2,
           const unsigned int& max_work = 3,
           const Course::ResourceMap& production = Course::ConstResourceMaps::FOREST_BP);
    /**
    * @brief Default destructor of class Forest_S
    */
    ~Forest_S();
    /**
    * @brief Returns the type of the tile
    * @return Forest_S
    */
    virtual std::string getType() const override;
    /**
    * @brief Add a building to the tile
    * @param building The building to be added
    */
    void addBuilding(const std::shared_ptr<Course::BuildingBase>& building) override;

private:

};
}
#endif // FOREST_S_H
