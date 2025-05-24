#include "mapitem.hh"
#include <iostream>
#include <QDebug>

namespace Student{


MapItem::MapItem(const std::shared_ptr<Course::GameObject> &obj,
                 int size, std::shared_ptr<Player> player, int workers):

    m_gameobject(obj), m_scenelocation(m_gameobject->getCoordinatePtr()->asQpoint()),
    m_size(size), player_(player), workers_(workers)
{

}

void MapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                    QWidget *widget)
{
    Q_UNUSED( option ); Q_UNUSED( widget );

    QRectF rect = boundingRect();

    if( m_gameobject->getType() == "HeadQuarters" ){


        if (player_->get_color() == "RED"){

            QPixmap image(":/files/castle_2.png");
            painter->setBrush(QBrush(image));

        }

        else if (player_->get_color() == "BLUE"){

            QPixmap image(":/files/blue_castle.png");
            painter->setBrush(QBrush(image));
        }

    }

    else if( m_gameobject->getType() == "House"){

        if (player_->get_color() == "RED"){
            QPixmap image(":/files/red_house.png");

            painter->setBrush(QBrush(image));
        }
        else if (player_->get_color() == "BLUE"){
            QPixmap image(":/files/blue_house.png");

            painter->setBrush(QBrush(image));
        }

    }

    else if( m_gameobject->getType() == "Dock"){

        if (player_->get_color() == "RED"){
            if(workers_ == 1){
                QPixmap image(":/files/red_dock_workers_1.png");
                painter->setBrush(QBrush(image));
            }
            else if(workers_ == 2){
                QPixmap image(":/files/red_dock_workers_2.png");
                painter->setBrush(QBrush(image));
            }
            else if(workers_ == 3){
                QPixmap image(":/files/red_dock_workers_3.png");
                painter->setBrush(QBrush(image));
            }
            else{
                QPixmap image(":/files/red_dock.png");
                painter->setBrush(QBrush(image));
            }
        }
        else if (player_->get_color() == "BLUE"){
            if(workers_ == 1){
                QPixmap image(":/files/blue_dock_workers_1.png");
                painter->setBrush(QBrush(image));
            }
            else if(workers_ == 2){
                QPixmap image(":/files/blue_dock_workers_2.png");
                painter->setBrush(QBrush(image));
            }
            else if(workers_ == 3){
                QPixmap image(":/files/blue_dock_workers_3.png");
                painter->setBrush(QBrush(image));
            }
            else{
                QPixmap image(":/files/blue_dock.png");
                painter->setBrush(QBrush(image));
            }
        }

    }

    else if( m_gameobject->getType() == "mine"){

        if (player_->get_color() == "RED"){
            if(workers_ == 1){
                QPixmap image(":/files/red_mine_workers_1.png");
                painter->setBrush(QBrush(image));
            }
            else if(workers_ == 2){
                QPixmap image(":/files/red_mine_workers_2.png");
                painter->setBrush(QBrush(image));
            }
            else if(workers_ == 3){
                QPixmap image(":/files/red_mine_workers_3.png");
                painter->setBrush(QBrush(image));
            }
            else{
                QPixmap image(":/files/red_mine.png");
                painter->setBrush(QBrush(image));
            }
        }
        else if (player_->get_color() == "BLUE"){
            if(workers_ == 1){
                QPixmap image(":/files/blue_mine_workers_1.png");
                painter->setBrush(QBrush(image));
            }
            else if(workers_ == 2){
                QPixmap image(":/files/blue_mine_workers_2.png");
                painter->setBrush(QBrush(image));
            }
            else if(workers_ == 3){
                QPixmap image(":/files/blue_mine_workers_3.png");
                painter->setBrush(QBrush(image));
            }
            else{
                QPixmap image(":/files/blue_mine.png");
                painter->setBrush(QBrush(image));
            }
        }


    }

    else if ( m_gameobject->getType() == "berrybush" ){

        if(workers_ == 1){
            QPixmap image(":/files/berrybush_1_worker.png");
            painter->setBrush(QBrush(image));
        }
        else if(workers_ == 2){
            QPixmap image(":/files/berrybush_2_worker.png");
            painter->setBrush(QBrush(image));
        }
        else if(workers_ == 3){
            QPixmap image(":/files/berrybush_3_worker.png");
            painter->setBrush(QBrush(image));
        }
        else{

            QPixmap bush_img(":/files/bush_2.png");
            painter->setBrush(QBrush(bush_img));
        }

    }

    else if( m_gameobject->getType() == "Forest") {

        QPixmap woods_img(":/files/woods.png");

        painter->setBrush(QBrush(woods_img));
    }

    else if( m_gameobject->getType() == "stone") {

        QPixmap cave_img(":/files/stonecave.png");

        painter->setBrush(QBrush(cave_img));
    }

    else if( m_gameobject->getType() == "watertile") {

        QPixmap water_img(":/files/water.png");

        painter->setBrush(QBrush(water_img));
    }

    else{
        QColor grass_color = QColor(36,156,98);
        painter->setBrush(grass_color);
    }

    painter->drawRect(rect);

}

const std::shared_ptr<Course::GameObject> &MapItem::getBoundObject()
{
    return m_gameobject;
}

QRectF MapItem::boundingRect() const
{
    return QRectF(m_scenelocation * m_size, m_scenelocation *
                  m_size + QPoint(m_size, m_size));
}


}
