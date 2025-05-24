#include "watertile.h"
namespace Student{
watertile::watertile(const Course::Coordinate &location,
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
                            production)
{

}

watertile::~watertile()
{

}

std::string watertile::getType() const
{
    return "watertile";
}

}
