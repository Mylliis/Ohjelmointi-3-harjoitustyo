#ifndef GAMESCENE_HH
#define GAMESCENE_HH

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

#include <map>
#include <memory>
#include "core/gameobject.h"
#include "interfaces/iobjectmanager.h"

namespace Student{

const std::pair<int, int> SCENE_WIDTH_LIMITS = {1, 100};
const std::pair<int, int> SCENE_HEIGHT_LIMITS = {1, 100};
const std::pair<int, int> SCENE_SCALE_LIMITS = {1, 500};

/**
 * @brief A custom QGraphicsScene that's used to
 * display game objects on the gameboard.
 */
class GameScene : public QGraphicsScene
{
    Q_OBJECT

public:

    /**
     * @brief Constructor for the class.
     *
     * @param qt_parent points to the parent object per Qt's parent-child-system.
     * @param width in tiles for the game map.
     * @param height in tiles for the game map.
     * @param scale is the size in pixels of a single square tile.
     *
     * @pre 0 < width <= 100 && 0 < height <= 100 && 0 < scale <= 500. Otherwise
     * default values are used for the created object.
     */
    GameScene(QWidget* qt_parent = nullptr,
                    int width = 10,
                    int height = 10,
                    int scale = 50
            );

    /** Default destructor **/
    ~GameScene() = default;

    /** Set the scene size
     * @param width - one tile width
     * @param height - one tile height **/
    void setSize(int width, int height);

    /** Set the scene scale
     * @param scale - The scale value **/
    void setScale(int scale);

    /** Resize the scene **/
    void resize();

    /** Draw an item to the gameboard. Object can be a tile or a building.
     * @param obj - object to be drawn
     * @param workers - workers on the tile
     * @note this is called upon game initialization and during runtime,
     * when player sends workers to activities on map. **/
    void drawItem( std::shared_ptr<Course::GameObject> obj, int workers);

    /** Handles the scene events
     * @param event - scene event **/
    virtual bool event(QEvent* event) override;

    /** Sets the current turn holder
     * @param player - a player object **/
    void turn(std::shared_ptr<Course::PlayerBase> player);

    /** Sets the object manager
     * @param - Pointer to the object manager **/
    void setObjectManager(std::shared_ptr<Course::iObjectManager> obj_m);

    /** Gets the information from a popup
     * @param building_type - type of a building player wants to build
     * @note Sets the buying mode to true (to enable updating the map) **/
    void Button_pressed(std::string building_type);

    /** Open a popup when a mouseclick event happens
     * @param tile - a tile object that determines which kind of popup opens **/
    void open_dialogue(std::shared_ptr<Course::TileBase> tile);

    /** Emits to mapwindow to update the interface texts **/
    void updateStats();

    /** Disables the gamescene
     * @note Is called after the game is over **/
    void disable_game_board();

public slots:

    /** Sends the workers to activities and updates the scene images
     * @param tile - the tile where the worker is going to
     * @param worker_type - the type of the worker
     * */
    void get_tile_and_worker_type(std::shared_ptr<Course::TileBase> tile,
                                  std::string worker_type );

    /** Getter of the worker type player has bought in the popup-dialog
     * @param worker_type - the type of the worker **/
    void get_bought_worker_type();

signals:

    void objectPlaced();
    void changeTexts();

private:

    QGraphicsItem* m_mapBoundRect;
    int m_width;
    int m_height;
    int m_scale;

    bool game_over;

    bool buying_mode;
    std::string building_type_;
    std::shared_ptr<Course::PlayerBase> current_player;
    std::shared_ptr<Course::iObjectManager> object_manager_;
};

}
#endif // GAMESCENE_HH
