#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include "graphics/simplemapitem.h"
#include "gamescene.hh"
#include "mapitem.hh"
#include <math.h>
#include <iostream>
#include "player.hh"
#include "gameeventhandler.hh"
#include "berrybush.h"
#include "grassland_s.h"
#include "forest_s.h"
#include "stone.h"
#include "watertile.h"
#include "house.h"
#include <QMessageBox>
#include <algorithm>
#include "popup_dialog.hh"
#include "objectmanager.hh"

namespace Student{


GameScene::GameScene(QWidget* parent,
                                 int width,
                                 int height,
                                 int scale):
    QGraphicsScene(parent),
    m_mapBoundRect(nullptr),
    m_width(10),
    m_height(10),
    m_scale(50)
{
    setSize(width, height);
    setScale(scale);

    game_over = false;
    buying_mode = false;

}

void GameScene::setSize(int width, int height)
{
    if ( width >= SCENE_WIDTH_LIMITS.first && width <= SCENE_WIDTH_LIMITS.second )
    {
        m_width = width;
    }
    if ( height >= SCENE_HEIGHT_LIMITS.first && height <= SCENE_HEIGHT_LIMITS.second )
    {
        m_height = height;
    }
    resize();
}

void GameScene::setScale(int scale)
{
    if ( scale >= SCENE_SCALE_LIMITS.first && scale <= SCENE_SCALE_LIMITS.second )
    {
        m_scale = scale;
    }
    resize();
}

void GameScene::resize()
{
    if ( m_mapBoundRect != nullptr ){
        QGraphicsScene::removeItem(m_mapBoundRect);
    }

    // Calculates rect with middle at (0,0).
    // Basically left upper corner coords and then width and height
    QRect rect = QRect( 0, 0,
                        m_width * m_scale - 1, m_height * m_scale - 1 );

    addRect(rect, QPen(Qt::black));
    setSceneRect(rect);
    m_mapBoundRect = itemAt(rect.topLeft(), QTransform());

    // Draw on the bottom of all items
    m_mapBoundRect->setZValue(-1);

}

bool GameScene::event(QEvent *event)
{

    if(event->type() == QEvent::GraphicsSceneMousePress)
    {
        QGraphicsSceneMouseEvent* mouse_event =
                dynamic_cast<QGraphicsSceneMouseEvent*>(event);

        // Check if the game is over
        // (If it is, the gamescene becomes unclickable)
        if(game_over == false){

            if ( sceneRect().contains(mouse_event->scenePos())){

                QPointF point = mouse_event->scenePos() / m_scale;

                point.rx() = floor(point.rx());
                point.ry() = floor(point.ry());

                QGraphicsItem* pressed = itemAt(point * m_scale, QTransform());

                if ( pressed != m_mapBoundRect ){

                    std::shared_ptr<Course::GameObject> current_object =
                            static_cast<MapItem*>(pressed)->getBoundObject();

                    Course::Coordinate coordis = current_object->getCoordinate();

                    std::shared_ptr<Student::tilebase_s> current_tile =
                            std::dynamic_pointer_cast<Student::tilebase_s>
                            (object_manager_->getTile(coordis));

                    std::shared_ptr<GameEventHandler> GEHandler_ =
                            std::dynamic_pointer_cast<GameEventHandler>
                            (current_tile->get_geh());

                    // If the player owns the clicked tile, open a dialog
                    if( current_tile->getOwner() == current_player)
                    {
                        open_dialogue(current_tile);
                    }

                    // Player has clicked a berrybush, which is unconquerable
                    else if(current_tile->getType() == "berrybush")
                    {
                        open_dialogue(current_tile);
                    }

                    // Player is buying something, so a different dialog opens
                    if(buying_mode)
                    {
                        GEHandler_->buy_and_manage_properties
                                (current_tile, building_type_);

                        buying_mode = false;

                    }

                    // Change the interface texts
                    emit changeTexts();
                    return true;
                }}
        }
    }

    return false;

}

void GameScene::open_dialogue(std::shared_ptr<Course::TileBase> tile){

    std::shared_ptr<Student::tilebase_s> tile_stu =
            std::dynamic_pointer_cast<Student::tilebase_s>(tile);

    std::shared_ptr<GameEventHandler> GEHandler_ =
            std::dynamic_pointer_cast<GameEventHandler>(tile_stu->get_geh());

    std::shared_ptr<Player> current_player =
            std::dynamic_pointer_cast<Player>(GEHandler_->get_current_player());

    // Player clicked a berrybush
    if (tile->getType() == "berrybush"){
        popup_dialog *New = new popup_dialog(tile_stu,current_player, true);
        New->show();

        connect(New, &popup_dialog::sendValue, this, &GameScene::get_tile_and_worker_type);
        connect(New, &popup_dialog::player_bought, this, &GameScene::get_bought_worker_type);

    }
    // Player clicked one of their owned properties (not house)
    else{
        if(current_player and tile_stu){
            if(tile_stu->getBuildings().at(0)->getType() != "House"){
                popup_dialog *New = new popup_dialog(tile_stu,current_player, false);
                New->show();

                connect(New, &popup_dialog::sendValue, this, &GameScene::get_tile_and_worker_type);
                connect(New, &popup_dialog::player_bought, this, &GameScene::get_bought_worker_type);


            }
        }
    }
}

void GameScene::get_tile_and_worker_type(std::shared_ptr<Course::TileBase> tile,
                                         std::string worker_type ){

    std::shared_ptr<tilebase_s> tile_s = std::dynamic_pointer_cast<tilebase_s>(tile);

    std::shared_ptr<GameEventHandler> GEHandler_ =
            std::dynamic_pointer_cast<GameEventHandler>(tile_s->get_geh());

    // Send a worker to activity, and then update the tile image to map
    // The tile will have a number in the lower right corner, that indicates
    // the number of workers on the tile

    GEHandler_->send_worker_to_activity(tile, worker_type);
    int workers = tile->getWorkerCount();

    if(tile->getType() == "berrybush"){
        this->drawItem(tile, workers);
    }
    else{

        this->drawItem(tile->getBuildings().at(0), workers);

    }


}

void GameScene::get_bought_worker_type(){

    updateStats();

}

void GameScene::drawItem( std::shared_ptr<Course::GameObject> obj, int workers )
{

    std::shared_ptr<Player> current_player_ =
            std::dynamic_pointer_cast<Player>(current_player);

    // Create a new item and add it to the map
    MapItem* nItem = new MapItem(obj, m_scale, current_player_, workers);
    addItem(nItem);
    emit objectPlaced();

    buying_mode = false;
}

void GameScene::Button_pressed(std::string building_type){

    // Player is buying a building type
    buying_mode = true;
    building_type_ = building_type;

}

void GameScene::turn(std::shared_ptr<Course::PlayerBase> player){

    current_player = player;
}

void GameScene::updateStats(){

    emit changeTexts();
}

void GameScene::disable_game_board()
{
    game_over = true;
}

void GameScene::setObjectManager(std::shared_ptr<Course::iObjectManager> obj_m){

    object_manager_ = obj_m;

}

}
