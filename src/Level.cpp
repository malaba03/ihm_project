#include "Level.h"

Level::Level() : Component("new-level")
{}

Level::Level(std::string nm) : Component(nm)
{}

// add get remove corridor
void Level::addCorridor(Corridor corridor)
{
    this->corridors.push_back(corridor);
}

std::list<Corridor> Level::getCorridors()
{
    return this->corridors;
}
void Level::removeCorridor(Corridor corridor)
{
    std::list<Corridor>::iterator iter;
    for (iter=this->corridors.begin(); iter!=this->corridors.end(); ++iter)
    {
        if(*iter==corridor)
        {
            this->corridors.remove(corridor);
        }
    }
}

// add get remove stair
void Level::addStair(Stair stair)
{
    this->stairs.push_back(stair);
}

std::list<Stair> Level::getStairs()
{
    return this->stairs;
}

void Level::removeStair(Stair stair)
{
    std::list<Stair>::iterator iter;
    for (iter=this->stairs.begin(); iter!=this->stairs.end(); ++iter)
    {
        if(*iter==stair)
        {
            this->stairs.remove(stair);
        }
    }
}

// add get remove elevator
void Level::addElevator(Elevator elevator)
{
    this->elevators.push_back(elevator);
}

std::list<Elevator> Level::getElevators()
{
    return this->elevators;
}

void Level::removeElevator(Elevator elevator)
{
    std::list<Elevator>::iterator iter;
    for (iter=this->elevators.begin(); iter!=this->elevators.end(); ++iter)
    {
        if(*iter==elevator)
        {
            this->elevators.remove(elevator);
        }
    }
}
/*
void Level::setBuilding(Building bld)
{this.building = bld;}

Building Level::getBuilding()
{return this.building;}*/
