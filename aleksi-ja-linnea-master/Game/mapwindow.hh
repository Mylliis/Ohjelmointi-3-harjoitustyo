#ifndef MAPWINDOW_HH
#define MAPWINDOW_HH

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "workerbase_s.h"
#include "interfaces/igameeventhandler.h"
#include "graphics/simplegamescene.h"
#include "graphics/simplemapitem.h"
#include "gamescene.hh"
#include "core/worldgenerator.h"
#include "core/gameobject.h"

#include "gameeventhandler.hh"
#include "core/playerbase.h"
#include "player.hh"

#include "buildings/headquarters.h"
#include "core/coordinate.h"
#include "tiles/grassland.h"
#include "tiles/forest.h"

#include "student_resourcemaps.h"

#include "starting_screen.hh"
#include "add_building_dialog.hh"

#include <math.h>
#include <string>
#include <map>
#include <QString>
#include "objectmanager.hh"

// Forward declarations
namespace Student{
class PlayerBase;
class Player;
class ObjectManager;
class GameEventHandler;
}

namespace Ui{
class MapWindow;
}

/** @brief
 * The main window of the game, constructs the players and maintains
 * the game's progress.
 * */
class MapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MapWindow(QWidget *parent = 0,
                       std::shared_ptr<Student::GameEventHandler> GEHandler = {}
                       );

    /** Default destructor. */
    ~MapWindow();

    /** Set the game-event handler
    @param nHandler - Game-event handler to be set
    */
    void setGEHandler(std::shared_ptr<Student::GameEventHandler> nHandler);

    /** Calls out to QGraphicsScene to add items to it
    @param obj - Object to be added to the scene
    */
    void drawItem( std::shared_ptr<Course::GameObject> obj);

    /** Grabs the player names given in the starting screen. Signal
     * from the starting screen is emitted to this.
     * @param player_1 - Player 1 name
     * @param player_2 - Player 2 name
     * @note If players leave the names blank, they will be by default "Player 1" and "Player 2".
     * */
    void get_starting_screen_info(QString player_1, QString player_2);

    /** Sets up both of the players.
     * */
    void construct_playerbase();

    /** Sets the player names to the corresponding class attributes **/
    void set_player_names();

    /** Sets the interface text to show current players info
     * @param player_name - Current players name
     * **/
    void set_resource_texts(std::string player_name);

    /** Checks if the game is over and disables the interface
    @return True if game is over, False if it's not over **/
    bool check_if_game_over();

    //
    // Getters
    //

    /** Getter for the game-event handler
    @return A pointer to the game-event handler **/
    std::shared_ptr<Student::GameEventHandler> get_ge_handler();

    /** Getter for the current player
    @return A pointer to the current player **/
    std::shared_ptr<Student::Player> get_current_player();


public slots:

    void build_type(QString type);

private slots:

    void on_end_mv_btn_clicked();
    void updateGraphicsView();
    void updateResourceTexts();
    void on_add_building_btn_clicked();

private:

    /** Changes the turn after player wants to hand the turn over.
     * Resets some of the texts in the interface. */
    void change_turn();


    Ui::MapWindow* m_ui;

    // The players
    std::shared_ptr<Student::Player> player_1 = nullptr;
    std::shared_ptr<Student::Player> player_2 = nullptr;

    std::shared_ptr<Student::GameEventHandler> m_GEHandler = nullptr;
    std::shared_ptr<Student::GameScene> m_simplescene = nullptr;
    std::shared_ptr<Student::ObjectManager> m_objmgr = nullptr;

    std::vector<std::shared_ptr<Course::GameObject>> world_objects;
    std::shared_ptr<Student::Player> current_turn_holder = nullptr;
    std::vector<std::shared_ptr<Course::GameObject>> player_1_objects;
    std::vector<std::shared_ptr<Course::GameObject>> player_2_objects;

    std::string player_1_name = "Player 1";
    std::string player_2_name = "Player 2";

    QString turn_message;

    int current_round;
    int map_size_width = 10;
    int map_size_height = 10;
    int total_tiles;



};

#endif // MapWINDOW_HH

