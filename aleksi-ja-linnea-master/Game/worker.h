#ifndef WORKER_H
#define WORKER_H
#include <string>
#include "interfaces/igameeventhandler.h"
#include "tiles/tilebase.h"
#include "student_resourcemaps.h"
#include "workerbase_s.h"
#include <string>


namespace Student{

class worker : public WorkerBase_S
{
public:
    /**
    * @brief Default constructor of class worker
    * @param eventhandler The GameEventHandler of the game
    * @param objectmanager The ObjectManager of the game
    * @param owner The owner of the worker
    * @param tilespaces The amount of tilespaces the worker
    * occupies, default set to 1
    * @param cost The cost of recruiting a worker,
    * default set to StudentResourcemaps::WORKER_RECRUITMENT_COST
    * @param efficiency The efficiency of the worker,
    * default set to StudentRecoursemaps::WORKER_EFFICIENSY
    */
    worker(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& cost =

                Student::StudentResourcemaps::WORKER_RECRUITMENT_COST,
            const Course::ResourceMapDouble& efficiency =
                Student::StudentResourcemaps::WORKER_EFFICIENCY
            );
    /**
    * @brief Default destructor of class worker
    */
    ~worker();
    /**
     * @brief Returns the type of the worker
     * @return Worker
     */
    virtual std::string getType() const override; 

};
}


#endif // WORKER_H
