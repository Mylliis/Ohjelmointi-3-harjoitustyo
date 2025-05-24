#include "mapwindow.hh"
#include "ui_mapwindow.h"

#include "stone.h"
#include "berrybush.h"
#include "mapitem.hh"
#include "forest_s.h"
#include "grassland_s.h"
#include "watertile.h"
#include <QMessageBox>
#include <ctime>

MapWindow::MapWindow(QWidget *parent,
                     std::shared_ptr<Student::GameEventHandler> handler):
    QMainWindow(parent),
    m_ui(new Ui::MapWindow),
    m_GEHandler(handler),
    m_simplescene(new Student::GameScene(this))
{

    m_ui->setupUi(this);
    this->setWindowTitle("Pirkanmaa Conquest - 2019");

    Starting_screen *dialog = new Starting_screen(this);
    connect(dialog, &Starting_screen::sendValue, this,
            &MapWindow::get_starting_screen_info);
    dialog->exec();

    Student::GameScene* sgs_rawptr = m_simplescene.get();

    m_ui->graphicsView->setScene(dynamic_cast<QGraphicsScene*>(sgs_rawptr));
    m_ui->graphicsView->setAlignment(Qt::AlignCenter);
    m_ui->game_over_lbl->setVisible(false);

    // Signals and slots
    connect(m_simplescene.get(), SIGNAL (objectPlaced()), this,
            SLOT (updateGraphicsView()));
    connect(m_simplescene.get(), SIGNAL(changeTexts()), this,
            SLOT (updateResourceTexts()));

    // Set the game-event handler
    std::shared_ptr<Student::GameEventHandler> geHandler =
            std::make_shared<Student::GameEventHandler>();

    setGEHandler(geHandler);

    // Set object manager
    m_objmgr = std::make_shared<Student::ObjectManager>();
    m_simplescene->setObjectManager(m_objmgr);


    // All the tiles used in the game
    Course::WorldGenerator::getInstance().addConstructor<Student::Grassland_S>(5);
    Course::WorldGenerator::getInstance().addConstructor<Student::Forest_S>(4);
    Course::WorldGenerator::getInstance().addConstructor<Student::stone>(3);
    Course::WorldGenerator::getInstance().addConstructor<Student::watertile>(2);
    Course::WorldGenerator::getInstance().addConstructor<Student::berrybush>(1);


    // Generate the map for the game, with a randomized seed 0-10
    srand(time(NULL));
    int seed = rand() % 11;
    Course::WorldGenerator::getInstance().generateMap(map_size_width,
                                                      map_size_height, seed,
                                                    m_objmgr, m_GEHandler);
    m_objmgr->DrawMap(m_simplescene);

    // Count the total conquerable tiles of the map
    total_tiles = 0;
    for(auto tile : m_objmgr->get_world_tiles()){
        if( tile->getType() != "berrybush" ){
            total_tiles += 1;
        }
    }

    m_ui->total_tiles_lbl->setText(QString::number(total_tiles));

    // Set up the players
    construct_playerbase();

    // Interface modification
    QPalette palette;
    palette.setBrush(QPalette::Background, Qt::lightGray);
    this->setPalette(palette);

    // Adjust the settings for a new game
    current_round = 0;
    current_turn_holder = player_1;
    m_GEHandler->turn(current_turn_holder,current_round);
    m_GEHandler->giveScene(m_simplescene.get());
    change_turn();

}

MapWindow::~MapWindow()
{
    delete m_ui;
}

void MapWindow::setGEHandler(
        std::shared_ptr<Student::GameEventHandler> nHandler)
{
    m_GEHandler = nHandler;
}

void MapWindow::drawItem( std::shared_ptr<Course::GameObject> obj)
{
    m_simplescene->drawItem(obj, 0);
}

void MapWindow::construct_playerbase(){

    player_1 = std::make_shared<Student::Player>(player_1_name, player_1_objects);
    player_2 = std::make_shared<Student::Player>(player_2_name, player_2_objects);

    // Hard-coded values
    player_1->set_color("RED");
    player_2->set_color("BLUE");

    // Create player 1 HQ and conquer the land beneath it
    std::shared_ptr<Course::HeadQuarters> player1_HQ =
            std::make_shared<Course::HeadQuarters>(m_GEHandler, m_objmgr, player_1);

    Course::Coordinate HQ_coord = Course::Coordinate(0,map_size_height-1);

    std::shared_ptr<Course::TileBase> tile = m_objmgr->getTile(HQ_coord);

    tile->addBuilding(player1_HQ);
    tile->setOwner(player_1);
    player_1->add_to_claimed_tiles();
    player_1->addObject(player1_HQ);
    m_objmgr->AddBuilding(player1_HQ);
    m_simplescene->turn(player_1);
    drawItem(player1_HQ);

    // Create player 2 HQ and conquer the land beneath it
    std::shared_ptr<Course::HeadQuarters> player2_HQ =
            std::make_shared<Course::HeadQuarters>(m_GEHandler, m_objmgr, player_2);

    Course::Coordinate HQ_coord_2 = Course::Coordinate(map_size_width-1,0);
    std::shared_ptr<Course::TileBase> tile_2 = m_objmgr->getTile(HQ_coord_2);

    tile_2->addBuilding(player2_HQ);
    tile_2->setOwner(player_2);
    player_2->addObject(player2_HQ);
    player_2->add_to_claimed_tiles();
    m_objmgr->AddBuilding(player2_HQ);
    m_simplescene->turn(player_2);
    drawItem(player2_HQ);


}


void MapWindow::get_starting_screen_info(QString player_1, QString player_2)
{

    player_1_name = player_1.toStdString();
    player_2_name = player_2.toStdString();

}


void MapWindow::change_turn(){

    // Change the turn holder
    if (current_round > 0){
        if (current_turn_holder == player_1){
            current_turn_holder = player_2;
        }
        else{
            current_turn_holder = player_1;
        }
    }

    // Change the interface texts to fit the current player
    set_resource_texts(current_turn_holder->getName());

    turn_message = QString::fromStdString(current_turn_holder->getName())
            + ", make your move!";

    m_ui->whoseMove_label->setText(turn_message);

    current_round += 1;

    // Notify GE handler and GameScene about the turn change.
    m_GEHandler->turn(current_turn_holder,current_round);
    m_simplescene->turn(current_turn_holder);

    QString current_round_message = QString("ROUND ")
            + QString::number(current_round);

    m_ui->currentRound_label->setText(current_round_message);

}

bool MapWindow::check_if_game_over(){

    //  Both of the players have conquered half of the total claimable tiles,
    //  which results in a tie.
    if(current_turn_holder->get_claimed_tiles_amt() == (total_tiles/2))
    {
        if(player_2->get_claimed_tiles_amt() == (total_tiles/2))
        {
            QMessageBox msgBox;
            msgBox.setStyleSheet("background-color: #550000; color: #e5bd1b;");
            msgBox.setWindowTitle("GAME OVER");

            QString win_message = "It's a tie between " +
                    QString::fromStdString(player_1_name) +
                    " and " + QString::fromStdString(player_2_name) + "!!";

            msgBox.setText(win_message);
            msgBox.exec();
            return true;
        }

    }

    // Current player has more than half of the tiles, so they win the game.
    else if(current_turn_holder->get_claimed_tiles_amt() > (total_tiles/2))
    {
        QMessageBox msgBox;
        msgBox.setStyleSheet("background-color: #550000; color: #e5bd1b;");
        msgBox.setWindowTitle("GAME OVER");

        QString win_message = QString::fromStdString(current_turn_holder->getName())
                    + " wins the game!";

        msgBox.setText(win_message);
        msgBox.exec();
        return true;

    }

    // Game is not over yet.
        return false;
}



std::shared_ptr<Student::Player> MapWindow::get_current_player(){

    return current_turn_holder;
}

void MapWindow::set_resource_texts(std::string player_name){

    Course::ResourceMap player_resources;

    if (player_1->getName() == player_name){
        player_resources = player_1->getResources();

    }
    else {
       player_resources = player_2->getResources();

    }

    // Get a vector of the current player's workers
    std::vector<std::shared_ptr<Course::WorkerBase>> workers =
            current_turn_holder->getWorkers();

    std::map<std::string, int> properties = current_turn_holder->
            get_total_properties();

    int player_miners = 0;
    int player_workers = 0;
    int available_miners = 0;
    int available_workers = 0;

    // Goes through the player's workers and checks their types and
    // availabilities.
    for(auto workertype : workers){
        std::shared_ptr<Student::WorkerBase_S> worker =
                std::dynamic_pointer_cast<Student::WorkerBase_S>(workertype);

        if(worker->getType() == "Miner"){
            player_miners += 1;

            if(worker->get_status() == "available"){
                available_miners += 1;
            }
        }
        else if(worker->getType() == "Worker"){
            player_workers += 1;

            if(worker->get_status() == "available"){
                available_workers += 1;
            }
        }
    }

    // Set the interface texts
    m_ui->gold_label->setText(QString::number(player_resources.at
                                              (Course::BasicResource::MONEY)));
    m_ui->food_label->setText(QString::number(player_resources.at
                                              (Course::BasicResource::FOOD)));
    m_ui->wood_label->setText(QString::number(player_resources.at
                                              (Course::BasicResource::WOOD)));
    m_ui->ore_label->setText(QString::number(player_resources.at
                                             (Course::BasicResource::ORE)));
    m_ui->stone_label->setText(QString::number(player_resources.at
                                               (Course::BasicResource::STONE)));

    m_ui->claimed_tiles_lbl->setText(QString::number(current_turn_holder->
                                                     get_claimed_tiles_amt()));

    m_ui->houses_amt_label->setText(QString::number(properties.at("House")));
    m_ui->docks_amt_label->setText(QString::number(properties.at("Dock")));
    m_ui->mines_amt_label->setText(QString::number(properties.at("Mine")));

    m_ui->total_miners_lbl->setText(QString::number(player_miners));
    m_ui->total_workers_lbl->setText(QString::number(player_workers));
    m_ui->available_miners_lbl->setText(QString::number(available_miners));
    m_ui->available_workers_lbl->setText(QString::number(available_workers));


}

void MapWindow::on_end_mv_btn_clicked()
{

   // If player has workers on a tile, update their progress
   m_GEHandler->update_rounds_on_work();
   change_turn();

}

void MapWindow::updateGraphicsView()
{
    m_ui->graphicsView->update();
}

void MapWindow::updateResourceTexts()
{
    bool over = check_if_game_over();
    set_resource_texts(current_turn_holder->getName());

    // Disable the gamescene and the buttons if game is over.
    if (over){
        m_simplescene->disable_game_board();
        m_ui->add_building_btn->setDisabled(true);
        m_ui->end_mv_btn->setDisabled(true);
        m_ui->game_over_lbl->setVisible(true);
    }
}

std::shared_ptr<Student::GameEventHandler> MapWindow::get_ge_handler()
{
    return m_GEHandler;
}

void MapWindow::on_add_building_btn_clicked()
{
    add_building_dialog *dialog_2 =
            new add_building_dialog(current_turn_holder->getResources());

    connect(dialog_2, &add_building_dialog::sendValue_2,
            this, &MapWindow::build_type);

    dialog_2->exec();
}

void MapWindow::build_type(QString type){

    std::string building_type = type.toStdString();
    m_simplescene->Button_pressed(building_type);

}
