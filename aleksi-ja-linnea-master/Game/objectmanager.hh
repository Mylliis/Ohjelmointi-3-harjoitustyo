#ifndef OBJECTMANAGER_HH
#define OBJECTMANAGER_HH
#include "gamescene.hh"
#include "interfaces/iobjectmanager.h"
#include "mapwindow.hh"

#include <vector>

namespace Student{

/** @brief
 * Manages the gameobjects. Passes the gametiles to other
 * classes.
 * */
class ObjectManager : public Course::iObjectManager
{
public:

    /** Default constructor **/
    ObjectManager();

    /** Adds tiles to the game's tile datastructure.
     * @param tiles - Bunch of tiles to be added.
     * @note gets called only when generating the map **/
    void addTiles(
            const std::vector<std::shared_ptr<Course::TileBase>>& tiles);

    /** Getter for a single tile by specific coordinate
     * @param coordinate - Tile's coordinate
     * @return a tile object
     * */
    virtual std::shared_ptr<Course::TileBase> getTile(
            const Course::Coordinate& coordinate);

    /** Getter for a single tile by specific object id
     * @param id - object's id
     * @return a tile object
     * */
    virtual std::shared_ptr<Course::TileBase> getTile(const Course::ObjectId& id);

    /** Getter for multiple tiles by specific coordinates
     * @param coordinates - list of coordinates
     * @return - list of tiles
     * */
    virtual std::vector<std::shared_ptr<Course::TileBase>> getTiles(
            const std::vector<Course::Coordinate>& coordinates);

    /** Draws all of the tiles into the scene (gameboard)
     * @param m_simplescene - scene where tiles are drawn
     * */
    void DrawMap(std::shared_ptr<GameScene> m_simplescene);

    /** Adds a building to the building datastructure
     * @param building - building object to be added
     * @note datastructure exists only to hold on to weak pointers
     * */
    void AddBuilding(std::shared_ptr<Course::BuildingBase> building);

    /** Getter for a single tile by specific coordinate
     * @param coordinate - Tile's coordinate
     * @return a tile object
     * */
    std::shared_ptr<Course::TileBase> getTile(std::shared_ptr<Course::Coordinate> coordinate);

    /** Getter for the tile-datastructure
     * @return a list of all the tiles in the game
     * */
    std::vector<std::shared_ptr<Course::TileBase>> get_world_tiles();


private:

    std::vector<std::shared_ptr<Course::TileBase>> world_tiles;
    std::vector<std::shared_ptr<Course::BuildingBase>> buildings;


};
}
#endif // OBJECTMANAGER_HH
