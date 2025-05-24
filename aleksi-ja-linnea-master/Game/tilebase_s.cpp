#include "tilebase_s.h"
namespace Student {


tilebase_s::tilebase_s(const Course::Coordinate &location,
                       const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                       const std::shared_ptr<Course::iObjectManager> &objectmanager,
                       const unsigned int &max_build,
                       const unsigned int &max_work,
                       const Course::ResourceMap &production):
    Course::TileBase(location,
                     eventhandler,
                     objectmanager,
                     max_build,
                     max_work,
                     production),geh_(eventhandler), objm_(objectmanager)
{

}

tilebase_s::~tilebase_s()
{

}
std::shared_ptr<Course::iGameEventHandler> tilebase_s::get_geh()
{
    return geh_;
}

std::shared_ptr<Course::iObjectManager> tilebase_s::get_objm()
{
    return objm_;
}

std::string tilebase_s::getType() const
{
    return "tilebase_s";
}
}
