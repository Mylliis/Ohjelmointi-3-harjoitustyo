#ifndef GAMEEVENTHANDLER_HH
#define GAMEEVENTHANDLER_HH
#include "interfaces/igameeventhandler.h"
#include "core/worldgenerator.h"
#include "mapwindow.hh"
#include "interfaces/iobjectmanager.h"

#include "player.hh"

#include "worker.h"

namespace Student{


struct worker_and_locale{

    std::shared_ptr<Course::WorkerBase> worker;
    std::shared_ptr<Course::TileBase> tile;
    int rounds_left;

};

/** @brief Handles all the game-related events, controls
 * worker actions and buying properties.
 * */
class GameEventHandler : public Course::iGameEventHandler
{

public:
    /**
    * @brief Default constructor of class GameEventHandler
    */
    GameEventHandler();

    /**
    * @brief Default destructor of class GameEventHandler
    */
    ~GameEventHandler();

    /**
     * @brief Modify a single players resource by
     * set value.
     * @param player The player of whom resources are going to be modified
     * @param resource The resource to be modified
     * @param amount amount that the resource is to be modified
     */
    virtual bool modifyResource(std::shared_ptr<Course::PlayerBase> player,
                                Course::BasicResource resource,
                                int amount) ;

    /**
     * @brief Modify multiple resources at once
     * @param player The player of whom resources are going to be modified
     * @param resources Resoursemap of the to be modified resources
     */
    virtual bool modifyResources(std::shared_ptr<Course::PlayerBase> player,
                                 Course::ResourceMap resources);
    /**
     * @brief Updates the rounds on work, when turn shifts
     * and updates the resources from work made.
     */
    void update_rounds_on_work();

    /**
     * @brief Start workers working
     * @param worker_going_work The worker going to work
     * @param tile The tile where worker is going
     */
    void start_working(std::shared_ptr<Course::WorkerBase> worker_going_work,
                       std::shared_ptr<Course::TileBase> tile);

    /**
     * @brief Adds a new worker to databases
     * @param worker_to_add The worker to be added
     * @param player The player who owns the worker
     * @param tile The tile where worker is going to be located
     */
    void add_worker(std::shared_ptr<Course::WorkerBase> worker_to_add,
                    std::shared_ptr<Course::PlayerBase> player,
                    std::shared_ptr<Course::TileBase> tile);

    /**
     * @brief Just gives the scene to GameEventHandler
     * @param scene The scene to give
     */
    void giveScene(Student::GameScene* scene);

    /**
     * @brief Shift the turn and set the current active player
     * @param player The player whitch turn is next
     * @param round The count of the round
     * @post Exception guarantee: No-throw
     */
    void turn(std::shared_ptr<Course::PlayerBase> player, int round);

    /**
     * @brief Returns the current player
     */
    std::shared_ptr<Course::PlayerBase> get_current_player();

    /**
     * @brief Opens the dialogue on the tile
     * @param tile The tile where dialogue is wanted to
     * be opened
     */
    void open_dialogue(std::shared_ptr<Course::TileBase> tile);

    /**
     * @brief The functionality of buying and
     * managing properties
     * @param tile The tile managed
     * @param building_type The type of building managed
     */
    void buy_and_manage_properties( std::shared_ptr<Course::TileBase> tile,
                                    std::string building_type);

    /**
     * @brief Buys a worker and bills it from the players resources
     * @param geh The GameEventHandler class
     * @param mngr The ObjectManager class
     * @param tile The tile where worker is set to go after purchase
     */
    void buy_worker(int type, std::shared_ptr<Course::iGameEventHandler> geh,
                    std::shared_ptr<Course::iObjectManager> mngr,
                    std::shared_ptr<Course::TileBase> tile);

    /**
     * @brief Sends a free worker to work to some other tile
     * @param tile The tile where worker is needed
     * @param worker_type the type of worker needed
     */
    void send_worker_to_activity(std::shared_ptr<Course::TileBase> tile,
                                 std::string worker_type );


private:
    //The databases used by GameEventHandler

    std::map<std::shared_ptr<Course::PlayerBase>,std::vector<worker_and_locale>> workers_;
    std::pair<std::shared_ptr<Course::PlayerBase>,int> turn_;
    Student::GameScene* scene_;

};
}
#endif // GAMEEVENTHANDLER_HH
