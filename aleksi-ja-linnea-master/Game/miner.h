#ifndef MINER_H
#define MINER_H
#include "workerbase_s.h"
#include "student_resourcemaps.h"

namespace Student{
class miner:public WorkerBase_S
{
public:
    /**
    * @brief Default constructor of class miner
    * @param eventhandler The GameEventHandler of the game
    * @param objectmanager The ObjectManager of the game
    * @param owner The owner of the miner
    * @param tilespaces The amount of tilespaces the miner
    * occupies, default set to 1
    * @param cost The cost of recruiting a miner,
    * default set to StudentResourcemaps::MINER_RECRUITMENT_COST
    * @param efficiency The efficiency of the miner,
    * default set to StudentRecoursemaps::MINER_EFFICIENSY
    */
    miner(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
          const std::shared_ptr<Course::iObjectManager>& objectmanager,
          const std::shared_ptr<Course::PlayerBase>& owner,
          const int& tilespaces = 1,
          const Course::ResourceMap& cost =
              Student::StudentResourcemaps::MINER_RECRUITMENT_COST,
          const Course::ResourceMapDouble& efficiency =
              Student::StudentResourcemaps::MINER_EFFICIENCY);
    /**
    * @brief Default destructor of class miner
    */
    ~miner();

    /**
    * @brief Returns the type of the worker
    * @return Miner
    */
    virtual std::string getType() const override;
};
}
#endif // MINER_H
