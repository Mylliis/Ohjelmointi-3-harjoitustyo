#ifndef WORKERBASE_S_H
#define WORKERBASE_S_H
#include "interfaces/igameeventhandler.h"
#include "workers/workerbase.h"
#include "tiles/tilebase.h"

namespace Student{


class WorkerBase_S:public Course::WorkerBase
{
public:
    WorkerBase_S(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                 const std::shared_ptr<Course::iObjectManager>& objectmanager,
                 const std::shared_ptr<Course::PlayerBase>& owner,
                 const int& tilespaces = 1,
                 const Course::ResourceMap& cost = {},
                 const Course::ResourceMapDouble& efficiency = {});
    /**
     * @brief Updates the status of
     * a worker derived from this base-class.
     * @param status new status to worker
     * @param tile where worker is
     */
    virtual void update_status(std::string status, std::shared_ptr<Course::TileBase> tile) final;
    /**
     * @brief Special action of worker,
     * does nothing but it was mandatory to
     * make so this would not be a abstract class.
     */
    virtual void doSpecialAction() override;
    /**
     * @brief Gets the type of the class
     * @return workerbase_s
     */
    virtual std::string getType() const override;
    /**
     * @brief returns the status of workerbase
     * derived worker.
     */
    virtual std::string get_status() final;
    /**
     * @brief Returns the tile where the workerbase
     * derived worker is at
     */
    virtual std::shared_ptr<Course::TileBase> get_tile_where_worker_is_at();
    /**
     * @brief Gets the worker back from the tile
     * to "home"
     */
    void fetch_worker_home();
    /**
     * @brief Gets the remaining unavailability
     * rounds of the worker
     */
    int return_remaining_unavailability_rounds();
    /**
     * @brief Updates unavailability rounds
     * when turn shifts
     */
    void update_rounds_unavailability();
    /**
     * @brief Set workers unavailability rounds.
     * @param rounds the rounds that is
     * wanted that the worker is unavailable
     */
    void set_unavailable_rounds(int rounds);


private:

    int rounds_unavailable;
    std::string worker_status_;
    std::shared_ptr<Course::TileBase> worker_at_tile_;
};
}
#endif // WORKERBASE_S_H
