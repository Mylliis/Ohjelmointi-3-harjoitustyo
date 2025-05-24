#ifndef STUDENT_RESOURCEMAPS_H
#define STUDENT_RESOURCEMAPS_H
#include "core/basicresources.h"

namespace Student{

namespace StudentResourcemaps{

const Course::ResourceMap EMPTY = {};

// For dev only
const Course::ResourceMap GOD_RESOURCES={
    {Course::BasicResource::MONEY, 5000},
    {Course::BasicResource::FOOD, 5000},
    {Course::BasicResource::WOOD, 5000},
    {Course::BasicResource::STONE, 5000},
    {Course::BasicResource::ORE, 5000}
};

const Course::ResourceMap PLAYER_STARTING_RESOURCES={
    {Course::BasicResource::MONEY, 500},
    {Course::BasicResource::FOOD, 200},
    {Course::BasicResource::WOOD, 300},
    {Course::BasicResource::STONE, 300},
    {Course::BasicResource::ORE, 0}
};

const Course::ResourceMap BERRYBUSHBP={
    {Course::BasicResource::FOOD, 2}
};

const Course::ResourceMapDouble WORKER_EFFICIENCY = {
    {Course::BasicResource::MONEY, 0.25},
    {Course::BasicResource::FOOD, 1.00},
    {Course::BasicResource::WOOD, 0.75},
    {Course::BasicResource::STONE, 0.50},
    {Course::BasicResource::ORE, 0.50}
};
const Course::ResourceMapDouble MINER_EFFICIENCY={
    {Course::BasicResource::MONEY, 0.35},
    {Course::BasicResource::STONE, 0.80},
    {Course::BasicResource::ORE, 0.70}
};
const Course::ResourceMap WATERTILE_BP={
    {Course::BasicResource::FOOD, 2}
};


const Course::ResourceMap WORKER_RECRUITMENT_COST = {
    {Course::BasicResource::MONEY, -20},
    {Course::BasicResource::FOOD, -50}
};
const Course::ResourceMap MINER_RECRUITMENT_COST={
    {Course::BasicResource::MONEY, -30},
    {Course::BasicResource::FOOD, -50}
};

const Course::ResourceMap HOUSE_BUILD_COST={
    {Course::BasicResource::MONEY, -50},
    {Course::BasicResource::FOOD, -25},
    {Course::BasicResource::WOOD, -100},
    {Course::BasicResource::STONE, -50}
};

const Course::ResourceMap HOUSE_PRODUCTION={
    {Course::BasicResource::MONEY, 0},
    {Course::BasicResource::FOOD, 0}
};
const Course::ResourceMap DOCK_BUILD_COST={
    {Course::BasicResource::MONEY, -50},
    {Course::BasicResource::FOOD, -50},
    {Course::BasicResource::WOOD, -100}
};

const Course::ResourceMap DOCK_PRODUCTION={
    {Course::BasicResource::MONEY, 0},
    {Course::BasicResource::FOOD, 3}
};
const Course::ResourceMap MINE_BUILD_COST={
    {Course::BasicResource::MONEY, -50},
    {Course::BasicResource::FOOD, -25},
    {Course::BasicResource::WOOD, -150}
};

const Course::ResourceMap MINE_PRODUCTION={
    {Course::BasicResource::MONEY, 50},
    {Course::BasicResource::FOOD, 0},
    {Course::BasicResource::ORE, 20},
    {Course::BasicResource::STONE, 50}

};
const Course::ResourceMap StoneBP={
  {Course::BasicResource::STONE, 2}
};


const Course::ResourceMap FOREST_BP = {
    {Course::BasicResource::MONEY, 1},
    {Course::BasicResource::FOOD, 3},
    {Course::BasicResource::WOOD, 5},
    {Course::BasicResource::STONE, 1},
    {Course::BasicResource::ORE, 0},
};

const Course::ResourceMap HQ_UPGRADE = {
    {Course::BasicResource::MONEY, -100},
    {Course::BasicResource::ORE, -150},
};

const Course::ResourceMap GRASSLAND_BP = {
    {Course::BasicResource::MONEY, 2},
    {Course::BasicResource::FOOD, 5},
    {Course::BasicResource::WOOD, 1},
    {Course::BasicResource::STONE, 1},
    {Course::BasicResource::ORE, 0},
};
}
}
#endif // RESOURCEMAPS_H
