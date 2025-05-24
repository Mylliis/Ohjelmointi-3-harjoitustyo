#include "mine.h"


namespace Student{

mine::mine(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
           const std::shared_ptr<Course::iObjectManager> &objectmanager,
           const std::shared_ptr<Course::PlayerBase> &owner,
           const int &tilespaces,
           const Course::ResourceMap &buildcost,
           const Course::ResourceMap &production):
    Course::BuildingBase(
        eventhandler,
        objectmanager,
        owner,
        tilespaces,
        buildcost,
        production
        )
{

}

mine::~mine()
{

}

std::string Student::mine::mine::getType() const
{
    return "mine";
}

bool mine::canBePlacedOnTile(const std::shared_ptr<Course::TileBase> &target) const
{
    if(target->getType()=="stone"
            and target->hasSpaceForBuildings(1)){
        return true;
    }else{return false;}
}


}
