#include "forest_s.h"
namespace Student{
Forest_S::Forest_S(const Course::Coordinate &location,
               const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
               const std::shared_ptr<Course::iObjectManager> &objectmanager,
               const unsigned int &max_build,
               const unsigned int &max_work,
               const Course::ResourceMap &production):
    tilebase_s(location,
                   eventhandler,
                   objectmanager,
                   max_build,
                   max_work,
                   production
        )
{

}

Forest_S::~Forest_S()
{

}
std::string Forest_S::getType() const
{
    return "Forest";
}

void Forest_S::addBuilding(const std::shared_ptr<Course::BuildingBase>& building)
{
    TileBase::addBuilding(building);
    building->addHoldMarkers(1);
}
}
