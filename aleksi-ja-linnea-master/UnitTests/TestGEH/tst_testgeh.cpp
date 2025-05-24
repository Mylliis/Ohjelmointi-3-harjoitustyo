#include <QtTest>
#include "core/coordinate.h"
#include "gameeventhandler.cpp"
#include "grassland_s.h"

// add necessary includes here

class TestGEH_and_OBJMGR : public QObject
{
    Q_OBJECT

public:
    TestGEH_and_OBJMGR();
    ~TestGEH_and_OBJMGR();

private slots:
    void test_modifyresource();
    void test_modifyresources();
    void test_add_worker();
    void test_turn_and_current_player();
    void test_buy_worker();
    void test_start_working();
    void test_update_rounds_on_work();
    void test_send_worker_to_activity();
    /*Objectmanager tests
    */
    void test_getTiles();
    void test_getTile1();
    void test_getTile2();
    void add_tiles_and_get_world_tiles();
private:
std::shared_ptr<Student::GameEventHandler> geh_;
std::shared_ptr<Student::ObjectManager> objm_;
std::shared_ptr<Student::Player> player_;
std::shared_ptr<Student::worker> worker_;
std::shared_ptr<Student::miner> miner_;
std::shared_ptr<Student::Grassland_S> grasstile_;
std::shared_ptr<Student::Grassland_S> grasstile_2;
};

TestGEH_and_OBJMGR::TestGEH_and_OBJMGR()
{
 geh_ = std::make_shared<Student::GameEventHandler>();
 objm_ = std::make_shared<Student::ObjectManager>();
 player_ = std::make_shared<Student::Player>("testplayer");
 worker_ = std::make_shared<Student::worker>(geh_,objm_,player_);
 Course::Coordinate xy_(1,1);
 Course::Coordinate xy2_(1,2);
 grasstile_ = std::make_shared<Student::Grassland_S>(xy_,geh_,objm_);
 grasstile_2 = std::make_shared<Student::Grassland_S>(xy2_,geh_,objm_);
}

TestGEH_and_OBJMGR::~TestGEH_and_OBJMGR()
{

}
/*Test modifyResource, modifyResources*/

void TestGEH_and_OBJMGR::test_modifyresource(){

geh_->modifyResource(player_,Course::BasicResource::MONEY,-5);
Course::ResourceMap testmap2={
    {Course::BasicResource::MONEY, 495},
    {Course::BasicResource::FOOD, 200},
    {Course::BasicResource::WOOD, 300},
    {Course::BasicResource::STONE, 300},
    {Course::BasicResource::ORE, 0}
};
QVERIFY(player_->getResources()==testmap2);
}void TestGEH_and_OBJMGR::test_modifyresources(){

Course::ResourceMap minusmap={
    {Course::BasicResource::MONEY, -5},
    {Course::BasicResource::FOOD, -5},
    {Course::BasicResource::WOOD, -5},
    {Course::BasicResource::STONE, -5},
    {Course::BasicResource::ORE, 0}
};
Course::ResourceMap testmap3={
    {Course::BasicResource::MONEY, 490},
    {Course::BasicResource::FOOD, 195},
    {Course::BasicResource::WOOD, 295},
    {Course::BasicResource::STONE, 295},
    {Course::BasicResource::ORE, 0}
};
geh_->modifyResources(player_,minusmap);
QVERIFY(player_->getResources() == testmap3);
}

void TestGEH_and_OBJMGR::test_add_worker()
{
    geh_->add_worker(worker_,player_,grasstile_);
    QVERIFY(player_->getWorkers().at(0)==worker_);
}

void TestGEH_and_OBJMGR::test_turn_and_current_player()
{
    geh_->turn(player_,1);
    QVERIFY(geh_->get_current_player()==player_);
}

void TestGEH_and_OBJMGR::test_buy_worker()
{
    geh_->buy_worker(1,geh_,objm_,grasstile_);
    QVERIFY(player_->getWorkers().size()==2);
}

void TestGEH_and_OBJMGR::test_start_working()
{
    geh_->start_working(worker_,grasstile_);
    QVERIFY(worker_->get_status()=="unavailable");
}

void TestGEH_and_OBJMGR::test_update_rounds_on_work()
{   int before=worker_->return_remaining_unavailability_rounds();
    geh_->update_rounds_on_work();
    int after =worker_->return_remaining_unavailability_rounds();
    QVERIFY(before>after);
}

void TestGEH_and_OBJMGR::test_send_worker_to_activity()
{/*
   std::shared_ptr<Student::worker> testworker_
            = std::make_shared<Student::worker>(geh_,objm_,player_);
    geh_->add_worker(worker_,player_,grasstile_2);
    geh_->turn(player_,1);
    Course::Coordinate xy3(2,1);
    std::shared_ptr<Student::Grassland_S> testtile
            = std::make_shared<Student::Grassland_S>(xy3,geh_,objm_);

geh_->send_worker_to_activity(testtile,"Worker");*/

}

void TestGEH_and_OBJMGR::test_getTiles()
{const std::vector<std::shared_ptr<Course::TileBase>> tilevektor_
            ={grasstile_,grasstile_2};
    objm_->addTiles(tilevektor_);
    Course::Coordinate cord1 = grasstile_->getCoordinate();
    Course::Coordinate cord2 = grasstile_2->getCoordinate();
    const std::vector<Course::Coordinate> coordinatevector_
            ={cord1,cord2};
    std::vector<std::shared_ptr<Course::TileBase>> tiles_gotten=
            objm_->getTiles(coordinatevector_);
    QVERIFY(tiles_gotten.size()>0);

}

void TestGEH_and_OBJMGR::test_getTile1()
{
    std::vector<std::shared_ptr<Course::TileBase>> tilevektor_
                ={grasstile_,grasstile_2};
    objm_->addTiles(tilevektor_);
    const Course::ObjectId id = grasstile_->ID;

    QVERIFY(objm_->getTile(id)==grasstile_);
}

void TestGEH_and_OBJMGR::test_getTile2()
{
    std::vector<std::shared_ptr<Course::TileBase>> tilevektor_
                ={grasstile_,grasstile_2};
    objm_->addTiles(tilevektor_);
    const Course::Coordinate cord = grasstile_->getCoordinate();
    QVERIFY(objm_->getTile(cord)==grasstile_);

}

void TestGEH_and_OBJMGR::add_tiles_and_get_world_tiles()
{
    std::vector<std::shared_ptr<Course::TileBase>> tilevektor_
                ={grasstile_,grasstile_2};
    objm_->addTiles(tilevektor_);
    QVERIFY(objm_->get_world_tiles().at(0)==grasstile_ &&
            objm_->get_world_tiles().at(1)==grasstile_2);
}



QTEST_MAIN(TestGEH_and_OBJMGR)
#include "tst_testgeh.moc"
