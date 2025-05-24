#ifndef HOUSE_H
#define HOUSE_H
#include <string>
#include <buildings/buildingbase.h>
#include "student_resourcemaps.h"


namespace Student{


class house : public Course::BuildingBase
{
public:
    /**
    * @brief Default constructor of class house
    * @param eventhandler The GameEventHandler of the game
    * @param objectmanager The ObjectManager of the game
    * @param owner The owner of the building
    * @param tilespaces The amount of tilespaces the building
    * occupies, default set to 1
    * @param buildcost The cost of building a house,
    * default set to StudentResourcemaps::HOUSE_BUILD_COST
    * @param production The resource production of the building,
    * default set to StudentRecoursemaps::HOUSE_PRODUCTION
    */
    house(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
          const std::shared_ptr<Course::iObjectManager>& objectmanager,
          const std::shared_ptr<Course::PlayerBase>& owner,
          const int& tilespaces = 1,
          const Course::ResourceMap& buildcost = StudentResourcemaps::HOUSE_BUILD_COST,
          const Course::ResourceMap& production = StudentResourcemaps::HOUSE_PRODUCTION);
    /**
    * @brief Default destructor of class house
    */
    ~house();
    /**
    * @brief Get the type of the building
    * @return house
    */
    virtual std::string getType() const override;

};
}
#endif // HOUSE_H
