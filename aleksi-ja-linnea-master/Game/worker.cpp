#include "worker.h"
#include "workerbase_s.h"
namespace Student{
worker::worker(const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
               const std::shared_ptr<Course::iObjectManager> &objectmanager,
               const std::shared_ptr<Course::PlayerBase> &owner,
               const int &tilespaces,
               const Course::ResourceMap &cost,
               const Course::ResourceMapDouble &efficiency):

    WorkerBase_S(eventhandler,

                       objectmanager,
                       owner,
                       tilespaces,
                       cost,
                       efficiency)
{


    update_status("available", nullptr);

}

worker::~worker()
{

}

std::string worker::getType() const
{
    return "Worker";
}



}
