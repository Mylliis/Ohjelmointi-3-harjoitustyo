#include "berrybush.h"
#include "QPixmap"


namespace Student{

berrybush::berrybush(const Course::Coordinate &location,
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

berrybush::~berrybush()
{

}

std::string Student::berrybush::berrybush::getType() const
{
    return "berrybush";
}

}
