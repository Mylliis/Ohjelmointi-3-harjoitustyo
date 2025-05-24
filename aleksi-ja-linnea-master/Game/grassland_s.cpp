#include "grassland_s.h"
namespace Student{
Grassland_S::Grassland_S(const Course::Coordinate& location,
                     const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                     const std::shared_ptr<Course::iObjectManager>& objectmanager,
                     const unsigned int& max_build,
                     const unsigned int& max_work,
                     const Course::ResourceMap& production):
    tilebase_s(location,
                      eventhandler,
                      objectmanager,
                      max_build,
                      max_work,
                      production)
{

}

Grassland_S::~Grassland_S()
{

}

std::string Grassland_S::getType() const
{
    return "Grassland";
}
}
