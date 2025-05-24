#ifndef TILEBASE_S_H
#define TILEBASE_S_H

#include "gameeventhandler.hh"
#include "objectmanager.hh"
#include "core/resourcemaps.h"

namespace Student{


class tilebase_s: public Course::TileBase
{
public:
    /**
    * @brief Default constructor of class tilebase_s
    * @param location The coordinate where tile is set to be
    * @param eventhandler The GameEventHandler of the game
    * @param objectmanager The ObjectManager of the game
    * @param max_build The amount of max buildings on the tile,
    * default set to 2
    * @param max_work The amount of max workers on the tile,
    * default set to 3
    * @param production The resource production of the tile,
    * default set to none
    */
    tilebase_s(const Course::Coordinate& location,
               const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
               const std::shared_ptr<Course::iObjectManager>& objectmanager,
               const unsigned int& max_build = 2,
               const unsigned int& max_work = 3,
               const Course::ResourceMap& production = {});
    /**
    * @brief Default destructor of class tilebase_s
    */
    ~tilebase_s();
    /**
    * @brief Get the GameEventHandler
    * @return Course::iGameEventHandler
    */
    std::shared_ptr<Course::iGameEventHandler> get_geh();
    /**
    * @brief Get the ObjectManager
    * @return Course::iObjectManager
    */
    std::shared_ptr<Course::iObjectManager> get_objm();

    virtual std::string getType() const override;
private:
    std::shared_ptr<Course::iGameEventHandler> geh_;
    std::shared_ptr<Course::iObjectManager> objm_;


};
}
#endif // TILEBASE_S_H
