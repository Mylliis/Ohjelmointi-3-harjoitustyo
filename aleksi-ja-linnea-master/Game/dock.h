#ifndef DOCK_H
#define DOCK_H
#include "buildings/buildingbase.h"
#include "student_resourcemaps.h"
namespace Student{

class dock:public Course::BuildingBase
{
public:
    /**
    * @brief Default constructor of class dock
    * @param eventhandler The GameEventHandler of the game
    * @param objectmanager The ObjectManager of the game
    * @param owner The owner of the building
    * @param tilespaces The amount of tilespaces the building
    * occupies, default set to 1
    * @param buildcost The cost of building a dock,
    * default set to StudentResourcemaps::DOCK_BUILD_COST
    * @param production The resource production of the building,
    * default set to StudentRecoursemaps::DOCK_PRODUCTION
    */
    dock(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
         const std::shared_ptr<Course::iObjectManager>& objectmanager,
         const std::shared_ptr<Course::PlayerBase>& owner,
         const int& tilespaces = 1,
         const Course::ResourceMap& buildcost = Student::StudentResourcemaps::DOCK_BUILD_COST,
         const Course::ResourceMap& production = Student::StudentResourcemaps::DOCK_PRODUCTION);
    /**
    * @brief Default destructor of class dock
    */
    ~dock();
    /**
    * @brief Returns the building type
    * @return dock
    */
    virtual std::string getType() const override;

};
}
#endif // DOCK_H
