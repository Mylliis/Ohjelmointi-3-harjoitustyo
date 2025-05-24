#ifndef GRASSLAND_S_H
#define GRASSLAND_S_H
#include "tiles/grassland.h"
#include "core/resourcemaps.h"
#include "gameeventhandler.hh"
#include "objectmanager.hh"
#include "student_resourcemaps.h"
#include "core/basicresources.h"
#include "tilebase_s.h"

namespace Student {


class Grassland_S : public tilebase_s
{
public:
    /**
    * @brief Default constructor of class Grassland_S
    * @param location The coordinate where tile is set to be
    * @param eventhandler The GameEventHandler of the game
    * @param objectmanager The ObjectManager of the game
    * @param max_build The amount of max buildings on the tile,
    * default set to 2
    * @param max_work The amount of max workers on the tile,
    * default set to 3
    * @param production The resource production of the tile,
    * default set to StudentResourcemaps::GRASSLAND_BP
    */
    Grassland_S(const Course::Coordinate& location,
              const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
              const std::shared_ptr<Course::iObjectManager> &objectmanager,
              const unsigned int& max_build = 2,
              const unsigned int& max_work = 3,
              const Course::ResourceMap& production = StudentResourcemaps::GRASSLAND_BP);
    /**
    * @brief Default destructor of class Grassland_S
    */
    ~Grassland_S();
    /**
    * @brief Get the type of the tile
    * @return Grassland_S
    */
    virtual std::string getType() const override;
private:
};
}
#endif // GRASSLAND_S_H
