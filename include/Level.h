#ifndef LEVEL_H
#define LEVEL_H

#include "Component.h"
//#include "Building.h"
#include "Corridor.h"
#include "Stair.h"
#include "Elevator.h"

class Level : public Component
{
    public:
        Level();
        Level(std::string nm);

        void setState(int s)
        {state=s;}

        void addCorridor(Corridor corridor);
        void addStair(Stair stair);
        void addElevator(Elevator elevator);

        std::list<Corridor> getCorridors();
        std::list<Stair> getStairs();
        std::list<Elevator> getElevators();

        void removeCorridor(Corridor corridor);
        void removeStair(Stair stair);
        void removeElevator(Elevator elevator);

       /* void setBuilding(Building bld);
        Building getBuilding();*/
    protected:
    private:
        std::list<Corridor> corridors;
        std::list<Stair> stairs;
        std::list<Elevator> elevators;

        //Building building;
};

#endif // LEVEL_H
