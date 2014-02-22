#ifndef CORRIDOR_H
#define CORRIDOR_H

#include "Component.h"
//#include "Level.h"
#include "Classroom.h"
#include "Restroom.h"
#include "Stair.h"
#include "Elevator.h"
#include "Junction.h"


class Corridor : public Component
{
    public:
        Corridor();
        Corridor(std::string nm);

        void setState(int s)
        {state=s;}

        void addClassroom(Classroom classroom);
        std::list<Classroom> getClassrooms();
        void removeClassroom(Classroom classroom);

        void addRestroom(Restroom restroom);
        std::list<Restroom> getRestrooms();
        void removeRestroom(Restroom restroom);

        void addStair(Stair stair);
        std::list<Stair> getStairs();
        void removeStair(Stair stair);

        void addElevator(Elevator elevator);
        std::list<Elevator> getElevators();
        void removeElevator(Elevator elevator);

        void addJunction(Junction junction);
        std::list<Junction> getJunctions();
        void removeJunction(Junction junction);
        //void findPath(std::string className);
    protected:
    private:
        std::list<Classroom> classrooms;
        std::list<Restroom> restrooms;

        std::list<Stair> stairs;
        std::list<Elevator> elevators;

        std::list<Junction> junctions;
};

#endif // CORRIDOR_H
