#include <list>
#include <iostream>
#include "Building.h"
#include "Corridor.h"

Building::Building() : Component("new-building")
{}

Building::Building(std::string nm) : Component(nm)
{}

void Building::addLevel(Level level)
{
    this->levels.push_back(level);
}

std::list<Level> Building::getLevels()
{
    return this->levels;
}

void Building::removeLevel(Level level)
{
    std::list<Level>::iterator iter;
    for (iter=this->levels.begin(); iter!=this->levels.end(); ++iter)
    {
        if(*iter==level)
        {
            this->levels.remove(*iter);
        }
    }
}


void Building::setFloor(Level level)
{
    this->floor = level;
}
Level Building::getFloor()
{
    return this->floor;
}

void Building::findPath(std::string name)
{
    //
    std::cout << "NB lev:" <<this->levels.size()<< std::endl;
    std::list<Level>::iterator iter_lvl;
    for (iter_lvl=this->levels.begin(); iter_lvl!=this->levels.end(); ++iter_lvl)
    {
        std::list<Corridor> corrs = (*iter_lvl).getCorridors();
        std::cout << "NB cor:"<< corrs.size() << std::endl;

        std::list<Corridor>::iterator iter_cor;
        for (iter_cor=corrs.begin(); iter_cor!=corrs.end(); ++iter_cor)
        {
            std::cout << "Corr:" <<(*iter_cor).getName()<< std::endl;

            std::list<Classroom> clsRooms = (*iter_cor).getClassrooms();
            std::cout << "NB clsrooms:"<< clsRooms.size() << std::endl;

            std::list<Classroom>::iterator iter_cls;
            for (iter_cls=clsRooms.begin(); iter_cls!=clsRooms.end(); ++iter_cls)
            {
                std::cout << "Cls:" <<(*iter_cls).getName()<< std::endl;
                if((*iter_cls).getName().compare("33")==0){
                    std::cout << "OK"<< std::endl;

                    // Calcul chemin
                    // gauche ou droite
                    // monter ou descendre

                }
            }
        }
    }
}
