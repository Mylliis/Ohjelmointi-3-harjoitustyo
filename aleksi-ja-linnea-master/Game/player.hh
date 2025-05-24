#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>
#include <map>
#include <vector>
#include <memory>
#include "core/gameobject.h"
#include "core/resourcemaps.h"
#include "core/playerbase.h"
#include "workers/workerbase.h"
#include "gameeventhandler.hh"

namespace Student{
class Player : public Course::PlayerBase
{
public:
    /**
     * @brief Default constructor
     * @param name The name of the player
     * @param objects The objects player has,
     * default set to none
     */
    Player(const std::string& name,
               const std::vector<std::shared_ptr<Course::GameObject> > objects ={});

    /**
     * @brief Default destructor
     */
    ~Player() = default;

    /**
     * @brief set the starting resources of the player
     * @param resources A vector of the resource values
     */
    void setStartingResources(std::vector<int> resources);

    /**
     * @brief Returns the resources of the player
     */
    Course::ResourceMap getResources();

    /**
     * @brief Modifies one resource of the player
     * @param resource The resource to be modified
     * @param amount The amound to be modified
     */
    void modify_resource(Course::BasicResource resource,
                         int amount);

    /**
     * @brief Modify multiple resources of the player
     * @param resources A resourcemap of the resources
     * to be modified
     */
    void modify_resources(Course::ResourceMap resources);

    /**
     * @brief Get the workers of the player
     */
    std::vector<std::shared_ptr<Course::WorkerBase>> getWorkers();

    /**
     * @brief Adds a worker or a miner to the player
     * @param worker_to_add The worker or miner to be added
     */
    void add_worker_miner(std::shared_ptr<Course::WorkerBase> worker_to_add);

    /**
     * @brief Get the colour of the player
     */
    std::string get_color();

    /**
     * @brief Set the colour of the player
     * @param color The colour to be set
     */
    void set_color(std::string color);

    /**
     * @brief Add one of a type to the total properties
     * @param type The type of the property to be added
     */
    void add_to_total_properties(std::string type);

    /**
     * @brief Returns the total properties of the player
     */
    std::map<std::string, int> get_total_properties();

    /**
     * @brief Player has updated hq
     */
    void upgraded_hq();

    /**
     * @brief Add one to the claimed tiles
     */
    void add_to_claimed_tiles();

    /**
     * @brief Get the amount of the claimed tiles of the player
     */
    int get_claimed_tiles_amt();

private:

    std::string m_name;
    std::string player_color;
    int claimed_tiles;
    std::map<std::string, int> total_properties;
    std::vector<std::weak_ptr<Course::GameObject> > m_objects;
    std::vector<std::shared_ptr<Course::WorkerBase>> workers_;
    Course::ResourceMap player_resources_;
    bool has_upgraded_hq;


};

}
#endif // PLAYER_HH
