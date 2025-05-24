#include "objectmanager.hh"
#include <algorithm>


namespace Student{

ObjectManager::ObjectManager():
    iObjectManager()
{

}

std::vector<std::shared_ptr<Course::TileBase> > ObjectManager::getTiles(
        const std::vector<Course::Coordinate> &coordinates)
{

    std::vector<std::shared_ptr<Course::TileBase>> tiles;

    // Search the tiles by given coordinates
    for(long unsigned int index; index<coordinates.size();++index){
        for (std::shared_ptr<Course::TileBase> tile : world_tiles){
            if(tile->getCoordinate()==coordinates.at(index)){
                tiles.push_back(tile);
            }
        }
    }

    return tiles;
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::ObjectId &id)
{

    std::shared_ptr<Course::TileBase> tile_to_return = nullptr;

    // Search the tile by id
    for(std::shared_ptr<Course::TileBase> tile : world_tiles){

        if (tile->ID==id){
            tile_to_return = tile;
        }
    }

    return tile_to_return;

}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::Coordinate &coordinate)
{

        // Search the tile by coordinate
        for(std::shared_ptr<Course::TileBase> tile : world_tiles){

            if(tile->getCoordinate() == coordinate){
                return tile;
            }
        }

      return nullptr;

}

void ObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase> > &tiles)

{
    std::vector<std::shared_ptr<Course::TileBase>>::size_type container_size = tiles.size();

    // Add tiles to the main tile datastructure
    for(unsigned int val = 0; val < container_size; ++val){
        world_tiles.push_back(tiles.at(val));
    }

}

std::vector<std::shared_ptr<Course::TileBase>> ObjectManager::get_world_tiles(){

    return world_tiles;
}


void ObjectManager::DrawMap(std::shared_ptr<GameScene> scene)

{

    // Draws all the tiles into the gamescene
    for (std::shared_ptr<Course::TileBase> tile : world_tiles){
        scene->drawItem(tile, 0);
    }

}

void ObjectManager::AddBuilding(std::shared_ptr<Course::BuildingBase> building){

    // Add the building to the building datastructure
    // so it wont disappear
    buildings.push_back(building);

}

}
