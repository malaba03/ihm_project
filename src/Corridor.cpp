#include "Corridor.h"

Corridor::Corridor() : Component("new-corridor")
{}

Corridor::Corridor(std::string nm) : Component(nm)
{}

// add get remove classrooms
void Corridor::addClassroom(Classroom classroom)
{
    this->classrooms.push_back(classroom);
}

std::list<Classroom> Corridor::getClassrooms()
{
    return this->classrooms;
}
void Corridor::removeClassroom(Classroom classroom)
{
    std::list<Classroom>::iterator iter;
    for (iter=this->classrooms.begin(); iter!=this->classrooms.end(); ++iter)
    {
        if(*iter==classroom)
        {
            this->classrooms.remove(classroom);
        }
    }
}

// add get remove restrooms
void Corridor::addRestroom(Restroom restroom)
{
    this->restrooms.push_back(restroom);
}

std::list<Restroom> Corridor::getRestrooms()
{
    return this->restrooms;
}

void Corridor::removeRestroom(Restroom restroom)
{
    std::list<Restroom>::iterator iter;
    for (iter=this->restrooms.begin(); iter!=this->restrooms.end(); ++iter)
    {
        if(*iter==restroom)
        {
            this->restrooms.remove(restroom);
        }
    }
}

// add get remove stair
void Corridor::addStair(Stair stair)
{
    this->stairs.push_back(stair);
}

std::list<Stair> Corridor::getStairs()
{
    return this->stairs;
}

void Corridor::removeStair(Stair stair)
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
void Corridor::addElevator(Elevator elevator)
{
    this->elevators.push_back(elevator);
}

std::list<Elevator> Corridor::getElevators()
{
    return this->elevators;
}

void Corridor::removeElevator(Elevator elevator)
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
