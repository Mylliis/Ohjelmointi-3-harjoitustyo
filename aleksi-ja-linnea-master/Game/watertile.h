#ifndef WATERTILE_H
#define WATERTILE_H
#include "tiles/tilebase.h"
#include "student_resourcemaps.h"
#include "gameeventhandler.hh"
#include "objectmanager.hh"
#include "tilebase_s.h"

namespace Student{
class watertile : public tilebase_s
{
public:
    /**
    * @brief Default constructor of class watertile
    * @param location The coordinate where tile is set to be
    * @param eventhandler The GameEventHandler of the game
    * @param objectmanager The ObjectManager of the game
    * @param max_build The amount of max buildings on the tile,
    * default set to 2
    * @param max_work The amount of max workers on the tile,
    * default set to 3
    * @param production The resource production of the tile,
    * default set to StudentResourcemaps::WATERTILE_BP
    */
    watertile(const Course::Coordinate& location,
              const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
              const std::shared_ptr<Course::iObjectManager> &objectmanager,
              const unsigned int& max_build = 1,
              const unsigned int& max_work = 3,
              const Course::ResourceMap& production = Student::StudentResourcemaps::WATERTILE_BP);
    /**
    * @brief Default destructor of class watertile
    */
    ~watertile();
    /**
    * @brief Get the type of the tile
    * @return watertile
    */
    virtual std::string getType() const override;
private:

};
}
#endif // WATERTILE_H
