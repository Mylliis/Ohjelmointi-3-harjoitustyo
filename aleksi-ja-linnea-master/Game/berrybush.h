#ifndef BERRYBUSH_H
#define BERRYBUSH_H
#include <string>
#include <tiles/tilebase.h>
#include "core/basicresources.h"
#include <QPainter>
#include "tilebase_s.h"

namespace Student{

class berrybush : public tilebase_s
{
public:
    /**
    * @brief Default constructor of class berrybush
    * @param location The coordinate where tile is set to be
    * @param eventhandler The GameEventHandler of the game
    * @param objectmanager The ObjectManager of the game
    * @param max_build The amount of max buildings on the tile,
    * default set to 2
    * @param max_work The amount of max workers on the tile,
    * default set to 3
    * @param production The resource production of the tile,
    * default set to StudentRecoursemaps::BERRYBUSHBP
    */
    berrybush(const Course::Coordinate& location,
              const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
              const std::shared_ptr<Course::iObjectManager> &objectmanager,
              const unsigned int& max_build = 2,
              const unsigned int& max_work = 3,
              const Course::ResourceMap& production = StudentResourcemaps::BERRYBUSHBP);

    /**
     * @brief Default destructor of class berrybush
    */
    ~berrybush();
    /**
     * @brief Get the type of the tile
     * @return berrybush
     */
    virtual std::string getType() const override;



};
}
#endif // BERRYBUSH_H
