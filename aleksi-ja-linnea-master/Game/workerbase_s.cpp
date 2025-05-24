#include "workerbase_s.h"
namespace Student{
WorkerBase_S::WorkerBase_S(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
                           const std::shared_ptr<Course::iObjectManager> &objectmanager,
                           const std::shared_ptr<Course::PlayerBase> &owner,
                           const int &tilespaces,
                           const Course::ResourceMap &cost,
                           const Course::ResourceMapDouble &efficiency):
    Course::WorkerBase(eventhandler,
                       objectmanager,
                       owner,
                       tilespaces,
                       cost,
                       efficiency)
{

}

void WorkerBase_S::update_status(std::string status, std::shared_ptr<Course::TileBase> tile)
{
    worker_status_ = status;
    worker_at_tile_ = tile;

}

void WorkerBase_S::set_unavailable_rounds(int rounds){

    rounds_unavailable = rounds;
}

void WorkerBase_S::update_rounds_unavailability(){

    rounds_unavailable -= 1;
}

int WorkerBase_S::return_remaining_unavailability_rounds(){

    return rounds_unavailable;
}

void WorkerBase_S::doSpecialAction()
{
    return;
}

std::string WorkerBase_S::getType() const
{
    return "workerbase_s";
}

std::string WorkerBase_S::get_status()
{
    return worker_status_;
}

std::shared_ptr<Course::TileBase> WorkerBase_S::get_tile_where_worker_is_at()
{
    return worker_at_tile_;
}

void WorkerBase_S::fetch_worker_home()
{
    worker_at_tile_ = nullptr;
}


}
